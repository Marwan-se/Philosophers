/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msekhsou <msekhsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 16:00:49 by msekhsou          #+#    #+#             */
/*   Updated: 2023/08/30 17:41:09 by msekhsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	mutex_destroy(pthread_mutex_t *fork, int number)
{
	int	i;

	i = 0;
	while (i < number)
	{
		pthread_mutex_destroy(&fork[i]);
		i++;
	}
}

int	is_eating(t_philosopher *philo, int number)
{
	int	i;

	i = 0;
	while (i < number)
	{
		if (philo[i].num_of_time_to_eat == 0)
		{
			return (1);
		}
		i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_infos			arg;
	t_philosopher	*infos;

	if ((ac != 5 && ac != 6) || check_for_char(ac, av))
		return (printf("args error\n"), 1);
	args_infos(&arg, ac, av);
	if (check_0(&arg))
		return (printf("args m error\n"), 1);
	infos = malloc(sizeof(t_philosopher) * arg.philo_nbr);
	if (!infos)
		return (printf("malloc error"), 1);
	if (init_infos(infos, arg, ac))
		return (1);
	philo_routine(infos, arg.philo_nbr);
}
