/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 13:12:04 by gbaumgar          #+#    #+#             */
/*   Updated: 2022/10/12 17:56:10 by gbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philo_fork(t_philo *philo)
{
	// if (philo->id % 2 && philo->next_philo->id != 1)
	// {
		pthread_mutex_lock(&philo->left_fork);
		printf("%lu %d has taken a fork\n", \
			atm() - philo->rules->time, philo->id);
		pthread_mutex_lock(&philo->next_philo->left_fork);
		printf("%lu %d has taken a fork\n", \
			atm() - philo->rules->time, philo->id);
	// }
	// else
	// {
	// 	pthread_mutex_lock(&philo->next_philo->left_fork);
	// 	printf("%lu %d has taken a fork\n", \
	// 		atm() - philo->rules->time, philo->id);
	// 	pthread_mutex_lock(&philo->left_fork);
	// 	printf("%lu %d has taken a fork\n", \
	// 		atm() - philo->rules->time, philo->id);
	// }
}

void	philo_eat(t_philo *philo)
{
	printf("%lu %d is eating\n", \
		atm() - philo->rules->time, philo->id);
	slip(philo->rules->eat);
	philo->last_meal = atm();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->next_philo->left_fork);
	pthread_mutex_unlock(&philo->left_fork);
}

void	philo_sleep(t_philo *philo)
{
	printf("%lu %d is sleeping\n", \
		atm() - philo->rules->time, philo->id);
	slip(philo->rules->sleep);
}

void	philo_think(t_philo *philo)
{
	printf("%lu %d is thinking\n", \
		atm() - philo->rules->time, philo->id);
}

void	*philosopher(void *args)
{
	t_philo			*philo;

	philo = args;
	printf("%d - START\n", philo->id);
	philo->last_meal = atm();
	philo->meals_eaten = 0;
	philo->ded = 0;
	while (1)
	{
		philo_fork(philo);
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	printf("%d - END\n", philo->id);
	return (NULL);
}
