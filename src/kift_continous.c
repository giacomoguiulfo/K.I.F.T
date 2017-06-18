/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kift_continous.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/18 06:20:54 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/06/18 08:41:49 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**  ====================================================================
**	Copyright (c) 1999-2010 Carnegie Mellon University.  All rights
**	reserved.
**
**	Redistribution and use in source and binary forms, with or without
**	modification, are permitted provided that the following conditions
**	are met:
**
**	1.	Redistributions of source code must retain the above copyright
**		notice, this list of conditions and the following disclaimer.
**
**	2.	Redistributions in binary form must reproduce the above copyright
**		notice, this list of conditions and the following disclaimer in
**		the documentation and/or other materials provided with the
**		distribution.
**
**	This work was supported in part by funding from the Defense Advanced
**	Research Projects Agency and the National Science Foundation of the
**	United States of America, and the CMU Sphinx Speech Consortium.
**
**	THIS SOFTWARE IS PROVIDED BY CARNEGIE MELLON UNIVERSITY ``AS IS'' AND
**	ANY EXPRESSED OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
**	THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
**	PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL CARNEGIE MELLON UNIVERSITY
**	NOR ITS EMPLOYEES BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
**	SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
**	LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
**	DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
**	THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
**	(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
**	OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**
**	====================================================================
*/

#include <kift.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <sys/select.h>
#include <sphinxbase/err.h>
#include <sphinxbase/ad.h>
#include "pocketsphinx.h"
#include "norm_helpers.h"

static ps_decoder_t	*g_ps;
static cmd_ln_t		*g_config;
static FILE			*g_rawdf;

static int	e_error_rtn(char *header, int index, char *error_msg)
{
	E_ERROR(error_msg, header[index]);
	return (0);
}

static int	check_wav_header(char *header, int expected_sr)
{
	int sr;

	if (header[34] != 0x10)
		return (e_error_rtn(header, 34,
		"Input audio file has [%d] bits per sample instead of 16\n"));
	if (header[20] != 0x1)
		return (e_error_rtn(header, 20,
		"Input audio file has compression [%d] and not required PCM\n"));
	if (header[22] != 0x1)
		return (e_error_rtn(header, 22,
		"Input audio file has [%d] channels, expected single channel mono\n"));
	sr = ((header[24] & 0xFF) | ((header[25] & 0xFF) << 8) |
		((header[26] & 0xFF) << 16) | ((header[27] & 0xFF) << 24));
	if (sr != expected_sr)
	{
		E_ERROR(WAV_MSG_E" [%d], but decoder expects [%d]\n", sr, expected_sr);
		return (0);
	}
	return (1);
}

static void	print_word_times()
{
	float		conf;
	int			frame_rate;
	ps_seg_t	*iter;
	t_norm_ints	norm_ints;

	frame_rate = cmd_ln_int32_r(g_config, "-frate");
	iter = ps_seg_iter(g_ps);
	while (iter != NULL)
	{
		ps_seg_frames(iter, &norm_ints.sf, &norm_ints.ef);
		norm_ints.pprob = ps_seg_prob(iter, NULL, NULL, NULL);
		conf = logmath_exp(ps_get_logmath(g_ps), norm_ints.pprob);
		printf("%s %.3f %.3f %f\n", ps_seg_word(iter),
				((float)norm_ints.sf / frame_rate),
				((float) norm_ints.ef / frame_rate), conf);
		iter = ps_seg_next(iter);
	}
}



static void	recognize_from_file(const char *fname, t_server *server)
{
	t_recognize_h all_v;

	all_v.print_times = cmd_ln_boolean_r(g_config, "-time");
	if ((g_rawdf = fopen(fname, "rb")) == NULL)
		E_FATAL_SYSTEM("Failed to open file '%s' for reading", fname);
	if (strlen(fname) > 4 && strcmp(fname + strlen(fname) - 4, ".wav") == 0)
	{
		char waveheader[44];
		fread(waveheader, 1, 44, g_rawdf);
		if (!check_wav_header(waveheader, (int)cmd_ln_float32_r(g_config, "-samprate")))
			E_FATAL("Failed to process file '%s' due to format mismatch.\n", fname);
	}
	if (strlen(fname) > 4 && strcmp(fname + strlen(fname) - 4, ".mp3") == 0)
		E_FATAL("Can not decode mp3 files, convert input file to WAV 16kHz 16-bit mono before decoding.\n");
	ps_start_utt(g_ps);
	all_v.utt_started = FALSE;
	while ((all_v.k = fread(all_v.adbuf, sizeof(int16), 2048, g_rawdf)) > 0)
	{
		ps_process_raw(g_ps, all_v.adbuf, all_v.k, FALSE, FALSE);
		all_v.in_speech = ps_get_in_speech(g_ps);
		if (all_v.in_speech && !(all_v.utt_started))
			all_v.utt_started = TRUE;
		if (!(all_v.in_speech) && all_v.utt_started)
		{
			ps_end_utt(g_ps);
			all_v.hyp = ps_get_hyp(g_ps, NULL);
			if (all_v.hyp != NULL)
			{
				printf("%s\n", all_v.hyp);
				server->recognized_len = strlen(all_v.hyp);
				strncpy(server->recognized, all_v.hyp, server->recognized_len);
			}
			if (all_v.print_times)
				print_word_times();
			fflush(stdout);
			ps_start_utt(g_ps);
			all_v.utt_started = FALSE;
		}
	}
	ps_end_utt(g_ps);
	if (all_v.utt_started)
	{
		all_v.hyp = ps_get_hyp(g_ps, NULL);
		if (all_v.hyp != NULL)
		{
			printf("%s\n", all_v.hyp);
			server->recognized_len = strlen(all_v.hyp);
			strncpy(server->recognized, all_v.hyp, server->recognized_len);
			if (all_v.print_times)
				print_word_times();
		}
	}
	fclose(g_rawdf);
}

int			init_pocketsphinx(t_server *server)
{
	char const	*cfg;

	g_config = cmd_ln_init(NULL, ps_args(), TRUE,
			"-hmm", MODELDIR "/en-us/en-us",
			"-lm", "./new_acoustic_model/new_acoustic_model.lm",
			"-dict", "./new_acoustic_model/new_acoustic_model.dict",
			NULL);
	g_ps = ps_init(g_config);
	if (g_ps == NULL)
	{
		cmd_ln_free_r(g_config);
		return (1);
	}
	recognize_from_file("out.wav", server);
	ps_free(g_ps);
	cmd_ln_free_r(g_config);
	return (0);
}
