/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kift_say.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkalia <jkalia@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/11 04:31:51 by jkalia            #+#    #+#             */
/*   Updated: 2017/06/11 04:35:47 by jkalia           ###   ########.fr       */
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

	for(i=0; input[i] != 0; i++)
		input[i] = toupper((int)input[i]);

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
