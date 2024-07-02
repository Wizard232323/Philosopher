/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekoubbi <ekoubbi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 16:16:05 by ekoubbi           #+#    #+#             */
/*   Updated: 2024/07/01 19:09:30 by ekoubbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_take_fork(t_philo *philo)
{
	if (philo->philo_id % 2 != 0)
	{
		pthread_mutex_lock(&philo->left_fork);
		ft_display("has taken a fork", philo);
		pthread_mutex_lock(philo->right_fork);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		ft_display("has taken a fork", philo);
		pthread_mutex_lock(&philo->left_fork);
	}
}

void	ft_eat(t_philo *philo, int time)
{
	ft_take_fork(philo);
	ft_display("is eating", philo);
	pthread_mutex_lock(&philo->m_meal_count);
	philo->meal_count++;
	pthread_mutex_unlock(&philo->m_meal_count);
	pthread_mutex_lock(&philo->m_last_meal);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->m_last_meal);
	if (((get_time() - philo->last_meal)
			+ philo->arg->time_to_eat) >= philo->arg->time_to_die)
		usleep(philo->arg->time_to_die * 1000);
	else
		usleep(time * 1000);
	pthread_mutex_unlock(&philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	ft_sleep(t_philo *philo, int time)
{
	ft_display("is sleeping", philo);
	if (((get_time() - philo->last_meal)
			+ philo->arg->time_to_sleep) >= philo->arg->time_to_die)
		usleep((philo->arg->time_to_die - philo->arg->time_to_eat) * 1000);
	else
		usleep(time * 1000);
}

void	ft_display(char *str, t_philo *philo)
{
	int	time;

	pthread_mutex_lock(&philo->arg->printf);
	if (!one_philo_is_dead(philo->arg))
	{
		time = get_time() - philo->arg->start_time;
		printf("%d %d %s\n", time, philo->philo_id, str);
	}
	pthread_mutex_unlock(&philo->arg->printf);
}

void	wait_thread(t_arg *arg)
{
	int	i;

	i = 0;
	while (i < arg->nb_philo)
	{
		pthread_join(arg->tab_philo[i]->thread, NULL);
		i++;
	}
}
