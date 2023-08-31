/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_infos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msekhsou <msekhsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 11:17:35 by msekhsou          #+#    #+#             */
/*   Updated: 2023/08/31 17:07:55 by msekhsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	args_infos(t_infos *info, int ac, char **av)
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

int	init_infos(t_philosopher *philo, t_infos arg, int ac)
{
	int	i;

	i = 0;
	while (i < arg.philo_nbr)
	{
		philo[i].philo_id = i;
		philo[i].time_to_sleep = arg.time_to_sleep;
		philo[i].time_to_eat = arg.time_to_eat;
		philo[i].duration = arg.time_to_die;
		philo[i].remaining_time = arg.time_to_die;
		if (ac == 6)
		{
			philo[i].have_time_to_eat = true;
			philo[i].num_of_time_to_eat = arg.number_of_time_to_eat;
			if (arg.number_of_time_to_eat == 0)
				return (1);
		}
		else
			philo[i].have_time_to_eat = false;
		i++;
	}
	return (0);
}

void philo_routine(t_philosopher *philo, int number)
{
    pthread_mutex_t *fork;
    pthread_mutex_t *write;
    int i;

    i = 0;
    fork = malloc(sizeof(pthread_mutex_t) * number);
    write = malloc(sizeof(pthread_mutex_t));
   	pthread_mutex_init(write, NULL);
    if (!fork)
        return;
    while (i < number)
	{
        philo[i].write = write;
        pthread_mutex_init(&fork[i], NULL);
   		pthread_mutex_init(&philo[i].mutex_last_meal, NULL);
   		pthread_mutex_init(&philo[i].mutex_eat_num, NULL);
        philo[i].left_fork = &fork[i];
        philo[i].right_fork = &fork[(i + 1) % number];
        i++;
    }
    i = 0;
    start_the_routine(philo, number);
    while (i < number)
	{
        pthread_create(&philo[i].philo_thread, NULL, &routine, &philo[i]);
        i++;
    }
    if (is_death(philo, number) && philo[0].num_of_time_to_eat == 0)
	{
        free(fork);
        pthread_mutex_destroy(write);
        free(write);
        mutex_destroy(fork, number);
        return;
    }
}

void	start_the_routine(t_philosopher *philo, int number)
{
	int			i;
	long long	start_time;

	i = 0;
	start_time = get_the_time(0);
	while (i < number)
	{
		philo[i].last_meal = start_time;
		philo[i].start = start_time;
		i++;
	}
}
