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

static bool	init_philo_threads(t_vars *vars)
{
	int		i;
	t_philo	*philo;

	i = 0;
	philo = vars->philos;
	while (i < vars->nb_philo)
	{
		if (pthread_create(&philo->thread, NULL, &simulation, (void *)philo))
		{
			join_philo_threads(vars, philo->nb);
			vars->end = true;
			return (false);
		}
		philo = philo->next;
		++i;
	}
	return (true);
}

static int	init_mutexes(t_vars *vars)
{
	int		i;
	int		ret_value;
	t_philo	*philo;

	ret_value = false;
	ret_value |= pthread_mutex_init(&vars->message, NULL);
	ret_value |= pthread_mutex_init(&vars->synchro, NULL);
	ret_value |= pthread_mutex_init(&vars->mutex_end, NULL);
	ret_value |= pthread_mutex_init(&vars->mutex_ate_enough, NULL);
	i = 0;
	philo = vars->philos;
	while (i < vars->nb_philo)
	{
		ret_value |= pthread_mutex_init(&philo->mutex_last_eat, NULL);
		ret_value |= pthread_mutex_init(&philo->fork, NULL);
		ret_value |= pthread_mutex_init(&philo->mutex_forks, NULL);
		philo = philo->next;
		++i;
	}
	return (ret_value);
}

bool	init(t_vars	*vars)
{
	if (init_philos(vars))
		return (free_philos(vars->philos), false);
	if (init_mutexes(vars))
		return (free_mutexes(vars), free_philos(vars), false);
	if (init_philo_threads(vars))
		return (free_mutexes(vars), free_philos(vars), false);
	if (set_time_start(vars))
		return (join_philo_threads(vars, vars->nb_philo),
			free_mutexes(vars), free_philos(vars), false);
	monitor(vars->philos, vars);
	return (true);
}
