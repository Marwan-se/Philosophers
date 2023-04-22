#include "philosophers.h"

void	args_infos(t_philosopher *info, int ac, char **av)
{
	if (ac == 5 || ac == 6)
	{
		info->philo_nbr = ft_atoi(av[1]);
		info->time_to_die = ft_atoi(av[2]);
		info->time_to_eat = ft_atoi(av[3]);
		info->time_to_sleep = ft_atoi(av[4]);
		if (ac == 6)
			info->number_of_time_to_eat = ft_atoi(av[5]);
	}
}