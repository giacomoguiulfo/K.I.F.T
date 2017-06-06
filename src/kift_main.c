/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kift_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkalia <jkalia@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 01:50:16 by jkalia            #+#    #+#             */
/*   Updated: 2017/06/06 05:35:47 by jkalia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <kift.h>
int debug = 0;

int		say(char *input)
{
	int		i;
	int		phonetic = 0;

	char	*wavfilename = NULL;
	SetSpeed(100);

	/**
	if (argc <= 1)
	{
		PrintUsage();
		return 1;
	}

	i = 1;
	while(i < argc)
	{
		if (argv[i][0] != '-')
		{
			strcat(input, argv[i]);
			strcat(input, " ");
		} else
		{
			if (strcmp(&argv[i][1], "wav")==0)
			{
				wavfilename = argv[i+1];
				i++;
			} else
			if (strcmp(&argv[i][1], "sing")==0)
			{
				EnableSingmode();
			} else
			if (strcmp(&argv[i][1], "phonetic")==0)
			{
				phonetic = 1;
			} else
			if (strcmp(&argv[i][1], "debug")==0)
			{
				debug = 1;
			} else
			if (strcmp(&argv[i][1], "pitch")==0)
			{
				SetPitch(atoi(argv[i+1]));
				i++;
			} else
			if (strcmp(&argv[i][1], "speed")==0)
			{
				SetSpeed(atoi(argv[i+1]));
				i++;
			} else
			if (strcmp(&argv[i][1], "mouth")==0)
			{
				SetMouth(atoi(argv[i+1]));
				i++;
			} else
			if (strcmp(&argv[i][1], "throat")==0)
			{
				SetThroat(atoi(argv[i+1]));
				i++;
			} else
			{
				PrintUsage();
				return 1;
			}
		}
		
		i++;
	} //while
	**/

	for(i=0; input[i] != 0; i++)
		input[i] = toupper((int)input[i]);

	/**
	if (debug)
	{
		if (phonetic) printf("phonetic input: %s\n", input);
		else printf("text input: %s\n", input); 
	}
	**/
	
	if (!phonetic)
	{
		strcat(input, "[");
		if (!TextToPhonemes(input)) return 1;
		if (debug)
			printf("phonetic input: %s\n", input);
	} else strcat(input, "\x9b");

#ifdef USESDL
	if ( SDL_Init(SDL_INIT_AUDIO) < 0 ) 
	{
		printf("Unable to init SDL: %s\n", SDL_GetError());
		exit(1);
	}
	atexit(SDL_Quit);
#endif

	SetInput(input);
	if (!SAMMain())
	{
		PrintUsage();
		return (1);
	}
	
	if (wavfilename != NULL) 
		WriteWav(wavfilename, GetBuffer(), GetBufferLength()/50);
	else
		OutputSound();
	return (0);
}

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
	say(strdup(hyp));
	fclose(fh);
	ps_free(ps);
	cmd_ln_free_r(config);
	return 0;
}
