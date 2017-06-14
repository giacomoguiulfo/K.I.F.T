#include <kift.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#if defined(_WIN32) && !defined(__CYGWIN__)
#include <windows.h>
#else
#include <sys/select.h>
#endif

#include <sphinxbase/err.h>
#include <sphinxbase/ad.h>

#include "pocketsphinx.h"

static ps_decoder_t *ps;
static cmd_ln_t *config;
static FILE *rawfd;

static int check_wav_header(char *header, int expected_sr)
{
	int sr;

	if (header[34] != 0x10) {
		E_ERROR("Input audio file has [%d] bits per sample instead of 16\n", header[34]);
		return 0;
	}
	if (header[20] != 0x1) {
		E_ERROR("Input audio file has compression [%d] and not required PCM\n", header[20]);
		return 0;
	}
	if (header[22] != 0x1) {
		E_ERROR("Input audio file has [%d] channels, expected single channel mono\n", header[22]);
		return 0;
	}
	sr = ((header[24] & 0xFF) | ((header[25] & 0xFF) << 8) | ((header[26] & 0xFF) << 16) | ((header[27] & 0xFF) << 24));
	if (sr != expected_sr) {
		E_ERROR("Input audio file has sample rate [%d], but decoder expects [%d]\n", sr, expected_sr);
		return 0;
	}
	return 1;
}

static void print_word_times()
{
	int frame_rate = cmd_ln_int32_r(config, "-frate");
	ps_seg_t *iter = ps_seg_iter(ps);
	while (iter != NULL) {
		int32 sf, ef, pprob;
		float conf;

		ps_seg_frames(iter, &sf, &ef);
		pprob = ps_seg_prob(iter, NULL, NULL, NULL);
		conf = logmath_exp(ps_get_logmath(ps), pprob);
		printf("%s %.3f %.3f %f\n", ps_seg_word(iter), ((float)sf / frame_rate),
				((float) ef / frame_rate), conf);
		iter = ps_seg_next(iter);
	}
}

/*
 * Continuous recognition from a file
 */
static void recognize_from_file(const char *fname, t_server *server)
{
	int16 adbuf[2048];
	const char *hyp;
	int32 k;
	uint8 utt_started, in_speech;
	int32 print_times = cmd_ln_boolean_r(config, "-time");

	if ((rawfd = fopen(fname, "rb")) == NULL)
	{
		if ((rawfd = fopen(fname, "rb")) == NULL) {
			E_FATAL_SYSTEM("Failed to open file '%s' for reading",
					fname);
		}
		if (strlen(fname) > 4 && strcmp(fname + strlen(fname) - 4, ".wav") == 0)
		{
			char waveheader[44];
			fread(waveheader, 1, 44, rawfd);
			if (!check_wav_header(waveheader, (int)cmd_ln_float32_r(config, "-samprate")))
				E_FATAL("Failed to process file '%s' due to format mismatch.\n", fname);
		}
		ps_start_utt(ps);
		utt_started = FALSE;

		while ((k = fread(adbuf, sizeof(int16), 2048, rawfd)) > 0)
		{
			ps_process_raw(ps, adbuf, k, FALSE, FALSE);
			in_speech = ps_get_in_speech(ps);
			if (in_speech && !utt_started) 
				utt_started = TRUE;
			if (!in_speech && utt_started)
			{
				ps_end_utt(ps);
				hyp = ps_get_hyp(ps, NULL);
				if (hyp != NULL)
				{
					ft_printf("%{red}\t%s%{eoc}\n", hyp);
					run_commands(strdup(hyp));
					strncpy(server->reply, hyp, strlen(hyp));
				}
				fflush(stdout);
				ps_start_utt(ps);
				utt_started = FALSE;
			}
		}
		ps_end_utt(ps);
		if (utt_started)
		{
			hyp = ps_get_hyp(ps, NULL);
			if (hyp != NULL) 
			{
				ft_printf("%{red}\t%s%{eoc}\n", hyp);
				run_commands(strdup(hyp));
				strncpy(server->reply, hyp, strlen(hyp));
			}
		}
		fclose(rawfd);
	}
}
// Sleep for specified msec
static void		sleep_msec(int32 ms)
{
	struct timeval tmo;

	tmo.tv_sec = 0;
	tmo.tv_usec = ms * 1000;

	select(0, NULL, NULL, NULL, &tmo);
}

int init_pocketsphinx(t_server *server)
{
	config = cmd_ln_init(NULL, ps_args(), TRUE,
			"-hmm", MODELDIR "/en-us/en-us",
			"-lm", MODELDIR "/en-us/en-us.lm.bin",
			"-dict", MODELDIR "/en-us/cmudict-en-us.dict",
			NULL);
	ps_default_search_args(config);
	ps = ps_init(config);
	if (ps == NULL) 
	{
		cmd_ln_free_r(config);
		return 1;
	}
	recognize_from_file("out.wav", server);
	ps_free(ps);
	cmd_ln_free_r(config);
	return (0);
}
