#include "philosophers.h"

bool	must_simul_end(t_vars *vars)
{
	return (true);
}

void	*simulation(void *arg)
{
	t_philo	*philo;
	t_vars	*vars;

	philo = (t_philo *)arg;
	vars = philo->vars;
	thread_synching(philo->vars);
	if (philo->nb % 2 == 0)
		ft_usleep(10000);
	while (!must_simul_end(vars) && !take_forks(philo, philo->next, vars))
	{
		eat(philo, vars);
		pthread_mutex_unlock(&philo->next->fork);
		pthread_mutex_unlock(&philo->fork);
		print_action(philo, SLEEPING, vars);
		ft_usleep(vars->tts);
		print_action(philo, THINKING, vars);
	}
	return (NULL);
}

void	monitor(t_philo *philo, t_vars *vars)
{
	t_ul	time;

	ft_usleep(20000);
	while (true)
	{
		pthread_mutex_lock(&philo->mutex_last_eat);
		get_time(time);
		if (time - philo->last_eat >= vars->ttd)
		{
			pthread_mutex_unlock(&philo->mutex_last_eat);
			pthread_mutex_lock(&vars->mutex_end);
			vars->end = true;
			pthread_mutex_unlock(&vars->mutex_end);
			print_action(philo, DIED, vars);
			break ;
		}
		pthread_mutex_unlock(&philo->mutex_last_eat);
		if (must_simul_end(vars))
			break ;
		philo = philo->next;

	}
}
