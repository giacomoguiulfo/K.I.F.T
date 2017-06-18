/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kift_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaleman <jaleman@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/11 02:21:22 by jaleman           #+#    #+#             */
/*   Updated: 2017/06/18 15:46:59 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <kift.h>

/*
** This function copies str to appropriate buffer in server struct
*/

void		ft_putbuf(const char *str, t_server *server)
{
	if (server->response_len != 0)
		return ;
	server->response_len = strlen(str);
	strncpy(server->response, str, server->response_len);
	printf("%s\n", str);
}

/*
** This function do one of the following:
**   - Invert the creen colors.
**   - Brightness display to 100%
**   - Brightness display to 5%
*/

static int	control_display(char *cmd, t_server *server)
{
	int		ret;

	ret = 0;
	if (!strcmp(cmd, "invert colors"))
	{
		ret = system("osascript -e 'tell application \"System Events\"' \
		-e 'key code 28 using {control down, option down, command down}' \
		-e 'end tell'");
		ft_putbuf("showing search results", server);
	}
	else if (!strcmp(cmd, "lights on") || !strcmp(cmd, "undim the screen"))
	{
		ret = system("osascript -e 'tell application \"System Events\"' \
		-e 'repeat 16 times' -e 'key code 144' -e 'end repeat' -e 'end tell'");
		ft_putbuf("showing search results", server);
	}
	else if (!strcmp(cmd, "lights off") || !strcmp(cmd, "dim the screen"))
	{
		ret = system("osascript -e 'tell application \"System Events\"' \
		-e 'repeat 16 times' -e 'key code 145' -e 'end repeat' -e 'end tell'");
		ft_putbuf("showing search results", server);
	}
	return (ret);
}

/*
** This function do one of the following:
**   - Mute the sound.
**   - Unmute the sound.
*/

static int	control_sound(char *cmd, t_server *server)
{
	int		ret;

	ret = 0;
	if (!strcmp(cmd, "mute") || !strcmp(cmd, "shut up"))
	{
		ret = system("osascript -e 'set volume with output muted'");
		ft_putbuf("showing search results", server);
	}
	else if (!strcmp(cmd, "unmute") || !strcmp(cmd, "speak"))
	{
		ret = system("osascript -e 'set volume without output muted'");
		ft_putbuf("showing search results", server);
	}
	return (ret);
}

/*
** This function do one of the following:
**   - Takes a screenshot of the whole screen.
**   - Takes a screenshot of just a section of the screen.
*/

static int	control_screenshot(char *cmd, t_server *server)
{
	int		ret;

	ret = 0;
	if (!strcmp(cmd, "screenshot"))
	{
		ret = system("screencapture ~/Desktop/$(date +%Y%m%d%H%M%S).png");
		ft_putbuf("showing search results", server);
	}
	else if (!strcmp(cmd, "take a section"))
	{
		ret = system("screencapture -i ~/Desktop/$(date +%Y%m%d%H%M%S).png");
		ft_putbuf("showing search results", server);
	}
	return (ret);
}

/*
** Run a specific command if it matches the words.
*/

void		run_commands(char *cmd, t_server *server)
{
	if (strncmp("KEVIN", cmd, 5))
	{
		ft_putbuf("name missing", server);
		return ;
	}
	if (control_finder(cmd, server) == ERROR)
		ft_putbuf("something went wrong!", server);
	if (control_display(cmd, server) == ERROR)
		ft_putbuf("something went wrong!", server);
	if (control_sound(cmd, server) == ERROR)
		ft_putbuf("something went wrong!", server);
	if (control_screenshot(cmd, server) == ERROR)
		ft_putbuf("something went wrong!", server);
	ft_putbuf("command not recognized", server);
}
