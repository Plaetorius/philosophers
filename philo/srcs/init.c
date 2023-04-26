#include "philosophers.h"

static t_philo	*new_philo(int nb, t_vars *vars)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->nb = nb;
	philo->meal_number = 0;
	philo->last_eat = 0;
	philo->vars = vars;
	philo->next = philo;
	philo->prev = philo;
	return (philo);
}

static bool	init_philos(t_vars *vars)
{
	int		i;
	t_philo	*philo;

	i = 1;
	while (i < vars->nb_philo + 1)
	{
		philo = new_philo(i, vars);
		if (!philo)
			return (free_philos(vars->philos), false);
		if (vars->philos)
		{
			philo->next = vars->philos;
			philo->prev = vars->philos->prev;
			vars->philos->prev->next = philo;
			vars->philos->prev = philo;
		}
		else
			vars->philos = philo;
		++i;
	}
	return (true);
}

static bool	init_threads(t_vars *vars)
{
	int		i;
	t_philo	*philo;

	i = 0;
	philo = vars->philos;
	while (i < vars->nb_philo)
	{
		if (pthread_create(&philo->thread, NULL, &simulation, NULL))
		{
			printf("test");
		}
	}
	return (true);
}

bool	init_mutexes(t_vars *vars)
{
	return (true);
}

bool	init(t_vars	*vars)
{
	if (init_philos(vars))
		return (free_philos(vars->philos), false);
	if (init_mutexes(vars))
		return (free_mutexes(vars), free_philos(vars), false);
	// if (init_threads(vars))
	// 	return (free_mutexes(vars), free_philos(vars), false);
	init_threads(vars); //TODO As evverrything will be cleared in the main function, don't know if necessary to clear in the return
	return (true);
}
