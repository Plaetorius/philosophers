/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgernez <tgernez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 16:28:00 by tgernez           #+#    #+#             */
/*   Updated: 2023/04/27 16:28:01 by tgernez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int ac, char **av)
{
	t_vars	vars;

	if (ac < 5 || ac > 6)
		return (printf("Not enough parameters\n"), EXIT_FAILURE);
	if (parsing(ac, av, &vars) == false)
		return (printf("Parsing failed\n"), EXIT_FAILURE);
	if (init(&vars) == false)
		return (printf("Init Failed\n"), EXIT_FAILURE);
	join_philo_threads(&vars, vars.nb_philo);
	destroy_mutexes(&vars);
	free_philos(vars.philos);
	return (EXIT_SUCCESS);
}
