/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enoye <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 10:12:37 by enoye             #+#    #+#             */
/*   Updated: 2021/10/17 10:10:35 by enoye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libphilo.h"

static long	summiruem(long sum, const char *str, int znak)
{
	int	check;
	int	isum;

	isum = (int) sum;
	while (*str >= '0' && *str <= '9')
	{
		check = isum;
		isum = isum * 10 + ((*str) - '0');
		str++;
		if (check > isum)
		{
			if (znak == -1)
				return (0);
			return (-1);
		}
	}
	return (isum);
}

int	ft_atoi(const char *str)
{
	long	sum;
	int		znak;

	znak = 1;
	sum = 0;
	while ((*str >= 9 && *str <= 13) || (*str == ' '))
		str++;
	if (*str == '-')
		znak = -1;
	if ((*str == '-') || (*str == '+'))
		str++;
	sum = summiruem((int) sum, str, znak);
	if (znak == -1)
		return (sum * znak);
	return (sum);
}
