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

void	zachistka(t_input *a, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < a->num)
	{
		pthread_mutex_destroy(a->fork + i);
		i++;
	}
	free(a->fork);
	free(a->thread);
	free(philo);
	pthread_mutex_destroy(&(a->go_go));
	pthread_mutex_destroy(&(a->end));
	pthread_mutex_destroy(&(a->print));
}
