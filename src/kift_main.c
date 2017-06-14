/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kift_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkalia <jkalia@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 01:50:16 by jkalia            #+#    #+#             */
/*   Updated: 2017/06/12 02:59:21 by jkalia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <kift.h>

/**
int		main(int argc, char **argv)
{
	ps_decoder_t *ps;
	cmd_ln_t *config;
	FILE *fh;
	char const *hyp, *uttid;
	int16 buf[512];
	int rv;
	int32 score;

	config = cmd_ln_init(NULL, ps_args(), TRUE,
			"-hmm", MODELDIR "/en-us/en-us",
			"-lm", MODELDIR "/en-us/en-us.lm.bin",
			"-dict", MODELDIR "/en-us/cmudict-en-us.dict",
			NULL);

	CHECK(config == NULL, RETURN(-1), "Failed to create config object, see log for  details");
	ps = ps_init(config);
	CHECK(ps == NULL, RETURN(-1), "Failed to create recognizer, see log for  details");

	fh = fopen("goforward.raw", "rb");
	CHECK(fh == NULL, RETURN(-1), "Unable to open input file goforward.raw");

	rv = ps_start_utt(ps);

	while (!feof(fh))
	{
		size_t nsamp;
		nsamp = fread(buf, 2, 512, fh);
		rv = ps_process_raw(ps, buf, nsamp, FALSE, FALSE);
	}

	rv = ps_end_utt(ps);
	hyp = ps_get_hyp(ps, &score);
	printf("Recognized: %s\n", hyp);

	recognize_from_microphone();
//	say(strdup(hyp));
	fclose(fh);
	ps_free(ps);
	cmd_ln_free_r(config);
	return 0;
}
**/
