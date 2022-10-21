/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 15:22:40 by gbaumgar          #+#    #+#             */
/*   Updated: 2022/10/21 18:45:01 by gbaumgar         ###   ########.fr       */
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
	if (philo->meals_eaten == philo->rules->full)
		return (1);
	return (0);
}

void	philo_end(t_philo *philo, t_rules rules)
{
	int	i;
	int	err;
	int	stat_loc;

	i = -1;
	err = 1;
	while (err > 0)
	{
		err = waitpid(-1, &stat_loc, 0);
		if (stat_loc == 65280 || stat_loc == 9)
			break ;
	}
	while (++i < rules.number)
		kill(philo[i].pid, SIGKILL);
	sem_close(philo->rules->forks);
	sem_unlink("/forks");
	sem_close(philo->rules->checker);
	sem_unlink("/checker");
	if (philo)
		free(philo);
}

void	*philo_death(void *arg)
{
	t_philo	*philo;

	philo = arg;
	while (1)
	{
		sem_wait(philo->rules->checker);
		if (philo->meals_eaten == philo->rules->full)
		{
			sem_post(philo->rules->checker);
			break ;
		}
		if (atm() >= philo->last_meal + philo->rules->die)
		{
			printf("%6lu %d has died\n", \
				atm() - philo->rules->time, philo->id);
			exit(-1);
		}
		sem_post(philo->rules->checker);
		usleep(100);
	}
	return (NULL);
}
