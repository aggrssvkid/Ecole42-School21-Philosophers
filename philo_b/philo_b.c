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

int	sema_init(t_input *a)
{
	sem_unlink("fork");
	sem_unlink("print");
	sem_unlink("dead");
	sem_unlink("if_circle");
	a->sema = sem_open("fork", O_CREAT | O_EXCL, 0644, a->num);
	a->print = sem_open("print", O_CREAT | O_EXCL, 0644, 1);
	a->dead = sem_open("dead", O_CREAT | O_EXCL, 0644, 0);
	a->if_circle = sem_open("if_circle", O_CREAT | O_EXCL, 0644, 0);
	if (a->sema == SEM_FAILED || a->print == SEM_FAILED || \
		a->dead == SEM_FAILED || a->if_circle == SEM_FAILED)
		return (0);
	return (1);
}

void	init_philo(t_input *a, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < a->num)
	{
		philo[i].index = i;
		philo[i].time_die = a->time_die;
		philo[i].time_eat = a->time_eat;
		philo[i].time_sleep = a->time_sleep;
		philo[i].circles = a->circles;
		philo[i].start_time = a->start_time;
		philo[i].sema = a->sema;
		philo[i].print = a->print;
		philo[i].dead = a->dead;
		philo[i].start_eat = a->start_time;
		philo[i].take_food = 0;
		philo[i].if_circle = a->if_circle;
		i++;
	}
}

int	init_params(t_input *a, char **argv)
{
	a->num = ft_atoi(argv[1]);
	a->time_die = ft_atoi(argv[2]);
	a->time_eat = ft_atoi(argv[3]);
	a->time_sleep = ft_atoi(argv[4]);
	if (argv[5] != 0)
		a->circles = ft_atoi(argv[5]);
	else
		a->circles = -1;
	if (sema_init(a) == 0)
		return (0);
	gettimeofday(&(a->tm), NULL);
	a->start_time = a->tm.tv_sec * 1000 + a->tm.tv_usec / 1000;
	return (1);
}

int	init_process(t_input *a, t_philo *philo)
{
	a->i = 0;
	while (a->i < a->num)
	{
		philo[a->i].pid = fork();
		if (philo[a->i].pid == 0)
		{
			usleep(200);
			if (pthread_create(&(philo[a->i].checker), NULL, \
			check_die, (void *) &(philo[a->i])) != 0)
				return (0);
			pthread_detach(philo[a->i].checker);
			if (philo[a->i].circles == -1)
			{
				while (1)
					go(&(philo[a->i]));
			}
			else
			{
				while (philo[a->i].take_food != philo[a->i].circles)
					go(&(philo[a->i]));
			}
		}
		a->i++;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_input	a;
	t_philo	*philo;

	if (argc != 5 && argc != 6)
	{
		printf("nevernoe chislo argumentov\n");
		return (0);
	}
	if (validation(argv) == 0)
		return (0);
	if (init_params(&a, argv) == 0)
		exit (0);
	philo = malloc(a.num * sizeof(t_philo));
	if (philo == 0)
		return (0);
	a.kill_them_all = philo;
	init_philo(&a, philo);
	if (init_process(&a, philo) == 0)
		exit (0);
	if (a.circles != -1)
		pthread_create(&(a.circle), NULL, if_circle, (void *) &a);
	sem_wait(a.dead);
	tri_v_odnom(&a);
	return (0);
}
