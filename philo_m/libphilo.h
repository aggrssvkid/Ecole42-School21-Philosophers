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

#ifndef LIBPHILO_H
# define LIBPHILO_H

# include <sys/time.h>
# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct s_input
{
	int				num;
	int				circles;
	int				threads_ended;
	int				is_dead;
	long			time_die;
	long			time_eat;
	long			time_sleep;
	long			start_time;
	pthread_t		*thread;
	pthread_mutex_t	*fork;
	pthread_mutex_t	go_go;
	pthread_mutex_t	print;
	pthread_mutex_t	end;
}	t_input;

typedef struct s_philo
{
	int				index;
	int				right;
	int				left;
	int				*dead;
	int				circles;
	int				*threads_ended;
	int				num;
	int				*is_dead;
	int				take_food;
	long			time_left;
	long			time_right;
	long			time_die;
	long			time_eat;
	long			time_sleep;
	long			start_time;
	long			start_eat;
	long			start_sleep;
	long			start_think;
	long			now_time;
	struct timeval	tm;
	pthread_mutex_t	*fork;
	pthread_mutex_t	*print;
	pthread_mutex_t	*end;
	pthread_mutex_t	*go_go;
}	t_philo;

int		ft_atoi(const char *str);
void	*func(void *args);
void	true_sleep(long time);
void	if_circle(t_philo *philo);
int		validation(char **argv);
void	print_die(t_philo *philo);
void	zachistka(t_input *a, t_philo *philo);

#endif