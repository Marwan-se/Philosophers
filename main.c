/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msekhsou <msekhsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 16:00:49 by msekhsou          #+#    #+#             */
/*   Updated: 2023/04/16 16:02:11 by msekhsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void *philosopher_thread(void *arg)
{
    t_philosopher *philosopher = (t_philosopher *)arg;

    while (!philosopher->is_dead && (philosopher->meals_eaten < philosopher->number_of_times_to_eat || philosopher->number_of_times_to_eat == -1))
    {
        // Take forks
        pthread_mutex_lock(philosopher->left_fork);
        pthread_mutex_lock(philosopher->right_fork);
        printf("%llu %d has taken a fork\n", get_timestamp_ms(), philosopher->id);

        // Eating
        printf("%llu %d is eating\n", get_timestamp_ms(), philosopher->id);
        usleep(philosopher->time_to_eat * 1000);
        philosopher->meals_eaten++;
        philosopher->last_meal = get_timestamp_ms();

        // Release forks
        pthread_mutex_unlock(philosopher->left_fork);
        pthread_mutex_unlock(philosopher->right_fork);

        // Sleeping
        printf("%llu %d is sleeping\n", get_timestamp_ms(), philosopher->id);
        usleep(philosopher->time_to_sleep * 1000);

        // Thinking
        printf("%llu %d is thinking\n", get_timestamp_ms(), philosopher->id);
    }

    return NULL;
}

unsigned long long get_timestamp_ms()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

int main(int argc, char **argv)
{
    if (argc < 5 || argc > 6)
    {
        printf("Usage: %s number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n", argv[0]);
        return 1;
    }

    int num_philosophers = atoi(argv[1]);
    int time_to_die = atoi(argv[2]);
    int time_to_eat = atoi(argv[3]);
    int time_to_sleep = atoi(argv[4]);
    int num_times_eat = argc == 6 ? atoi(argv[5]) : -1;

    pthread_t *threads = malloc(num_philosophers * sizeof(pthread_t));
    t_philosopher *philosophers = malloc(num_philosophers * sizeof(t_philosopher));
    pthread_mutex_t *forks = malloc(num_philosophers * sizeof(pthread_mutex_t));

    for (int i = 0; i < num_philosophers; i++)
    {
        pthread_mutex_init(&forks[i], NULL);
    }

    for (int i = 0; i < num_philosophers; i++)
    {
        philosophers[i].id = i + 1;
        philosophers[i].time_to_die = time_to_die;
        philosophers[i].time_to_eat = time_to_eat;
        philosophers[i].time_to_sleep = time_to_sleep;
        philosophers[i].number_of_times_to_eat = num_times_eat;
        philosophers[i].meals_eaten = 0;
        philosophers[i].last_meal = get_timestamp_ms();
        philosophers[i].is_dead = false;
        philosophers[i].left_fork = &forks[i];
        philosophers[i].right_fork = &forks[(i + 1) % num_philosophers];

        pthread_create(&threads[i], NULL, philosopher_thread, &philosophers[i]);
    }

    for (int i = 0; i < num_philosophers; i++)
    {
        pthread_join(threads[i], NULL);
    }

    for (int i = 0; i < num_philosophers; i++)
    {
        pthread_mutex_destroy(&forks[i]);
    }

    free(threads);
    free(philosophers);
    free(forks);

    return 0;
}