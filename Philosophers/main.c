/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msekhsou <msekhsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 16:00:49 by msekhsou          #+#    #+#             */
/*   Updated: 2023/08/31 21:01:49 by msekhsou         ###   ########.fr       */
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

long long	get_the_time(long long beginning_time)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000) - beginning_time);
}

void	*ft_sleep(void *philo)
{
	t_philosopher	*philosophers;

	philosophers = (t_philosopher *) philo;
	pthread_mutex_lock(philosophers->write);
	printf("%lld ms philosopher %d is sleeping\n",
		get_the_time(philosophers->start), philosophers->philo_id + 1);
	pthread_mutex_unlock(philosophers->write);
	usleep(philosophers->time_to_sleep * 1000);
	pthread_mutex_lock(philosophers->write);
	printf("%lld ms philosopher %d is thinking\n",
		get_the_time(philosophers->start), philosophers->philo_id + 1);
	pthread_mutex_unlock(philosophers->write);
	routine(philosophers);
	return (NULL);
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
		return (printf("args error\n"), 1);
	infos = malloc(sizeof(t_philosopher) * arg.philo_nbr);
	if (!infos)
		return (printf("malloc error"), 1);
	if (init_infos(infos, arg, ac))
		return (1);
	philo_routine(infos, arg.philo_nbr);
}
