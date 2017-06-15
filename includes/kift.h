/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kift.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkalia <jkalia@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 01:50:55 by jkalia            #+#    #+#             */
/*   Updated: 2017/06/14 21:36:33 by jkalia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KIFT_H
# define KIFT_H
# include <libft.h>
# include <pocketsphinx.h>
# include <reciter.h>
# include <sam.h>
# include <debug.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# ifdef USESDL
#  include <SDL.h>
#  include <SDL_audio.h>
# endif
#define BUFFER 1024

typedef struct	s_server
{
	char	recognized[BUFFER];
	int	recognized_len;
	char	response[BUFFER];
	int	response_len;
	char	send[BUFFER * 12];
	int	send_len;
}		t_server;

int		init_pocketsphinx(t_server *server);
void		run_commands(char *cmd, t_server *server);
int		say(char *input);
#endif
