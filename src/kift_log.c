/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kift_log.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/18 04:54:07 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/06/18 17:19:24 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

void	kift_log(char *recognized, char *response)
{
	char buf[2048];

	sprintf(buf, "echo \"User: '%s'\" >> kevin_log.txt", recognized);
	system(buf);
	if (strcmp(response, "name missing\n"))
	{
		sprintf(buf, "echo \"Kevin: '%s'\" >> kevin_log.txt", response);
		system(buf);
	}
}
