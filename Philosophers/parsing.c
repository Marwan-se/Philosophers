/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msekhsou <msekhsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 11:18:03 by msekhsou          #+#    #+#             */
/*   Updated: 2023/08/30 17:44:46 by msekhsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_for_char(int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	while (i < ac)
	{
		j = 0;
		while (av[i][j] != '\0')
		{
			if (!ft_isdigit(av[i][j]))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	check_0(t_infos *arg)
{
	if (arg->philo_nbr <= 0 || arg->time_to_die <= 0
		|| arg->time_to_eat <= 0 || arg->time_to_sleep <= 0)
		return (1);
	return (0);
}
