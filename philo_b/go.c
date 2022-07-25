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

int	go_two(t_philo *philo)
{
	if (sem_wait(philo->print) == -1)
		return (0);
	gettimeofday(&(philo->tm), NULL);
	philo->start_sleep = philo->tm.tv_sec * 1000 + philo->tm.tv_usec / 1000;
	printf("Clown %i start sleep. Vremya uhodit %li\n", \
	philo->index, philo->start_sleep - philo->start_time);
	if (sem_post(philo->print) == -1)
		return (0);
	true_sleep(philo->time_sleep);
	if (sem_wait(philo->print) == -1)
		return (0);
	gettimeofday(&(philo->tm), NULL);
	philo->start_think = philo->tm.tv_sec * 1000 + philo->tm.tv_usec / 1000;
	printf("Clown %i start think. Vremya uhodit %li\n", \
	philo->index, philo->start_think - philo->start_time);
	if (sem_post(philo->print) == -1)
		return (0);
	return (1);
}

int	go_one(t_philo *philo)
{
	if (sem_wait(philo->print) == -1)
		return (0);
	gettimeofday(&(philo->tm), NULL);
	philo->start_eat = philo->tm.tv_sec * 1000 + philo->tm.tv_usec / 1000;
	printf("Clown %i start eat. Vremya uhodit %li\n", philo->index, \
	philo->start_eat - philo->start_time);
	if (philo->circles != -1)
		philo->take_food++;
	if (sem_post(philo->print) == -1)
		return (0);
	true_sleep(philo->time_eat);
	if (sem_post(philo->sema) == -1)
		return (0);
	if (sem_post(philo->sema) == -1)
		return (0);
	if (philo->take_food == philo->circles)
	{
		printf("END THIS SHIT %i\n", philo->index);
		sem_post(philo->if_circle);
		exit(0);
	}
	return (1);
}

int	go(t_philo *philo)
{
	if (sem_wait(philo->sema) == -1)
		return (0);
	if (sem_wait(philo->print) == -1)
		return (0);
	gettimeofday(&(philo->tm), NULL);
	philo->vilka_time = philo->tm.tv_sec * 1000 + philo->tm.tv_usec / 1000;
	printf("Clown %i joke left: %li\n", philo->index, \
	philo->vilka_time - philo->start_time);
	if (sem_post(philo->print) == -1)
		return (0);
	if (sem_wait(philo->sema) == -1)
		return (0);
	if (sem_wait(philo->print) == -1)
		return (0);
	gettimeofday(&(philo->tm), NULL);
	philo->vilka_time = philo->tm.tv_sec * 1000 + philo->tm.tv_usec / 1000;
	printf("Clown %i joke right: %li\n", philo->index, \
	philo->vilka_time - philo->start_time);
	if (sem_post(philo->print) == -1)
		return (0);
	go_one(philo);
	go_two(philo);
	return (1);
}
