/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 15:22:40 by gbaumgar          #+#    #+#             */
/*   Updated: 2022/10/21 17:15:48 by gbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long unsigned	atm(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((long unsigned)time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	ft_sleep(long delay)
{
	long unsigned	time;

	time = atm();
	usleep(delay * 900);
	while (1)
	{
		if (atm() >= time + delay)
			break ;
		usleep(100);
	}
}

int	philo_check(t_philo *philo)
{
	pthread_mutex_lock(&philo->rules->lock);
	if (!philo->rules->finish && atm() >= philo->last_meal + philo->rules->die)
	{
		printf("%6lu %d has died\n", \
			atm() - philo->rules->time, philo->id);
		philo->rules->finish = 1;
		pthread_mutex_unlock(&philo->rules->lock);
		return (1);
	}
	if (philo->rules->finish || philo->meals_eaten == philo->rules->full)
	{
		pthread_mutex_unlock(&philo->rules->lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->rules->lock);
	return (0);
}

void	philo_end(t_philo *philo, t_rules rules)
{
	while (rules.number--)
	{
		if (philo + rules.number)
		{
			free(philo[rules.number].thread);
			pthread_mutex_destroy(&philo[rules.number].left_fork);
			pthread_mutex_destroy(&philo[rules.number].lock);
		}
	}
	pthread_mutex_destroy(&rules.lock);
	if (philo)
		free(philo);
}
