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

void	print_die(t_philo *philo)
{
	pthread_mutex_lock(philo->print);
	usleep(200);
	if (*(philo->is_dead) == 0)
	{
		gettimeofday(&(philo->tm), NULL);
		philo->now_time = philo->tm.tv_sec * 1000 + philo->tm.tv_usec / 1000;
		printf("Chel nomer %i pomer! Pomyanem. %li\n", philo->index, \
		philo->now_time - philo->start_time);
	}
	*(philo->is_dead) = 1;
}
