/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekoubbi <ekoubbi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 16:15:23 by ekoubbi           #+#    #+#             */
/*   Updated: 2024/07/01 18:56:00 by ekoubbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philo(t_arg *arg)
{
	int	i;

	i = -1;
	while (++i < arg->nb_philo)
		arg->tab_philo[i] = malloc(sizeof(t_philo));
	i = 0;
	while (i < arg->nb_philo)
	{
		arg->tab_philo[i]->philo_id = i + 1;
		arg->tab_philo[i]->meal_count = 0;
		arg->tab_philo[i]->finish_meal = false;
		arg->tab_philo[i]->arg = arg;
		arg->tab_philo[i]->last_meal = get_time();
		pthread_mutex_init(&arg->tab_philo[i]->m_meal_count, NULL);
		pthread_mutex_init(&arg->tab_philo[i]->m_last_meal, NULL);
		pthread_mutex_init(&arg->tab_philo[i]->left_fork, NULL);
		if (i != 0)
			arg->tab_philo[i]->right_fork = &arg->tab_philo[i - 1]->left_fork;
		i++;
	}
	arg->tab_philo[0]->right_fork = &arg->tab_philo[i - 1]->left_fork;
	return (0);
}

int	init_arg(int argc, char **argv, t_arg *arg)
{
	argc--;
	arg->is_dead = false;
	arg->nb_philo = ft_atoi_mod(argv[1]);
	if (arg->nb_philo == 0 || arg->nb_philo > 200)
		return (1);
	arg->tab_philo = malloc(sizeof(t_philo *) * arg->nb_philo);
	if (!arg->tab_philo)
		return (1);
	arg->time_to_eat = ft_atoi_mod(argv[3]);
	if (arg->time_to_eat == LONG_MAX)
		return (1);
	arg->time_to_sleep = ft_atoi_mod(argv[4]);
	if (arg->time_to_sleep == LONG_MAX)
		return (1);
	if (argc == 5)
		arg->max_meal = ft_atoi_mod(argv[5]);
	else
		arg->max_meal = -42;
	if (arg->max_meal > INT_MAX)
		return (1);
	arg->start_time = get_time();
	return (init_more(arg, argv));
}

int	init_more(t_arg *arg, char **argv)
{
	arg->time_to_die = ft_atoi_mod(argv[2]);
	if (arg->time_to_die == LONG_MAX)
		return (1);
	pthread_mutex_init(&arg->printf, NULL);
	pthread_mutex_init(&arg->dead, NULL);
	return (0);
}

void	free_all(t_arg *arg)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&arg->printf);
	pthread_mutex_destroy(&arg->dead);
	while (i < arg->nb_philo)
	{
		pthread_mutex_destroy(&arg->tab_philo[i]->left_fork);
		pthread_mutex_destroy(&arg->tab_philo[i]->m_last_meal);
		pthread_mutex_destroy(&arg->tab_philo[i]->m_meal_count);
		free(arg->tab_philo[i]);
		i++;
	}
	free(arg->tab_philo);
}

void	init_thread(t_arg *arg)
{
	int	i;

	if (arg->nb_philo == 1)
		pthread_create(&(arg->tab_philo[0]->thread), NULL, one_philo,
			arg->tab_philo[0]);
	else
	{
		i = 0;
		while (i < arg->nb_philo)
		{
			pthread_create(&(arg->tab_philo[i]->thread), NULL, philo_routine,
				(void *)arg->tab_philo[i]);
			i++;
		}
	}
}
