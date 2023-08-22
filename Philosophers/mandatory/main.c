/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msekhsou <msekhsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 16:00:49 by msekhsou          #+#    #+#             */
/*   Updated: 2023/08/18 11:47:36 by msekhsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int ac, char **av)
{
	t_infos			arg;
	t_philosopher	*infos;
	
	infos = malloc(sizeof(t_philosopher) * arg.philo_nbr);
	if (!infos)
		return (0);
	if ((ac != 5 && ac != 6) || check_for_char(ac, av))
		return(printf("args error"), 1);
	args_infos(&arg, ac, av);
	init_infos(infos, arg, ac);
	philo_routine(infos, arg.philo_nbr);
}
