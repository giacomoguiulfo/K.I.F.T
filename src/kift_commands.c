/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kift_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaleman <jaleman@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/11 02:21:22 by jaleman           #+#    #+#             */
/*   Updated: 2017/06/11 04:20:30 by jkalia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// TODO : Put all the includes and defines into its own "kift.h"
// Use ft_strequ instead of strcmp for code readability?

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ERROR	(-1)


/*
** This function do one of the following:
**   - Show the active programs
**   - Search
**   - Hide hidden files
**   - Show hidden files
*/

static int	control_finder(char *cmd)
{
	int		ret;

	if (!strcmp(cmd, "show active programs"))
		ret = system("osascript -e 'tell application \"System Events\"' \
		-e 'key code 160' -e 'end tell'");
	else if (!strcmp(cmd, "search"))
		ret = system("osascript -e 'tell application \"System Events\"' \
		-e 'key code 131' -e 'end tell'");
	else if (!strcmp(cmd, "hide hidden files"))
		ret = system("defaults write com.apple.finder AppleShowAllFiles NO \
		&& killall Finder '/System/Library/CoreServices/Finder.app'");
	else if (!strcmp(cmd, "show hidden files"))
		ret = system("defaults write com.apple.finder AppleShowAllFiles YES \
		&& killall Finder '/System/Library/CoreServices/Finder.app'");
	ret = 0;
	return (ret);
}

/*
** This function do one of the following:
**   - Invert the creen colors.
**   - Brightness display to 100%
**   - Brightness display to 5%
*/

static int	control_display(char *cmd)
{
	int		ret;

	if (!strcmp(cmd, "invert colors"))
		ret = system("osascript -e 'tell application \"System Events\"' \
		-e 'key code 28 using {control down, option down, command down}' \
		-e 'end tell'");
	else if (!strcmp(cmd, "lights on") || !strcmp(cmd, "undim the screen"))
		ret = system("osascript -e 'tell application \"System Events\"' \
		-e 'repeat 16 times' -e 'key code 144' -e 'end repeat' -e 'end tell'");
	else if (!strcmp(cmd, "lights off") || !strcmp(cmd, "dim the screen"))
		ret = system("osascript -e 'tell application \"System Events\"' \
		-e 'repeat 16 times' -e 'key code 145' -e 'end repeat' -e 'end tell'");
	ret = 0;
	return (ret);
}

/*
** This function do one of the following:
**   - Mute the sound.
**   - Unmute the sound.
*/

static int	control_sound(char *cmd)
{
	int		ret;

	if (!strcmp(cmd, "mute") || !strcmp(cmd, "shut up"))
		ret = system("osascript -e 'set volume with output muted'");
	else if (!strcmp(cmd, "unmute") || !strcmp(cmd, "speak"))
		ret = system("osascript -e 'set volume without output muted'");
	ret = 0;
	return (ret);
}

/*
** This function do one of the following:
**   - Takes a screenshot of the whole screen.
**   - Takes a screenshot of just a section of the screen.
*/

static int	control_screenshot(char *cmd)
{
	int		ret;

	if (!strcmp(cmd, "screenshot"))
		ret = system("screencapture ~/Desktop/$(date +%Y%m%d%H%M%S).png");
	else if (!strcmp(cmd, "take a section"))
		ret = system("screencapture -i ~/Desktop/$(date +%Y%m%d%H%M%S).png");
	ret = 0;
	return (ret);
}

/*
** This function is from my libft, it uses ft_putendl instead of printf.
*/

void	ft_puterror(char *str, int ret)
{
	printf("%s\n", str);
	exit(ret);
}

/*
** Run a specific command if it matches the words.
*/

void		run_commands(char *cmd)
{
	if (control_finder(cmd) == ERROR)
		ft_puterror("Something went wrong!", -1);
	if (control_display(cmd) == ERROR)
		ft_puterror("Something went wrong!", -1);
	if (control_sound(cmd) == ERROR)
		ft_puterror("Something went wrong!", -1);
	if (control_screenshot(cmd) == ERROR)
		ft_puterror("Something went wrong!", -1);
}
