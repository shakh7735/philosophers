/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eshakhge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 14:11:05 by eshakhge          #+#    #+#             */
/*   Updated: 2022/06/12 14:11:15 by eshakhge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H

# define PHILO_BONUS_H

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
	int		philo_num;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		count_must_eat;
	sem_t	*sem_forks[P_COUNT];
	sem_t	*sem_finish;
	sem_t	*sem_eat_count;
	sem_t	*sem_forks_count;
	sem_t	*sem_stop;
	int		fork[P_COUNT];
	int		eat[P_COUNT];
	long	die[P_COUNT];
	long	zero_time;
	int		fin;
	pid_t	pid;
	pid_t	pid_id[P_COUNT];
}			t_data;

typedef struct s_philos
{
	int			philo_id;
	pthread_t	tread_id;
	t_data		*info;
}				t_philos;

int		init_struct_data(int ac, char **av, t_data *data);
void	ft_sem_close_all(t_data *data);
int		create_philosophers(int ac, char **av, t_data *data);
int		create_forks(t_philos *phil, t_data *data);
void	philosopher(t_philos *phil);
void	*philo_action(void *pr);
void	pil_loop(t_philos *phil, int id, long zero);
void	time_control(void *pr);
int		ft_strlen(char *s);
int		ft_atoi(const char *s);
char	*ft_join_strnum(char *str, int num);
long	gettimenow(void);
long	gettime_ms(long zero);

#endif
