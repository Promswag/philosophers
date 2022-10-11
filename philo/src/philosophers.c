/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:46:14 by gbaumgar          #+#    #+#             */
/*   Updated: 2022/10/11 17:02:00 by gbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philosopher(void *args)
{
	t_philo			*philo;
	struct timeval	time;

	philo = args;
	gettimeofday(&time, NULL);
	pthread_mutex_lock(philo->rules->lock);
	printf("Coucou -> %loms\n", time.tv_sec * 1000 + time.tv_usec / 1000 - philo->rules->time);
	pthread_mutex_unlock(philo->rules->lock);
	return (NULL);
}

void	philo_init(t_philo **philo, t_rules *rules)
{
	int				i;
	struct timeval	time;

	*philo = malloc(sizeof(t_philo *) * rules->number);
	gettimeofday(&time, NULL);
	rules->time = time.tv_sec * 1000 + time.tv_usec / 1000;
	rules->lock = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(rules->lock, NULL);
	i = -1;
	pthread_mutex_lock(rules->lock);
	while (++i < rules->number)
	{
		philo[i]->id = i;
		philo[i]->rules = rules;
		philo[i]->thread = malloc(sizeof(pthread_t));
		if (pthread_create(philo[i]->thread, NULL, &philosopher, philo[i]))
			break ;
	}
	pthread_mutex_unlock(rules->lock);
	i = -1;
	while (++i < rules->number)
	{
		if (philo[i]->thread)
			pthread_join(*philo[i]->thread, NULL);
	}
}

int	main(int argc, char **argv)
{
	t_philo	*philo;
	t_rules	rules;

	if (args_handler(argc, argv, &rules))
		return (-1);
	philo_init(&philo, &rules);
	pthread_mutex_destroy(rules.lock);
	return (0);
}
