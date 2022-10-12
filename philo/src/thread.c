/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 13:12:04 by gbaumgar          #+#    #+#             */
/*   Updated: 2022/10/12 16:52:14 by gbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philo_fork(t_philo *philo)
{
	if (philo->id % 2 && philo->next_philo->id != 1)
	{
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(philo->rules->lock);
		printf("%lo %d has taken a fork\n", \
			atm() - philo->rules->time, philo->id);
		printf("%lo %d has taken a fork\n", \
			atm() - philo->rules->time, philo->id);
		pthread_mutex_unlock(philo->rules->lock);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->rules->lock);
		printf("%lo %d has taken a fork\n", \
			atm() - philo->rules->time, philo->id);
		printf("%lo %d has taken a fork\n", \
			atm() - philo->rules->time, philo->id);
		pthread_mutex_unlock(philo->rules->lock);
	}
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->rules->lock);
	printf("%lo %d is eating\n", \
		atm() - philo->rules->time, philo->id);
	pthread_mutex_unlock(philo->rules->lock);
	usleep(philo->rules->eat * 1000);
	philo->last_meal = atm();
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	philo_sleep(t_philo *philo)
{
	pthread_mutex_lock(philo->rules->lock);
	printf("%lo %d is sleeping\n", \
		atm() - philo->rules->time, philo->id);
	pthread_mutex_unlock(philo->rules->lock);
	usleep(philo->rules->sleep * 1000);
}

void	philo_think(t_philo *philo)
{
	pthread_mutex_lock(philo->rules->lock);
	printf("%lo %d is thinking\n", \
		atm() - philo->rules->time, philo->id);
	pthread_mutex_unlock(philo->rules->lock);
}

void	*philosopher(void *args)
{
	t_philo			*philo;

	philo = args;
	philo->last_meal = atm();
	philo->meals_eaten = 0;
	philo->ded = 0;
	while (69)
	{
		philo_fork(philo);
		usleep(500);
		philo_eat(philo);
		usleep(500);
		philo_sleep(philo);
		usleep(500);
		philo_think(philo);
		usleep(500);
	}
	return (NULL);
}
