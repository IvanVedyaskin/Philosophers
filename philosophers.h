//
// Created by Ivan on 29.04.2022.
//

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include "stdio.h"
# include "stdlib.h"
# include "pthread.h"
# include "unistd.h"
# include "sys/time.h"

# define PHILOS 201

typedef struct s_philo_person
{
	int				_id;
	int				_sleep;
	int				max;
	int				n_eat;
	pthread_mutex_t check_n_eat;
	// int				must_die;
	pthread_mutex_t	*right;
	pthread_mutex_t	*left;
	pthread_mutex_t	*std_out;
	pthread_t		id;
	pthread_mutex_t	time;
	struct timeval	t_eat;
	struct timeval	m_time;
	long int		ms_eat;
}	t_philo;

typedef struct s_main_data
{
	int				n_philo;
	int				t_to_die;
	int				t_to_eat;
	int				t_to_sleep;
	int				n_eat;
	struct timeval	m_time;
	t_philo			philo[PHILOS];
	pthread_mutex_t check_n_eat;
	pthread_mutex_t	std_out;
	pthread_mutex_t	fork[PHILOS];
}	t_m_data;

int		ph_mutex_tread_all(t_m_data *m_data);
int		print_status(t_philo *philo, int status);
int		time_count(struct timeval *tm1, struct timeval *tm2);
void	ft_usleep(long int ms, struct timeval *t_eat);
int		all_destroy(t_m_data *m_data);

#endif
