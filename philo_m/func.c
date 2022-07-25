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

void	ne_hvatilo_mesta(t_philo *philo)
{
	gettimeofday(&(philo->tm), NULL);
	philo->start_think = philo->tm.tv_sec * 1000 + philo->tm.tv_usec / 1000;
	pthread_mutex_lock(philo->print);
	if (*(philo->is_dead) == 0)
		printf("Chel nomer %i dumaet. Vremya uhodit %li\n", philo->index, \
		philo->start_think - philo->start_time);
	pthread_mutex_unlock(philo->print);
}

void	print_vilkins(t_philo *philo)
{
	pthread_mutex_lock(&(philo->fork[philo->left]));
	gettimeofday(&(philo->tm), NULL);
	philo->time_left = philo->tm.tv_sec * 1000 + philo->tm.tv_usec / 1000;
	pthread_mutex_lock(philo->print);
	if (*(philo->is_dead) == 0)
		printf("Chelik %i vzyal left. Vremya uhodit %li\n", philo->index, \
		philo->time_left - philo->start_time);
	pthread_mutex_unlock(philo->print);
	pthread_mutex_lock(&(philo->fork[philo->right]));
	gettimeofday(&(philo->tm), NULL);
	philo->time_right = philo->tm.tv_sec * 1000 + philo->tm.tv_usec / 1000;
	pthread_mutex_lock(philo->print);
	if (*(philo->is_dead) == 0)
		printf("Chelik nomer %i vzyal vilkins right. Vremya uhodit %li\n", \
		philo->index, philo->time_right - philo->start_time);
	pthread_mutex_unlock(philo->print);
}

void	go(t_philo *philo)
{
	print_vilkins(philo);
	gettimeofday(&(philo->tm), NULL);
	philo->start_eat = philo->tm.tv_sec * 1000 + philo->tm.tv_usec / 1000;
	pthread_mutex_lock(philo->print);
	if (*(philo->is_dead) == 0)
		printf("Chel nomer %i kushaet. Vremya uhodit %li\n", \
		philo->index, philo->start_eat - philo->start_time);
	if (philo->circles != -1)
		if_circle(philo);
	pthread_mutex_unlock(philo->print);
	true_sleep(philo->time_eat);
	gettimeofday(&(philo->tm), NULL);
	philo->start_sleep = philo->tm.tv_sec * 1000 + philo->tm.tv_usec / 1000;
	pthread_mutex_lock(philo->print);
	if (*(philo->is_dead) == 0)
		printf("Chel nomer %i spit. Vremya uhodit %li\n", philo->index, \
		philo->start_sleep - philo->start_time);
	pthread_mutex_unlock(philo->print);
	pthread_mutex_unlock(&(philo->fork[philo->left]));
	pthread_mutex_unlock(&(philo->fork[philo->right]));
	true_sleep(philo->time_sleep);
	ne_hvatilo_mesta(philo);
}

void	*f_check_die(void *args)
{
	t_philo			*philo;
	struct timeval	tm;

	philo = (t_philo *) args;
	while (1)
	{
		usleep(1000);
		gettimeofday(&tm, NULL);
		philo->now_time = tm.tv_sec * 1000 + tm.tv_usec / 1000;
		if (philo->now_time - philo->start_eat > philo->time_die)
		{
			print_die(philo);
			pthread_mutex_unlock(philo->go_go);
			return (NULL);
		}
	}
	return (NULL);
}

void	*func(void *args)
{
	t_philo		*philo;
	pthread_t	check_die;
	int			i;

	philo = (t_philo *) args;
	pthread_create(&check_die, NULL, f_check_die, args);
	if (philo->circles == -1)
	{
		while (1)
			go(philo);
	}
	else
	{
		i = 0;
		while (i < philo->circles)
		{
			go(philo);
			i++;
		}
	}
	return (NULL);
}
