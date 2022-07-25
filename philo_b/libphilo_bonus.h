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

#ifndef LIBPHILO_BONUS_H
# define LIBPHILO_BONUS_H

# include <sys/time.h>
# include <signal.h>
# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <semaphore.h>

typedef struct s_philo
{
	int				index;
	int				circles;
	int				*threads_ended;
	int				num;
	int				take_food;
	long			vilka_time;
	long			time_die;
	long			time_eat;
	long			time_sleep;
	long			start_time;
	long			start_eat;
	long			start_sleep;
	long			start_think;
	long			now_time;
	sem_t			*sema;
	sem_t			*print;
	sem_t			*dead;
	sem_t			*if_circle;
	struct timeval	tm;
	pid_t			pid;
	pthread_t		checker;
}	t_philo;

typedef struct s_input
{
	int				num;
	int				circles;
	int				threads_ended;
	int				is_dead;
	int				i;
	char			**sema_names;
	long			time_die;
	long			time_eat;
	long			time_sleep;
	long			start_time;
	struct timeval	tm;
	t_philo			*kill_them_all;
	sem_t			*sema;
	sem_t			*print;
	sem_t			*dead;
	sem_t			*if_circle;
	pthread_t		circle;
}	t_input;

int		ft_atoi(const char *str);
void	*func(void *args);
void	true_sleep(long time);
int		validation(char **argv);
int		go(t_philo *philo);
int		kill_process(t_input *a);
void	*check_die(void *args);
void	*if_circle(void *args);
void	tri_v_odnom(t_input *a);

#endif