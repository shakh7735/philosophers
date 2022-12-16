/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eshakhge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 13:20:47 by eshakhge          #+#    #+#             */
/*   Updated: 2022/06/12 13:20:55 by eshakhge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	{
		write (2, ERROR_ARG, ft_strlen (ERROR_ARG));
		return (2);
	}
	return (0);
}

int	create_philosophers(int ac, char **av, t_data *data)
{
	int			i;
	t_philos	phil[P_COUNT];

	if (init_struct_data(ac, av, data) != 0)
		return (2);
	i = -1;
	while (++i < data->philo_num)
	{
		phil[i].philo_id = i;
		data->fork[i] = 0;
		data->die[i] = 0;
		data->eat[i] = data->count_must_eat;
		data->zero_time = gettimenow();
		phil[i].info = data;
		pthread_mutex_init (&data->mutex_id[i], NULL);
		pthread_mutex_init (&data->mutex_finish, NULL);
	}
	return (create_philosophers_loop(phil));
}

int	create_philosophers_loop(t_philos phil[P_COUNT])
{
	int	i;

	i = -1;
	while (++i < phil[0].info->philo_num)
	{
		if (pthread_create (&phil[i].tread_id, NULL, \
			philosopher, (void *)&phil[i]))
			return (printf("Error: create thread!\n"));
		usleep(100);
	}
	time_control (phil[0].info);
	return (0);
}
