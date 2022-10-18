/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 15:22:40 by gbaumgar          #+#    #+#             */
/*   Updated: 2022/10/18 18:15:48 by gbaumgar         ###   ########.fr       */
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
	usleep(delay * 950);
	while (1)
	{
		if (atm() >= time + delay)
			break ;
		usleep(5);
	}
}

int	philo_check(t_philo *philo)
{
	sem_wait(philo->rules->checker);
	if (atm() >= philo->last_meal + philo->rules->die)
	{
		printf("%6lu %d has died\n", \
			atm() - philo->rules->time, philo->id);
		while (philo->next_philo->pid != 0)
		{
			kill(philo->next_philo->pid, SIGKILL);
			philo = philo->next_philo;
		}
		sem_post(philo->rules->checker);
		return (1);
	}
	if (philo->meals_eaten == philo->rules->full && philo->rules->full != 0)
	{
		sem_post(philo->rules->checker);
		return (1);
	}
	sem_post(philo->rules->checker);
	return (0);
}

void	philo_end(t_philo *philo, t_rules rules)
{
	int	i;

	i = -1;
	while (++i < rules.number)
		waitpid(philo[i].pid, NULL, 0);
	sem_close(philo[0].rules->forks);
	sem_unlink("/forks");
	sem_close(philo[0].rules->checker);
	sem_unlink("/checker");
	if (philo)
		free(philo);
}
