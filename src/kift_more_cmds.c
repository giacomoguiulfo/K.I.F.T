/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kift_more_cmds.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/18 10:25:58 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/06/18 10:38:56 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <kift.h>

/*
** This function do one of the following:
**   - Show the active programs
**   - Search
**   - Hide hidden files
**   - Show hidden files
**   - Sleep
*/

static void	control_finder_extension(int *ret, char *cmd, t_server *server)
{
	if (!strcmp(cmd, "KEVIN SHOW HIDDEN FILES"))
	{
		*ret = system("defaults write com.apple.finder AppleShowAllFiles YES \
		&& killall Finder '/System/Library/CoreServices/Finder.app'");
		ft_putbuf("showing hidden files", server);
	}
	else if (!strcmp(cmd, "KEVIN SLEEP"))
	{
		*ret = system("osascript -e 'tell application \"Finder\" to sleep'");
		ft_putbuf("entering sleep mode", server);
	}
}

int			control_finder(char *cmd, t_server *server)
{
	int		ret;

	ret = 0;
	if (!strcmp(cmd, "KEVIN SHOW"))
	{
		ret = system("osascript -e 'tell application \"System Events\"' \
		-e 'key code 160' -e 'end tell'");
		ft_putbuf("showing active programs", server);
	}
	else if (!strcmp(cmd, "KEVIN DO NOT SHOW HIDDEN FILES"))
	{
		ret = system("defaults write com.apple.finder AppleShowAllFiles NO \
		&& killall Finder '/System/Library/CoreServices/Finder.app'");
		ft_putbuf("hiding hidden files", server);
	}
	else
		control_finder_extension(&ret, cmd, server);
	return (ret);
}
