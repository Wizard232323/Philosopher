/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekoubbi <ekoubbi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 16:16:05 by ekoubbi           #+#    #+#             */
/*   Updated: 2024/07/01 19:09:23 by ekoubbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <sys/types.h>
# include <unistd.h>

typedef struct s_arg
{
	long			nb_philo;
	unsigned long	time_to_die;
	unsigned long	time_to_eat;
	long			time_to_sleep;
	long			max_meal;
	bool			is_dead;
	pthread_mutex_t	dead;
	pthread_mutex_t	printf;
	size_t			start_time;
	struct s_philo	**tab_philo;
}					t_arg;

typedef struct s_philo
{
	int				philo_id;
	int				meal_count;
	bool			finish_meal;
	long			last_meal;
	pthread_mutex_t	m_meal_count;
	pthread_mutex_t	m_last_meal;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	left_fork;
	t_arg			*arg;
	pthread_t		thread;
}					t_philo;

void				ft_take_fork(t_philo *philo);
int					all_philo_full(t_arg *arg);
int					check_arg(int argc, char **argv, t_arg *arg);
void				wait_thread(t_arg *arg);
int					one_philo_is_dead(t_arg *arg);
int					init_more(t_arg *arg, char **argv);
void				ft_sleep(t_philo *philo, int time);
int					philo_is_dead(t_philo *philo);
void				free_all(t_arg *arg);
int					is_finish(t_philo *philo);
void				*one_philo(void *arg);
void				ft_eat(t_philo *philo, int time);
void				init_thread(t_arg *arg);
void				ft_display(char *str, t_philo *philo);
void				*philo_routine(void *args);
size_t				get_time(void);
void				ft_putstr_fd(char *s, int fd);
int					ft_isdigit(int c);
int					tab_is_digit(char **tab);
size_t				ft_strlen(const char *s);
long int			ft_atoi_mod(const char *nptr);
int					init_arg(int nb, char **tab, t_arg *arg);
int					init_philo(t_arg *arg);

#endif
