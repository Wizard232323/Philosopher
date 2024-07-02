/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekoubbi <ekoubbi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 16:15:16 by ekoubbi           #+#    #+#             */
/*   Updated: 2024/07/01 18:52:12 by ekoubbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	if (philo->philo_id % 2 == 0)
	{
		if (((get_time() - philo->last_meal)
				+ philo->arg->time_to_eat) >= philo->arg->time_to_die)
			usleep(philo->arg->time_to_die * 1000);
		else
			usleep(philo->arg->time_to_eat * 1000);
	}
	while (!is_finish(philo))
	{
		if (!is_finish(philo))
			ft_eat(philo, philo->arg->time_to_eat);
		if (!is_finish(philo))
			ft_sleep(philo, philo->arg->time_to_sleep);
		if (!is_finish(philo))
			ft_display("is thinking", philo);
		usleep(500);
	}
	return (args);
}

void	*one_philo(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	ft_display("has take a fork", philo);
	usleep(philo->arg->time_to_die * 1000);
	return (0);
}

int	check_arg(int argc, char **argv, t_arg *arg)
{
	if (argc < 5 || argc > 6)
	{
		ft_putstr_fd("Bad number of arguments\n", STDERR_FILENO);
		exit(1);
	}
	if (tab_is_digit(argv) || init_arg(argc, argv, arg) == 1)
	{
		ft_putstr_fd("Bad arguments\n", STDERR_FILENO);
		if (init_arg(argc, argv, arg) == 1)
			free(arg->tab_philo);
		exit(1);
	}
	return (0);
}

int	all_philo_full(t_arg *arg)
{
	int	i;

	i = 0;
	while (i < arg->nb_philo)
	{
		pthread_mutex_lock(&arg->tab_philo[i]->m_meal_count);
		if (arg->tab_philo[i]->meal_count == arg->max_meal)
		{
			pthread_mutex_unlock(&arg->tab_philo[i]->m_meal_count);
			return (1);
		}
		pthread_mutex_unlock(&arg->tab_philo[i]->m_meal_count);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	static t_arg	arg;
	int				i;

	check_arg(argc, argv, &arg);
	init_philo(&arg);
	init_thread(&arg);
	while (!one_philo_is_dead(&arg) && !all_philo_full(&arg))
	{
		i = 0;
		while (i < arg.nb_philo)
		{
			if (arg.tab_philo[i])
				philo_is_dead(arg.tab_philo[i]);
			i++;
		}
	}
	wait_thread(&arg);
	free_all(&arg);
	return (0);
}
