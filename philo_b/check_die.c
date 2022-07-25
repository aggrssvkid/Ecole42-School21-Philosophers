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

#include "libphilo_bonus.h"

void	*check_die(void *args)
{
	t_philo	*philo;

	philo = (t_philo *) args;
	while (1)
	{
		usleep(1000);
		gettimeofday(&(philo->tm), NULL);
		philo->now_time = philo->tm.tv_sec * 1000 + philo->tm.tv_usec / 1000;
		if (philo->now_time - philo->start_eat > philo->time_die)
		{
			sem_wait(philo->print);
			gettimeofday(&(philo->tm), NULL);
			philo->now_time = philo->tm.tv_sec * 1000 + \
			philo->tm.tv_usec / 1000;
			printf("Clown %i pomer. A vremya smerti is: %li\n", \
			philo->index, philo->now_time - philo->start_time);
			sem_post(philo->dead);
		}
	}
	return (NULL);
}
