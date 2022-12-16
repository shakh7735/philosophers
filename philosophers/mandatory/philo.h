/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eshakhge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 13:21:25 by eshakhge          #+#    #+#             */
/*   Updated: 2022/06/12 13:21:29 by eshakhge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H

# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <semaphore.h>
# include <fcntl.h>

# define ERROR_ARG "Error: wrong arguments!\n"
# define P_COUNT 200

typedef struct s_data
{
	int				philo_num;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				count_must_eat;
	int				fork[P_COUNT];
	int				eat[P_COUNT];
	long			die[P_COUNT];
	long			zero_time;
	pthread_mutex_t	mutex_id[P_COUNT];
	pthread_mutex_t	mutex_finish;
}					t_data;

typedef struct s_philos
{
	int			philo_id;
	pthread_t	tread_id;
	pthread_t	timecon_id;
	t_data		*info;
}				t_philos;

int		init_struct_data(int ac, char **av, t_data *data);
int		create_philosophers(int ac, char **av, t_data *data);
void	*philosopher(void *data);
void	philo_action(t_philos *phil, int id, int idr);
void	philo_eat(t_philos *phil, int id, int idr);
int		check_died_time(t_philos *p);
void	time_control(t_data *info);
int		check_eat(t_data *info);
int		create_philosophers_loop(t_philos phil[P_COUNT]);
int		ft_strlen(char *s);
int		ft_atoi(const char *s);
long	gettimenow(void);
long	gettime_ms(long zero);

#endif
