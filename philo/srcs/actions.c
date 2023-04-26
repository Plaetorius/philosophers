#include "philosophers.h"

void	eat(t_philo *philo, t_vars *vars)
{
	print_action(philo, EATING, vars);
	pthread_mutex_lock(&philo->mutex_last_eat);
	get_time(&philo->last_eat);
	pthread_mutex_unlock(&philo->mutex_last_eat);
	++(philo->meal_number);
	if (philo->meal_number == vars->ttf)
	{
		pthread_mutex_lock(&vars->mutex_ate_enough);
		++(vars->ate_enough);
		pthread_mutex_unlock(&vars->mutex_ate_enough);
	}
	ft_usleep(vars->tte);
}

/*
	Philosophers have their own fork and also take the fork of the next philo
*/
bool	take_forks(t_philo *philo, t_philo *n_philo, t_vars *vars)
{
	pthread_mutex_lock(&philo->fork);
	print_action(philo, TAKEN_FORK, vars);
	if (vars->nb_philo == 1)
	{
		pthread_mutex_unlock(&philo->fork);
		return (false);
	}
	pthread_mutex_lock(&n_philo->fork);
	print_action(n_philo, TAKEN_FORK, vars);
	return (true);
}
