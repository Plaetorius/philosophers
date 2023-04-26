#include "philosophers.h"

int	join_philo_threads(t_vars *vars, int failed_nb)
{
	int		i;
	int		failed;
	t_philo	*philo;

	failed = 0;
	i = 0;
	philo = vars->philos;
	while (i < failed_nb)
	{
		failed = pthread_join(philo->thread, NULL);
		if (failed)
		{
			printf("Failed joining philo %d code %d\n", philo->nb, failed);
			pthread_detach(philo->thread);
		}
		philo = philo->next;
		++i;
	}
	return (failed);
}

/*
	Free Philos
	The condition "philo != NULL" is to protect against a failure that might
	happen when this function is being called in create_philos, in case of a
	malloc fail
*/
void	free_philos(t_philo *philo)
{
	const int	nb_philo = philo->vars->nb_philo;
	int			i;
	t_philo		*tmp;

	i = 0;
	while (i < nb_philo && philo != NULL)
	{
		tmp = philo->next;
		free(philo);
		philo = tmp;
		++i;
	}
	philo = NULL;
}

int		free_mutexes(t_vars *vars)
{
	int		i;
	int		ret_value;
	t_philo	*philo;

	ret_value = false;
	ret_value |= pthread_mutex_destroy(&vars->message);
	ret_value |= pthread_mutex_destroy(&vars->synchro);
	ret_value |= pthread_mutex_destroy(&vars->mutex_end);
	ret_value |= pthread_mutex_destroy(&vars->mutex_ate_enough);
	i = 0;
	philo = vars->philos;
	while (i < vars->nb_philo)
	{
		ret_value |= pthread_mutex_destroy(&philo->mutex_last_eat);
		ret_value |= pthread_mutex_destroy(&philo->fork);
		ret_value |= pthread_mutex_destroy(&philo->mutex_forks);
		philo = philo->next;
		++i;
	}
	return (ret_value);
}
