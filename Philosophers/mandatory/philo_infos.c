/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_infos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msekhsou <msekhsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 11:17:35 by msekhsou          #+#    #+#             */
/*   Updated: 2023/08/20 12:12:33 by msekhsou         ###   ########.fr       */
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
		i++;
	}
		if (ac == 6)
		{
			philo[i].have_time_to_eat = true;
			philo[i].num_of_time_to_eat = arg.number_of_time_to_eat;
		}
		else
			philo[i].have_time_to_eat = false;
}

void cr_mutex_init(pthread_mutex_t *mutex, t_philosopher *philos, int number,
                      pthread_mutex_t *write)
{
    int i;

	i = 0;
    while (i < number)
	{
        philos[i].write = write;
        pthread_mutex_init(&mutex[i], NULL);
        philos[i].left_fork = &mutex[i % number];
        philos[i].right_fork = &mutex[(i + 1) % number];
        i++;
    }
}

void	philo_routine(t_philosopher *philo, int number)
{
	
	pthread_mutex_t	*fork;
	pthread_mutex_t	write;
	int				i;

	i = 0;
	fork = malloc(sizeof(pthread_mutex_t) * number);
	if (!fork)
		return ;
	cr_mutex_init(fork, philo, number, &write);
	start_the_routine(philo, number);
	while (i < number)
	{
		pthread_create(&philo[i].philo_thread, NULL, &routine, &philo[i]);
		i++;
	}
	if (is_death(philo, number))
	{
		free(fork);
		mutex_destroy(fork, number);
		return ;
	}
}

void	*routine(void *philo)
{
	t_philosopher	*philosopher;

	philosopher = (t_philosopher *) philo;
	if (philosopher->philo_id % 2)
		usleep(1000);
	pthread_mutex_lock(philosopher->left_fork);
	pthread_mutex_lock(philosopher->write);
	printf("%lld ms philosopher %d has FIRST taken a fork\n",
		get_the_time(philosopher->start), philosopher->philo_id);
	pthread_mutex_unlock(philosopher->write);
	pthread_mutex_lock(philosopher->right_fork);
	pthread_mutex_lock(philosopher->write);
	printf("%lld ms philosopher %d has SECOND taken a fork\n",
		get_the_time(philosopher->start), philosopher->philo_id);
	printf("%lld ms philosopher %d is eating\n",
		get_the_time(philosopher->start), philosopher->philo_id);
	pthread_mutex_unlock(philosopher->write);
	usleep(philosopher->time_to_eat * 1000);
	pthread_mutex_unlock(philosopher->left_fork);
	pthread_mutex_unlock(philosopher->right_fork);
	philosopher->last_meal = get_the_time(0);
	if (philosopher->have_time_to_eat)
		philosopher->num_of_time_to_eat--;
	ft_sleep(philosopher);
	return (NULL);
}


void	*ft_sleep(void *philo)
{
	t_philosopher	*philosophers;

	philosophers = (t_philosopher *) philo;
	pthread_mutex_lock(philosophers->write);
	printf("%lld ms philosopher %d is sleeping\n",
		get_the_time(philosophers->start), philosophers->philo_id);
	pthread_mutex_unlock(philosophers->write);
	usleep(philosophers->time_to_sleep * 1000);
	pthread_mutex_lock(philosophers->write);
	printf("%lld ms philosopher %d is thinking\n",
		get_the_time(philosophers->start), philosophers->philo_id);
	pthread_mutex_unlock(philosophers->write);
	routine(philosophers);
	return (NULL);
}


void start_the_routine(t_philosopher *philo, int number)
{
    int i;

	i = 0;
    long long start_time = get_the_time(0);
    while (i < number)
	{
        philo[i].last_meal = start_time;	
        philo[i].start = start_time;
        i++;
    }
}


long long get_the_time(long long beginning_time)
{
    struct timeval time;

    gettimeofday(&time, NULL);
    return ((time.tv_sec * 1000) + (time.tv_usec / 1000) - beginning_time);
}

int	is_death(t_philosopher *philo, int num)
{
	int	i;

	i = 0;
	while (1)
	{
		i = 0;
		while (i < num)
		{
			if (philo[i % num].duration
				< get_the_time(philo[i % num].last_meal))
			{
				pthread_mutex_lock(philo[i].write);
				printf("%lld ms philosopher %d died\n",
					get_the_time(philo[i % num].start), philo[i % num].philo_id);
				return (1);
			}
			i++;
		}
		if (philo->have_time_to_eat && is_eating(philo, num))
			return (1);
	}
	return (0);
}

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
		if (philo[i].num_of_time_to_eat)
			return (0);
		i++;
	}
	return (1);
}