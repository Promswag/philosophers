/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:46:14 by gbaumgar          #+#    #+#             */
/*   Updated: 2022/10/12 16:55:42 by gbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	int		i;
	t_philo	*philo;
	t_rules	rules;

	if (args_handler(argc, argv, &rules))
		return (-1);
	philo = philo_init(&rules);
	i = -1;
	// rules.lock = malloc(sizeof(pthread_mutex_t));
	// pthread_mutex_init(&rules.lock, NULL);
	while (++i < rules.number)
	{
		pthread_create(philo[i].thread, NULL, &philosopher, &philo[i]);
		// usleep(1);
	}
	i = -1;
	while (++i < rules.number)
		pthread_join(*philo[i].thread, NULL);
	return (0);
}

	// pthread_mutex_destroy(rules.lock);
	// philo_thread_start(&philo, &rules);
	// philo_thread_end(&philo, &rules);