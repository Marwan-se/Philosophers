/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msekhsou <msekhsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 15:59:50 by msekhsou          #+#    #+#             */
/*   Updated: 2023/04/16 16:00:40 by msekhsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <pthread.h>
#include <stdbool.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct s_philosopher
{
    int id;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int number_of_times_to_eat;
    int meals_eaten;
    unsigned long long last_meal;
    bool is_dead;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    pthread_mutex_t *state_mutex;
} t_philosopher;

unsigned long long get_timestamp_ms();

#endif