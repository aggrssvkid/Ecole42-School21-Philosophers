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

void	init_philo_index(t_input *a, t_philo *philo, int i)
{
	if (i == 0)
	{
		philo[i].left = 0;
		philo[i].right = a->num - 1;
	}
	else
	{
		philo[i].left = i;
		philo[i].right = i - 1;
	}
}

void	init_philo(t_input *a, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < a->num)
	{
		init_philo_index(a, philo, i);
		philo[i].index = i;
		philo[i].time_die = a->time_die;
		philo[i].time_eat = a->time_eat;
		philo[i].time_sleep = a->time_sleep;
		philo[i].fork = a->fork;
		philo[i].start_time = a->start_time;
		philo[i].circles = a->circles;
		philo[i].threads_ended = &(a->threads_ended);
		philo[i].num = a->num;
		philo[i].start_eat = a->start_time;
		philo[i].print = &(a->print);
		philo[i].go_go = &(a->go_go);
		philo[i].end = &(a->end);
		philo[i].is_dead = &(a->is_dead);
		philo[i].take_food = 0;
		i++;
	}
}

void	threads_init(t_input *a, t_philo *philo)
{
	int	i;

	a->threads_ended = 0;
	a->is_dead = 0;
	pthread_mutex_init(&(a->end), NULL);
	pthread_mutex_init(&(a->print), NULL);
	pthread_mutex_init(&(a->go_go), NULL);
	pthread_mutex_lock(&(a->go_go));
	i = 0;
	while (i < a->num)
	{
		pthread_create(a->thread + i, NULL, func, (void *) &(philo[i]));
		pthread_detach(*(a->thread + i));
		i = i + 2;
	}
	i = 1;
	usleep(2000);
	while (i < a->num)
	{
		pthread_create(a->thread + i, NULL, func, (void *) &(philo[i]));
		pthread_detach(*(a->thread + i));
		i = i + 2;
	}
}

void	init_params(t_input *a, char **argv)
{
	int				i;
	struct timeval	tm;

	i = 0;
	a->num = ft_atoi(argv[1]);
	a->time_die = ft_atoi(argv[2]);
	a->time_eat = ft_atoi(argv[3]);
	a->time_sleep = ft_atoi(argv[4]);
	if (argv[5] != 0)
		a->circles = ft_atoi(argv[5]);
	else
		a->circles = -1;
	a->thread = malloc(a->num * sizeof(pthread_t));
	a->fork = malloc(a->num * sizeof(pthread_mutex_t));
	while (i < a->num)
	{
		pthread_mutex_init(a->fork + i, NULL);
		i++;
	}
	gettimeofday(&tm, NULL);
	a->start_time = tm.tv_sec * 1000 + tm.tv_usec / 1000;
}

int	main(int argc, char **argv)
{
	t_input	a;
	t_philo	*philo;

	if (argc != 6 && argc != 5)
	{
		printf("malo argumentov, malo malo argumentov!\n");
		return (0);
	}
	if (validation(argv) == 0)
		return (0);
	init_params(&a, argv);
	philo = malloc(a.num * sizeof(t_philo));
	if (philo == 0)
		return (0);
	init_philo(&a, philo);
	threads_init(&a, philo);
	pthread_mutex_lock(&(a.go_go));
	zachistka(&a, philo);
	return (0);
}
