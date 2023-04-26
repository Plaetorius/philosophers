#include "philosophers.h"

static bool	all_synced(t_vars *vars)
{
	bool	all_synced;

	pthread_mutex_lock(&vars->synchro);
	all_synced = vars->synched == vars->nb_philo;
	all_synced = all_synced & vars->start_time != 0;
	pthread_mutex_unlock(&vars->synchro);
	return (all_synced);
}

void	sync_thread(t_vars *vars)
{
	pthread_mutex_lock(&vars->synchro);
	++(vars->synched);
	pthread_mutex_unlock(&vars->synchro);
	while (!all_synced(vars))
	{
		if (must_philo_end(vars))
			return ;
	}
}
