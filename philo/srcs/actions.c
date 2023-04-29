/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgernez <tgernez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 16:28:28 by tgernez           #+#    #+#             */
/*   Updated: 2023/04/29 13:48:47 by tgernez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// static void	give_back_forks(t_philo *philo)
// {
// 	t_philo	*prev_philo;
// 	t_philo	*next_philo;

// 	prev_philo = philo->prev;
// 	next_philo = philo->next;

// 	pthread_mutex_lock(&prev_philo->mutex_forks);
// 	if (prev_philo->fork_state == NO_FORK)
// 		prev_philo->fork_state = LEFT_FORK;
// 	else if (next_philo->fork_state == RIGHT_FORK)
// 		prev_philo->fork_state = BOTH_FORKS;
// 	pthread_mutex_unlock(&prev_philo->mutex_forks);
// 	pthread_mutex_lock(&next_philo->mutex_forks);
// 	if (next_philo->fork_state == NO_FORK)
// 		next_philo->fork_state = RIGHT_FORK;
// 	else if (next_philo->fork_state == LEFT_FORK)
// 		next_philo->fork_state = BOTH_FORKS;
// 	pthread_mutex_unlock(&next_philo->mutex_forks);
// 	pthread_mutex_unlock(&philo->mutex_forks);
// }

void	eat(t_philo *philo, t_vars *vars)
{
	if (vars->ttf != -1 && philo->meal_number >= vars->ttf)
		return ;
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
	// give_back_forks(philo);
		pthread_mutex_unlock(&philo->next->fork);
	pthread_mutex_unlock(&philo->fork);
}

/*
	Philosophers have their own fork (right)
	and also take the fork of the next philo (left)
*/
bool	take_forks(t_philo *philo, t_vars *vars)
{
	// t_philo	*prev_philo;
	// t_philo	*next_philo;

	// if (philo->fork_state != BOTH_FORKS)
	// 	return (false);
	// pthread_mutex_lock(&philo->mutex_forks);
	// prev_philo = philo->prev;
	// next_philo = philo->next;
	// pthread_mutex_lock(&prev_philo->mutex_forks);
	// if (prev_philo->fork_state == BOTH_FORKS)
	// 	prev_philo->fork_state = RIGHT_FORK;
	// else if (prev_philo->fork_state == LEFT_FORK)
	// 	prev_philo->fork_state = NO_FORK;
	// pthread_mutex_unlock(&prev_philo->mutex_forks);
	// pthread_mutex_lock(&next_philo->mutex_forks);
	// if (next_philo->fork_state == BOTH_FORKS)
	// 	next_philo->fork_state = LEFT_FORK;
	// else if (next_philo->fork_state == RIGHT_FORK)
	// 	next_philo->fork_state = NO_FORK;
	// pthread_mutex_unlock(&next_philo->mutex_forks);
	if (philo->nb % 2)
	{
		pthread_mutex_lock(&philo->fork);
		print_action(philo, TAKEN_FORK, vars);
		pthread_mutex_lock(&philo->next->fork);
		print_action(philo, TAKEN_FORK, vars);
	}
	else
	{
		pthread_mutex_lock(&philo->next->fork);
		print_action(philo, TAKEN_FORK, vars);
		pthread_mutex_lock(&philo->fork);
		print_action(philo, TAKEN_FORK, vars);
	}
	return (true);
}
