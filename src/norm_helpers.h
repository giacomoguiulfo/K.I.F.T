/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm_helpers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/18 06:48:32 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/06/18 07:04:59 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NORM_HELPERS_H
# define NORM_HELPERS_H

# define WAV_MSG_E "Input audio file has sample rate"

typedef struct	s_norm_ints
{
	int32		sf;
	int32		ef;
	int32		pprob;
}				t_norm_ints;

typedef struct	s_recognize_h
{
	const		char *hyp;
	int16		adbuf[2048];
	int32		k;
	uint8		utt_started;
	uint8		in_speech;
	int32		print_times;
}				t_recognize_h;

#endif
