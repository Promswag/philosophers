/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 13:12:04 by gbaumgar          #+#    #+#             */
/*   Updated: 2022/10/21 18:40:30 by gbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	philo_fork(t_philo *philo)
{
	// if (philo->meals_eaten == 0 && philo->id % 2 == 0)
	// 	usleep(1000);
	// if (philo->meals_eaten != 0 && atm() - philo->last_meal > (unsigned long) \
	// 	philo->rules->die - philo->rules->eat - philo->rules->sleep - 1)
	// 	usleep(100);
	if (philo_check(philo))
		return (-1);
	sem_wait(philo->rules->forks);
	sem_wait(philo->rules->checker);
	printf("%6lu %d has taken a fork\n", \
		atm() - philo->rules->time, philo->id);
	sem_post(philo->rules->checker);
	return (0);
}

int	philo_eat(t_philo *philo)
{
	if (philo_check(philo))
		return (-1);
	sem_wait(philo->rules->checker);
	printf("%6lu %d is eating\n", \
		atm() - philo->rules->time, philo->id);
	philo->last_meal = atm();
	philo->meals_eaten++;
	sem_post(philo->rules->checker);
	ft_sleep(philo->rules->eat);
	sem_post(philo->rules->forks);
	sem_post(philo->rules->forks);
	return (0);
}

int	philo_sleep(t_philo *philo)
{
	if (philo_check(philo))
		return (-1);
	sem_wait(philo->rules->checker);
	printf("%6lu %d is sleeping\n", \
		atm() - philo->rules->time, philo->id);
	sem_post(philo->rules->checker);
	ft_sleep(philo->rules->sleep);
	return (0);
}

int	philo_think(t_philo *philo)
{
	if (philo_check(philo))
		return (-1);
	sem_wait(philo->rules->checker);
	printf("%6lu %d is thinking\n", \
		atm() - philo->rules->time, philo->id);
	sem_post(philo->rules->checker);
	return (0);
}

void	philosopher(t_philo *philo)
{
	philo->last_meal = atm();
	philo->meals_eaten = 0;
	pthread_create(&philo->thread, NULL, philo_death, philo);
	pthread_detach(philo->thread);
	while (1)
	{
		if (philo_fork(philo) || philo_fork(philo) || philo_eat(philo) || \
			philo_sleep(philo) || philo_think(philo))
			break ;
	}
	pthread_join(philo->thread, NULL);
	exit (0);
}
