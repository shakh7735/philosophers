/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eshakhge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 13:21:40 by eshakhge          #+#    #+#             */
/*   Updated: 2022/06/12 13:21:44 by eshakhge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philosopher(void *philo)
{
	int			id;
	int			idr;
	t_philos	*phil;

	phil = (t_philos *)philo;
	id = phil->philo_id;
	if (id == phil->info->philo_num - 1)
		idr = 0;
	else
		idr = id + 1;
	phil->info->die[id] = gettime_ms(phil->info->zero_time);
	phil->info->eat[id] = 0;
	printf("%-7ld %d is thinking\n", gettime_ms(phil->info->zero_time), id + 1);
	philo_action (phil, id, idr);
	return (0);
}

void	philo_action(t_philos *phil, int id, int idr)
{
	long	zero;
	long	sleep;

	zero = phil->info->zero_time;
	while (phil->info->eat[id] != phil->info->count_must_eat)
	{
		if (phil->info->philo_num <= 1)
			continue ;
		philo_eat(phil, id, idr);
		printf("%-7ld %d is sleeping\n", gettime_ms(zero), id + 1);
		sleep = gettime_ms(zero);
		while (gettime_ms(zero) - sleep < phil->info->time_to_sleep)
			;
		printf("%-7ld %d is thinking\n", gettime_ms(zero), id + 1);
	}
}

void	philo_eat(t_philos *phil, int id, int idr)
{
	long	zero;

	zero = phil->info->zero_time;
	pthread_mutex_lock (&phil->info->mutex_id[id]);
	printf("%-7ld %d has taken a fork\n", gettime_ms(zero), id + 1);
	pthread_mutex_lock (&phil->info->mutex_id[idr]);
	printf("%-7ld %d has taken a fork\n", gettime_ms(zero), id + 1);
	phil->info->eat[id]++;
	printf("%-7ld %d is eating\n", gettime_ms(zero), id + 1);
	phil->info->die[id] = gettime_ms(zero);
	while (gettime_ms(zero) - phil->info->die[id] < phil->info->time_to_eat)
		;
	pthread_mutex_unlock (&phil->info->mutex_id[id]);
	pthread_mutex_unlock (&phil->info->mutex_id[idr]);
}

void	time_control(t_data *info)
{
	int			id;

	id = -1;
	while (++id < info->philo_num)
	{
		if (info->eat[id] != info->count_must_eat)
		{
			usleep(50);
			if (gettime_ms(info->zero_time) - info->die[id] \
				>= info->time_to_die)
			{
				printf("\033[1;31m%-7ld %d died\n\033[0m", \
					gettime_ms(info->zero_time), id + 1);
				break ;
			}
		}
		if (!check_eat(info))
			break ;
		if (id == info->philo_num - 1)
			id = -1;
	}
}

int	check_eat(t_data *info)
{
	int	i;

	i = -1;
	while (++i < info->philo_num)
		if (info->eat[i] != info->count_must_eat)
			break ;
	if (i == info->philo_num)
		return (0);
	return (1);
}
