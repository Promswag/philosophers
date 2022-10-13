/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 13:12:04 by gbaumgar          #+#    #+#             */
/*   Updated: 2022/10/13 14:27:22 by gbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	philo_check(t_philo *philo)
{
	pthread_mutex_lock(&philo->rules->lock);
	if (atm() >= philo->last_meal + philo->rules->die && \
		!philo->ded && !philo->rules->finish)
	{
		printf("%lu %d has died\n", \
			atm() - philo->rules->time, philo->id);
		philo->ded = 1;
		philo->rules->finish = 1;
		pthread_mutex_unlock(&philo->rules->lock);
		return (1);
	}
	if (philo->rules->finish || philo->ded || \
		(philo->meals_eaten == philo->rules->full && philo->rules->full != 0))
	{
		pthread_mutex_unlock(&philo->rules->lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->rules->lock);
	return (0);
}

// void	philo_fork(t_philo *philo)
// {
// 	int	forks;

// 	forks = 0;
// 	while (forks != 2 && !philo_check(philo))
// 	{
// 		pthread_mutex_lock(&philo->left_fork);
// 		if (philo->fork_state)
// 		{
// 			philo->fork_state--;
// 			printf("%lu %d has taken a fork\n", \
// 			atm() - philo->rules->time, philo->id);
// 			forks++;
// 		}
// 		pthread_mutex_unlock(&philo->left_fork);
// 		pthread_mutex_lock(&philo->next_philo->left_fork);
// 		if (philo->next_philo->fork_state)
// 		{
// 			philo->next_philo->fork_state--;
// 			printf("%lu %d has taken a fork\n", \
// 			atm() - philo->rules->time, philo->id);
// 			forks++;
// 		}
// 		pthread_mutex_unlock(&philo->next_philo->left_fork);
// 	}
// }

int	philo_fork(t_philo *philo, int *status, pthread_mutex_t *fork)
{
	while (!philo_check(philo))
	{
		pthread_mutex_lock(fork);
		if (*status)
		{
			(*status)--;
			pthread_mutex_lock(&philo->rules->lock);
			if (!philo->rules->finish)
				printf("%lu %d has taken a fork\n", \
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
		printf("%lu %d is eating\n", \
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
		printf("%lu %d is sleeping\n", \
			atm() - philo->rules->time, philo->id);
	pthread_mutex_unlock(&philo->rules->lock);
	ft_sleep(philo->rules->sleep);
	return (0);
}

int	philo_think(t_philo *philo)
{
	if (philo_check(philo))
		return (-1);
	pthread_mutex_lock(&philo->rules->lock);
	if (!philo->rules->finish)
		printf("%lu %d is thinking\n", \
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
		if (philo->id % 2)
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
