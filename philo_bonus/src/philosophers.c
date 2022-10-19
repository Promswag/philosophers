/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:46:14 by gbaumgar          #+#    #+#             */
/*   Updated: 2022/10/19 15:36:59 by gbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_rules		rules;
	int			i;
	t_philo		*philo;

	if (args_handler(argc, argv, &rules))
		return (-1);
	philo = philo_init(&rules);
	i = -1;
	while (++i < rules.number)
	{
		philo[i].pid = fork();
		if (philo[i].pid == 0)
		{
			philosopher(&philo[i]);
			return (0);
		}
	}
	philo_end(philo, rules);
	return (0);
}
