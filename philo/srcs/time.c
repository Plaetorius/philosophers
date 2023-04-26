#include "philosophers.h"

bool	print_action(t_philo *philo, int action, t_vars *vars)
{
	t_ul	time;

	if (get_time(&time) == false)
		return (false);
	time = (time - vars->start_time) / 1000;
	if (action == TAKEN_FORK)
		printf("%lu %d has taken a fork\n", time, philo->nb);
	else if (action == EATING)
		printf("%lu %d is eating\n", time, philo->nb);
	else if (action == SLEEPING)
		printf("%lu %d is sleeping\n", time, philo->nb);
	else if (action == THINKING)
		printf("%lu %d is thinking\n", time, philo->nb);
	else if (action == DIED)
		printf("%lu %d died\n", time, philo->nb);
	return (true);
}

bool	get_time(t_ul *val)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (false);
	*val = tv.tv_sec * 1000000 + tv.tv_usec;
	return (true);
}

bool	ft_usleep(t_ul sleep_time)
{
	t_ul			start_time;
	t_ul			curr_time;

	if (get_time(&curr_time) == false)
		return (false);
	start_time = curr_time;
	while (start_time + sleep_time > curr_time)
	{
		usleep(sleep_time / 10);
		if (get_time(&curr_time) == false)
			return (false);
	}
	return (true);
}
