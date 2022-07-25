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

void	*if_circle(void *args)
{
	int		i;
	t_input	*a;

	a = (t_input *) args;
	i = 0;
	while (i < a->num)
	{
		sem_wait(a->if_circle);
		i++;
	}
	free(a->kill_them_all);
	printf("vse processi cikli zavershili\n");
	exit (0);
	return (NULL);
}
