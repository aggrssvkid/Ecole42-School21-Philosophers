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

int	is_int(char **argv)
{
	int		checker;
	char	**kek;

	kek = argv;
	kek++;
	while (*kek != 0)
	{
		checker = ft_atoi(*kek);
		if (checker == -1)
		{
			printf("Slishkom bolshoe chislo, durik!\n");
			return (0);
		}
		kek++;
	}
	return (1);
}

int	validation(char **argv)
{
	char	*saver;

	argv++;
	while (*argv != 0)
	{
		if (**argv == '0')
		{
			printf("Clown, tolko ne nulik\n");
			return (0);
		}
		saver = *argv;
		while (**argv >= '0' && **argv <= '9')
			(*argv)++;
		if (**argv != '\0')
		{
			printf("Nu etot focus ne proydet!\n");
			return (0);
		}
		*argv = saver;
		argv++;
	}
	if (is_int(argv) == 0)
		return (0);
	return (1);
}
