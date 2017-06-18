/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kift_log.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/18 04:54:07 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/06/18 04:59:10 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

void	kift_log(char *recognized)
{
	char buf[2048];

	sprintf(buf, "echo \"%s\" >> kevin_log.txt", recognized);
	system(buf);
}
