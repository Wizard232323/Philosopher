/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekoubbi <ekoubbi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 16:15:28 by ekoubbi           #+#    #+#             */
/*   Updated: 2024/06/29 15:27:34 by ekoubbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != 0)
		i++;
	return (i);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = ft_strlen(s);
	write(fd, s, i);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

long int	ft_atoi_mod(const char *nptr)
{
	long	i;
	long	k;

	i = 0;
	k = 0;
	if (nptr[i] == 0)
		return (LONG_MAX);
	while (nptr[i] != 0)
	{
		if (nptr[i] >= '0' && nptr[i] <= '9')
			k = k * 10 + nptr[i] - '0';
		else
			break ;
		if (k > INT_MAX)
			return (LONG_MAX);
		i++;
	}
	return (k);
}

int	tab_is_digit(char **tab)
{
	int	i;
	int	j;

	i = 1;
	while (tab[i])
	{
		j = 0;
		while (tab[i][j])
		{
			if (!ft_isdigit(tab[i][j]))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}
