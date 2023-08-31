/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_infos2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msekhsou <msekhsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 17:38:23 by msekhsou          #+#    #+#             */
/*   Updated: 2023/08/31 20:59:40 by msekhsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	take_forks(t_philosopher *philosopher)
{
	if (philosopher->philo_id % 2)
		usleep(1000);
	pthread_mutex_lock(philosopher->left_fork);
	pthread_mutex_lock(philosopher->write);
	printf("%lld ms philosopher %d has taken a fork\n",
		get_the_time(philosopher->start), philosopher->philo_id + 1);
	pthread_mutex_unlock(philosopher->write);
	pthread_mutex_lock(philosopher->right_fork);
	pthread_mutex_lock(philosopher->write);
	printf("%lld ms philosopher %d has taken a fork\n",
		get_the_time(philosopher->start), philosopher->philo_id + 1);
	printf("%lld ms philosopher %d is eating\n",
		get_the_time(philosopher->start), philosopher->philo_id + 1);
	pthread_mutex_unlock(philosopher->write);
	ft_usleep_test(philosopher->time_to_eat);
	pthread_mutex_unlock(philosopher->left_fork);
	pthread_mutex_unlock(philosopher->right_fork);
}

void	update_last_meal(t_philosopher *philosopher)
{
	pthread_mutex_lock(&philosopher->mutex_last_meal);
	philosopher->last_meal = get_the_time(0);
	pthread_mutex_unlock(&philosopher->mutex_last_meal);
}

void	*routine(void *philo)
{
	t_philosopher	*philosopher;

	philosopher = (t_philosopher *)philo;
	take_forks(philosopher);
	update_last_meal(philosopher);
	if (philosopher->have_time_to_eat)
	{
		pthread_mutex_lock(&philosopher->mutex_eat_num);
		philosopher->num_of_time_to_eat--;
		pthread_mutex_unlock(&philosopher->mutex_eat_num);
	}
	ft_sleep(philosopher);
	return (NULL);
}

void	ft_usleep_test(int time)
{
	long long	t;

	t = get_the_time(0);
	while (get_the_time(0) - t < time)
		usleep(1);
}

int	is_dead(t_philosopher *philo, int num)
{
	int	eat_num;

	while (1)
	{
		if (has_any_philosopher_died(philo, num))
			return (1);
		pthread_mutex_lock(&philo[0].mutex_eat_num);
		eat_num = philo[0].num_of_time_to_eat;
		pthread_mutex_unlock(&philo[0].mutex_eat_num);
		if (philo[0].have_time_to_eat && eat_num < 0)
			return (1);
	}
	return (0);
}
