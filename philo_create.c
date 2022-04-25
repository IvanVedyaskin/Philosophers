//
// Created by Mohamed Meredith on 4/10/22.
//
#include	"philo.h"

void	philo_game(t_philos *philos)
{
    if (philos->index % 2 != 0) {
        ft_usleep(1000);
    }
    gettimeofday(&(philos->start_time), 0);
    philos->eating_time = philos->start_time;
    philos->ms_eat.tv_sec = philos->eating_time.tv_sec - philos->start_time.tv_sec;
    philos->ms_eat.tv_usec = philos->eating_time.tv_usec - philos->start_time.tv_usec;
    while (1)
    {
		if (philos->max != 0)
		{
			pthread_mutex_lock((philos->left));
			printf("Vzyal levyu vilku  # %d\n", philos->index);
			pthread_mutex_lock(&(philos->right));
			printf("Vzyal pravyu vilku  # %d\n", philos->index);
		}
		else
		{
			pthread_mutex_lock(&(philos->right));
			printf("Vzyal pravyu vilku  # %d\n", philos->index);
			pthread_mutex_lock((philos->left));
			printf("Vzyal levyu vilku  # %d\n", philos->index);
		}
		gettimeofday(&(philos->eating_time), 0);
        philos->ms_eat.tv_sec = philos->eating_time.tv_sec - philos->start_time.tv_sec;
        philos->ms_eat.tv_usec = philos->eating_time.tv_usec - philos->start_time.tv_usec;
        printf ("ms = %d\n", philos->ms_eat.tv_sec * 1000 + philos->ms_eat.tv_usec / 1000);
		printf("Eating # %d\n", philos->index);
        pthread_mutex_unlock(&(philos->time));
        ft_usleep(philos->time_to_eat);
        pthread_mutex_lock(&(philos->time));
        philos->start_time = philos->eating_time;
        printf ("check_time!!! %ld\n", philos->eating_time.tv_sec);
        if (philos->max != 0) {
            pthread_mutex_unlock(&(philos->right));
            pthread_mutex_unlock((philos->left));
        }
        else
        {
            pthread_mutex_unlock((philos->left));
            pthread_mutex_unlock(&(philos->right));
        }
		printf ("sleep # %d\n", philos->index);
		ft_usleep(philos->time_to_sleep);
		printf ("thinking # %d\n", philos->index);
	}
}

void	create_list(t_philos *philos, t_main_philo *philo_main)
{
	int	i;

	i = 0;
	while (i < philo_main->num_of_philo)
	{
		philos[i].time_to_die = philo_main->time_to_die * 1000;
		philos[i].time_to_eat = philo_main->time_to_eat * 1000;
		philos[i].time_to_sleep = philo_main->time_to_sleep * 1000;
		philos[i].max = 0;
		philos[i].index = i;
		pthread_mutex_init(&(philos[i].right), 0);
		pthread_mutex_init(&(philos[i].time), 0);
		i++;
	}
	philos[i - 1].max = i;
	i = 0;
	while (i < philo_main->num_of_philo - 1)
	{
		philos[i].left = &(philos[i + 1].right);
		i++;
	}
	philos[i].left = &(philos[0].right);
}

int	is_died(t_philos *philos, t_main_philo *philo_main)
{
	int	i;

	i = 0;
	while (i < philo_main->num_of_philo)
    {
//		pthread_mutex_lock(&(philos[i].time));
        if (((philos[i].ms_eat.tv_sec) * 1000 + \
				(philos[i].ms_eat.tv_usec) / 1000) > philo_main->time_to_die)
		{
			printf ("philo is died # %d\n", (philos[i].index));
			printf ("main_usec_start = %ld\n", philos[i].start_time.tv_usec);
			printf ("philo_usec_eat = %ld\n", philos[i].eating_time.tv_usec);
			printf ("main_sec = %ld\n", philos[i].start_time.tv_sec);
			printf ("philo_sec = %ld\n", philos[i].eating_time.tv_sec);
			printf ("check_die = %ld \n", (philos[i].eating_time.tv_sec - philos[i].start_time.tv_sec) * 1000 + \
				(philos[i].eating_time.tv_usec - philos[i].start_time.tv_usec) / 1000);
			i = 0;
			while (i < philo_main->num_of_philo)
			{
			//	pthread_mutex_lock(&(philos[i].time));
				printf ("philo_time [%d] = %ld\n", i, philos[i].eating_time.tv_sec);
				i++;
			}
			return (1);
		}
//		printf ("start_time1 %ld index = %d\n", philos[i].start_time.tv_usec, i);
//		philos[i].start_time = philos[i].eating_time;
//		printf ("start_time2 %ld\n", philos[i].start_time.tv_usec);
//		pthread_mutex_unlock(&(philos[i].time));
		i++;
	}
	i = 0;
	return (0);
}

int philo_create(t_main_philo *philo_main)
{
	t_philos	philos[philo_main->num_of_philo];
	int			i;     
	
	i = 0;
	create_list(philos, philo_main);
	while (i < philo_main->num_of_philo)
	{
//		gettimeofday(&(philos[i].start_time), 0);
//		printf ("time_init %ld index = %d\n", philos[i].start_time.tv_usec, i);
		pthread_create(&(philos[i].id), 0, (void *) philo_game, (void *)&philos[i]);
		pthread_detach((philos[i].id));
		i++;
	}
	while (1)
	{
		if (is_died(philos, philo_main) == 1)
			return (0);
        ft_usleep(1000);
	}
	return (1);
}