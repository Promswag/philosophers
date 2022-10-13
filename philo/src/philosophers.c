/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:46:14 by gbaumgar          #+#    #+#             */
/*   Updated: 2022/10/13 14:13:38 by gbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philo_end(t_philo *philo, t_rules rules)
{
	while (rules.number--)
		if (philo + rules.number)
			free(philo[rules.number].thread);
	if (philo)
		free(philo);
}

int	main(int argc, char **argv)
{
	int		i;
	t_philo	*philo;
	t_rules	rules;

	if (args_handler(argc, argv, &rules))
		return (-1);
	philo = philo_init(&rules);
	i = -1;
	while (++i < rules.number)
	{
		pthread_create(philo[i].thread, NULL, &philosopher, &philo[i]);
	}
	i = -1;
	while (++i < rules.number)
		pthread_join(*philo[i].thread, NULL);
	philo_end(philo, rules);
	return (0);
}

	// pthread_mutex_destroy(rules.lock);
	// philo_thread_start(&philo, &rules);
	// philo_thread_end(&philo, &rules);