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

void	if_circle(t_philo *philo)
{
	(philo->take_food)++;
	if (philo->take_food == philo->circles)
	{
		pthread_mutex_lock(philo->end);
		(*(philo->threads_ended))++;
		printf("POTOKOV ZAVERSHILO CIKLI: %i\n", *(philo->threads_ended));
		if (*(philo->threads_ended) == philo->num)
			pthread_mutex_unlock(philo->go_go);
		pthread_mutex_unlock(philo->end);
	}
}
