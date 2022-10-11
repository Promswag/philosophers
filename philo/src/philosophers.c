/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:46:14 by gbaumgar          #+#    #+#             */
/*   Updated: 2022/10/11 14:52:26 by gbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philosopher(void *args)
{
	t_philo	*philo;

	philo = args;
	printf("Coucou\n");
	return (NULL);
}

void	philo_init(t_philo **philo)
{
	int	i;

	(*philo)->threads = calloc(sizeof(pthread_t), (*philo)->rules.number);
	i = -1;
	while (++i < (*philo)->rules.number)
	{
		if (pthread_create(&(*philo)->threads[i], NULL, &philosopher, philo))
			break ;
	}
	i = -1;
	while (++i < (*philo)->rules.number)
	{
		if ((*philo)->threads[i])
			pthread_join((*philo)->threads[i], NULL);
	}
}

int	main(int argc, char **argv)
{
	// int				i;
	// t_ph			*threads;

	// threads = calloc(3, sizeof(t_ph *));
	// (void)argc;
	// (void)argv;
	// i = -1;
	// while (++i < 3)
	// {
	// 	threads[i].num = i;
	// 	pthread_create(&threads[i].id, NULL, &hello, &threads[i]);
	// }
	// i = -1;
	// while (++i < 3)
	// {
	// 	pthread_join(threads[i].id, NULL);
	// }
	// return (0);

	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (-1);
	if (args_handler(argc, argv, &philo))
		return (-1);
	philo_init(&philo);
	return (0);
}
