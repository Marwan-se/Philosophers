/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_infos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msekhsou <msekhsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 11:17:35 by msekhsou          #+#    #+#             */
/*   Updated: 2023/05/23 19:25:57 by msekhsou         ###   ########.fr       */
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

void	init_infos(t_philosopher *philo, t_infos arg, int ac)
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
	}
		if (ac == 6)
		{
			philo[i].have_time_to_eat = true;
			philo[i].num_of_time_to_eat = arg.number_of_time_to_eat;
		}
		else
			philo[i].have_time_to_eat = false;
		i++;
}

void	cr_mutex_init(pthread_mutex_t *mutex, t_philosopher *philos,
		int number, pthread_mutex_t *write)
{
	int	i;

	i = 0;
	while (i < number)
	{
		philos[i].print = write;
		pthread_mutex_init(&mutex[i], NULL);
		i++;
	}
	i = 0;
	while (i < number)
	{
		philos[i].left_fork = &mutex[i % number];
		philos[i].right_fork = &mutex[(i + 1) % number];
		i++;
	}
	
}
void	cr_mutex_init(pthread_mutex_t *mutex, t_philosopher *philos,
		int number, pthread_mutex_t *write)
{
    int i;

	i = 0;
    while (i < number)
	{
        philos[i].print = write;
        i++;
    }
    i = 0;
    while (i < number)
	{
        if (pthread_mutex_init(&mutex[i], NULL) != 0)
            exit(1);
        i++;
    }
    i = 0;
    while (i < number)
	{
        philos[i].left_fork = &mutex[i % number];
        philos[i].right_fork = &mutex[(i + 1) % number];
        i++;
    }
}


void	philo_routine(t_philosopher *philo, int number)
{
	pthread_mutex_t	*fork;
	pthread_mutex_t	print;
	int				i;

	i = 0;
	fork = malloc(sizeof(pthread_mutex_t) * number);
	if (!fork)
		return ;
	cr_mutex_init(fork, philo, number, &print);
	
}
void start_the_routine(t_philosopher *philo, int number)
{
    int i = 0;
    long long start_time = get_the_time(0);

    while (i < number)
	{
        philo[i].start = start_time;
        philo[i].last_meal = start_time;
        i++;
    }
}

size_t	get_the_time(void)
{
	struct timeval	time;
	long long		milliseconds;

	gettimeofday(&time, NULL);
	milliseconds = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (milliseconds);
}