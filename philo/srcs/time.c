/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgernez <tgernez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 16:27:49 by tgernez           #+#    #+#             */
/*   Updated: 2023/04/28 16:48:25 by tgernez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	print_action(t_philo *philo, int action, t_vars *vars)
{
	t_ul	time;

	if (get_time(&time) == false)
		return (false);
	pthread_mutex_lock(&vars->mutex_start_time);
	time = (time - vars->start_time) / 1000;
	pthread_mutex_unlock(&vars->mutex_start_time);
	pthread_mutex_lock(&vars->mutex_end);
	if (vars->end == true)
		return (pthread_mutex_unlock(&vars->mutex_end), true);
	pthread_mutex_unlock(&vars->mutex_end);
	pthread_mutex_lock(&vars->message);
	if (action == TAKEN_FORK)
		printf("%lu %d has taken a fork\n", time, philo->nb);
	else if (action == EATING)
		printf("%lu %d is eating\n", time, philo->nb);
	else if (action == SLEEPING)
		printf("%lu %d is sleeping\n", time, philo->nb);
	else if (action == THINKING)
		printf("%lu %d is thinking\n", time, philo->nb);
	pthread_mutex_unlock(&vars->message);
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

bool	set_time_start(t_vars *vars)
{
	int		i;
	t_philo	*philo;

	pthread_mutex_lock(&vars->synchro);
	if (get_time(&vars->start_time) == false)
		return (pthread_mutex_unlock(&vars->synchro), false);
	pthread_mutex_unlock(&vars->synchro);
	i = 0;
	philo = vars->philos;
	while (i < vars->nb_philo)
	{
		pthread_mutex_lock(&philo->mutex_last_eat);
		if (get_time(&philo->last_eat) == false)
			return (pthread_mutex_unlock(&philo->mutex_last_eat), false);
		pthread_mutex_unlock(&philo->mutex_last_eat);
		philo = philo->next;
		++i;
	}
	return (true);
}
