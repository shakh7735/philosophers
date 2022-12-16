/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eshakhge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 13:21:57 by eshakhge          #+#    #+#             */
/*   Updated: 2022/06/12 13:22:00 by eshakhge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

int	ft_atoi(const char *s)
{
	int	n;
	int	i;
	int	m;

	m = 1;
	n = 0;
	i = 0;
	if (!s)
		return (0);
	while (s[i] == ' ')
		i++;
	if (s[i] == '+' || s[i] == '-')
		if (s[i++] == '-')
			m = -1;
	while (s[i] && s[i] >= '0' && s[i] <= '9')
		n = n * 10 + s[i++] - 48;
	if (!s || s[i] != 0)
		return (0);
	return (n * m);
}

long	gettimenow(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return (t.tv_sec * 1000 + t.tv_usec / 1000);
}

long	gettime_ms(long zero)
{
	return (gettimenow() - zero);
}

int	check_died_time(t_philos *p)
{
	int		i;
	long	max_time;

	max_time = p->info->die[p->philo_id];
	i = -1;
	while (++i < p->info->philo_num)
		if (p->info->die[i] < max_time)
			return (0);
	return (1);
}
