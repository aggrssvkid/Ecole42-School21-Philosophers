/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enoye <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 14:17:14 by enoye             #+#    #+#             */
/*   Updated: 2022/03/03 14:17:56 by enoye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libphilo.h"

void	true_sleep(long time)
{
	long			start_time;
	long			current_time;
	struct timeval	tm;

	gettimeofday(&tm, NULL);
	start_time = tm.tv_sec * 1000 + tm.tv_usec / 1000;
	current_time = start_time;
	while (current_time - start_time < time)
	{
		usleep(250);
		gettimeofday(&tm, NULL);
		current_time = tm.tv_sec * 1000 + tm.tv_usec / 1000;
	}
}
