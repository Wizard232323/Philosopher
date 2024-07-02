/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_control.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekoubbi <ekoubbi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 16:15:16 by ekoubbi           #+#    #+#             */
/*   Updated: 2024/07/01 17:47:09 by ekoubbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_finish(t_philo *philo)
{
	if (philo->meal_count == philo->arg->max_meal
		|| one_philo_is_dead(philo->arg))
		return (1);
	return (0);
}

int	one_philo_is_dead(t_arg *arg)
{
	int	dead;

	pthread_mutex_lock(&arg->dead);
	dead = arg->is_dead;
	pthread_mutex_unlock(&arg->dead);
	return (dead);
}

int	philo_is_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->m_last_meal);
	if ((get_time() - philo->last_meal) >= philo->arg->time_to_die)
	{
		ft_display("died", philo);
		pthread_mutex_lock(&philo->arg->dead);
		philo->arg->is_dead = 1;
		pthread_mutex_unlock(&philo->arg->dead);
		pthread_mutex_unlock(&philo->m_last_meal);
		return (1);
	}
	pthread_mutex_unlock(&philo->m_last_meal);
	return (0);
}

size_t	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		ft_putstr_fd("gettimeofday() error\n", STDERR_FILENO);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}
