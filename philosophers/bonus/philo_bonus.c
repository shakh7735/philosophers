/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eshakhge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 14:10:39 by eshakhge          #+#    #+#             */
/*   Updated: 2022/06/12 14:10:45 by eshakhge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 5 && ac != 6)
	{
		write (2, ERROR_ARG, ft_strlen(ERROR_ARG));
		return (0);
	}
	create_philosophers (ac, av, &data);
	return (0);
}

int	init_struct_data(int ac, char **av, t_data *data)
{
	data->philo_num = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
	{
		data->count_must_eat = ft_atoi(av[5]);
		if (data->count_must_eat <= 0)
		{
			write (2, ERROR_ARG, ft_strlen(ERROR_ARG));
			return (1);
		}
	}
	else
		data->count_must_eat = -1;
	if (data->philo_num <= 0 || data->time_to_die <= 0 \
		|| data->time_to_eat <= 0 || data->time_to_sleep <= 0)
		return (write (2, ERROR_ARG, ft_strlen(ERROR_ARG)));
	sem_unlink ("finish");
	sem_unlink ("fork");
	sem_unlink ("stop");
	data->sem_finish = sem_open("finish", O_CREAT, 0644, 1);
	data->sem_stop = sem_open("stop", O_CREAT, 0644, 0);
	data->sem_forks_count = sem_open("fork", O_CREAT, 0644, data->philo_num);
	return (0);
}

void	ft_sem_close_all(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_num)
		kill (data->pid_id[i], 15);
	sem_close(data->sem_finish);
	sem_close(data->sem_eat_count);
	sem_close(data->sem_forks_count);
	sem_close(data->sem_stop);
	i = -1;
	while (++i < data->philo_num)
		sem_close(data->sem_forks[i]);
}

int	create_philosophers(int ac, char **av, t_data *data)
{
	int			i;
	t_philos	phil[P_COUNT];
	char		*sem_name;

	i = init_struct_data(ac, av, data);
	if (i != 0)
		return (i);
	i = -1;
	while (++i < data->philo_num)
	{
		sem_name = ft_join_strnum("fork", i);
		phil[i].philo_id = i;
		data->fork[i] = 0;
		data->die[i] = 0;
		data->eat[i] = data->count_must_eat;
		sem_unlink (sem_name);
		data->sem_forks[i] = sem_open(sem_name, O_CREAT, 0644, 1);
		data->zero_time = gettimenow();
		phil[i].info = data;
		free (sem_name);
	}
	create_forks(phil, data);
	sem_wait(data->sem_stop);
	ft_sem_close_all(data);
	return (0);
}

int	create_forks(t_philos *phil, t_data *data)
{
	int		i;
	int		y;
	pid_t	pid;

	i = -1;
	while (++i < data->philo_num)
	{
		data->pid_id[i] = fork();
		if (data->pid_id[i] < 0)
			exit(printf("Error create fork!\n"));
		if (data->pid_id[i] == 0)
		{
			philosopher(&phil[i]);
			exit (0);
		}
	}
	return (0);
}
