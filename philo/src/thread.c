/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 13:12:04 by gbaumgar          #+#    #+#             */
/*   Updated: 2022/10/21 17:27:06 by gbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	philo_fork(t_philo *philo, int *status, pthread_mutex_t *fork)
{
	if (philo->meals_eaten == 0 && philo->id % 2 == 0)
		ft_sleep(1);
	if (philo->id % 2 && philo->next_philo->id == 1)
		ft_sleep(1);
	if (philo->meals_eaten != 0 && atm() - philo->last_meal > (unsigned long) \
		philo->rules->die - philo->rules->eat - philo->rules->sleep - 1)
		usleep(100);
	while (!philo_check(philo))
	{
		pthread_mutex_lock(fork);
		if (*status)
		{
			(*status)--;
			pthread_mutex_lock(&philo->rules->lock);
			if (!philo->rules->finish)
				printf("%6lu %d has taken a fork\n", \
					atm() - philo->rules->time, philo->id);
			pthread_mutex_unlock(&philo->rules->lock);
			pthread_mutex_unlock(fork);
			return (0);
		}
		pthread_mutex_unlock(fork);
	}
	return (-1);
}

int	philo_eat(t_philo *philo)
{
	if (philo_check(philo))
		return (-1);
	pthread_mutex_lock(&philo->rules->lock);
	if (!philo->rules->finish)
		printf("%6lu %d is eating\n", \
			atm() - philo->rules->time, philo->id);
	pthread_mutex_unlock(&philo->rules->lock);
	philo->last_meal = atm();
	ft_sleep(philo->rules->eat);
	philo->meals_eaten++;
	pthread_mutex_lock(&philo->left_fork);
	pthread_mutex_lock(&philo->next_philo->left_fork);
	philo->fork_state++;
	philo->next_philo->fork_state++;
	pthread_mutex_unlock(&philo->left_fork);
	pthread_mutex_unlock(&philo->next_philo->left_fork);
	return (0);
}

int	philo_sleep(t_philo *philo)
{
	if (philo_check(philo))
		return (-1);
	pthread_mutex_lock(&philo->rules->lock);
	if (!philo->rules->finish)
		printf("%6lu %d is sleeping\n", \
			atm() - philo->rules->time, philo->id);
	pthread_mutex_unlock(&philo->rules->lock);
	if (philo->rules->sleep + philo->rules->eat > philo->rules->die)
		ft_sleep(philo->rules->die - philo->rules->sleep);
	else
		ft_sleep(philo->rules->sleep);
	return (0);
}

int	philo_think(t_philo *philo)
{
	if (philo_check(philo))
		return (-1);
	pthread_mutex_lock(&philo->rules->lock);
	if (!philo->rules->finish)
		printf("%6lu %d is thinking\n", \
			atm() - philo->rules->time, philo->id);
	pthread_mutex_unlock(&philo->rules->lock);
	return (0);
}

void	*philosopher(void *args)
{
	t_philo			*philo;

	philo = args;
	philo->last_meal = atm();
	philo->meals_eaten = 0;
	while (1)
	{
		if (philo->id % 2 && philo->next_philo->id != 1)
		{
			if (philo_fork(philo, &philo->fork_state, &philo->left_fork) || \
				philo_fork(philo, &philo->next_philo->fork_state, \
				&philo->next_philo->left_fork))
				return (NULL);
		}
		else
		{
			if (philo_fork(philo, &philo->next_philo->fork_state, \
				&philo->next_philo->left_fork) || \
				philo_fork(philo, &philo->fork_state, &philo->left_fork))
				return (NULL);
		}
		if (philo_eat(philo) || philo_sleep(philo) || philo_think(philo))
			return (NULL);
	}
	return (NULL);
}
