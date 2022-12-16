/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phil_proc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eshakhge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 14:10:20 by eshakhge          #+#    #+#             */
/*   Updated: 2022/06/12 14:10:25 by eshakhge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philosopher(t_philos *phil)
{
	int	id;
	int	idr;
	int	i;

	id = phil->philo_id;
	if (id == phil->info->philo_num - 1)
		idr = 0;
	else
		idr = id + 1;
	phil->info->die[id] = gettime_ms(phil->info->zero_time);
	phil->info->eat[id] = 0;
	printf("%-7ld %d is thinking\n", phil->info->die[id], id + 1);
	pthread_create (&phil->tread_id, NULL, philo_action, (void *)phil);
	time_control (phil);
	pthread_join (phil->tread_id, NULL);
}

void	*philo_action(void *pr)
{
	long		zero;
	t_philos	*phil;
	int			id;

	phil = (t_philos *)pr;
	id = phil->philo_id;
	zero = phil->info->zero_time;
	pil_loop(phil, id, zero);
	sem_post(phil->info->sem_stop);
	return (0);
}

void	pil_loop(t_philos *phil, int id, long zero)
{
	long	temp;

	while (phil->info->eat[id] != phil->info->count_must_eat)
	{
		if (phil->info->philo_num <= 1)
			continue ;
		sem_wait(phil->info->sem_forks_count);
		printf("%-7ld %d has taken a fork\n", gettime_ms(zero), id + 1);
		sem_wait(phil->info->sem_forks_count);
		printf("%-7ld %d has taken a fork\n", gettime_ms(zero), id + 1);
		phil->info->eat[id]++;
		printf("%-7ld %d is eating\n", gettime_ms(zero), id + 1);
		phil->info->die[id] = gettime_ms(zero);
		while (gettime_ms(zero) - phil->info->die[id] < phil->info->time_to_eat)
			;
		sem_post(phil->info->sem_forks_count);
		sem_post(phil->info->sem_forks_count);
		printf("%-7ld %d is sleeping\n", gettime_ms(zero), id + 1);
		temp = gettime_ms(zero);
		while (gettime_ms(zero) - temp < phil->info->time_to_sleep)
			;
		printf("%-7ld %d is thinking\n", gettime_ms(zero), id + 1);
	}
}

void	time_control(void *pr)
{
	t_philos	*phil;
	int			id;

	phil = (t_philos *)pr;
	id = phil->philo_id;
	while (phil->info->eat[id] != phil->info->count_must_eat)
	{
		usleep(50);
		if (gettime_ms(phil->info->zero_time) - phil->info->die[id] \
			>= phil->info->time_to_die)
		{
			sem_wait(phil->info->sem_finish);
			printf("\033[1;31m%-7ld %d died\n\033[0m", \
				gettime_ms(phil->info->zero_time), id + 1);
			phil->info->fork[id] = 1;
			id = -1;
			while (++id < phil->info->philo_num)
				sem_post(phil->info->sem_stop);
			exit (0);
		}
	}
}
