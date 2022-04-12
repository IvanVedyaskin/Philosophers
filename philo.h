#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_main_philo
{
	int				num_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_must_eat;
}	t_main_philo;

typedef struct s_other_philos
{
	pthread_mutex_t	right;
	pthread_mutex_t	*left;
	pthread_t		id;
	pthread_mutex_t	time;
	int				num;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	struct timeval	eating_time;
	struct timeval	start_time;
}	t_philos;

// t_philos    *list_init(t_main_philo *data);
// int         free_lists(t_philos **philos);
// int         create_list(t_philos **philos, t_main_philo *data);
int		philo_create(t_main_philo *philo_main);
void	create_list(t_philos *philos, t_main_philo *philo_main);

#endif