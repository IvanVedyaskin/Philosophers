//
// Created by Mohamed Meredith on 4/10/22.
//
#include	"philo.h"

void	put_message(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	write(1, str, i);
}

void	check_fork(t_philos *philos)
{
	long int		t1;
	struct timeval	take_fork;

	if (philos->max != 0)
	{
		pthread_mutex_lock((philos->left));
		pthread_mutex_lock(philos->time);
		gettimeofday(&(take_fork), 0);
		t1 = (take_fork.tv_sec - philos->global_time.tv_sec) * 1000 + (take_fork.tv_usec - philos->global_time.tv_usec) / 1000;
		printf("%d %d ",t1, philos->index);
		put_message("has taken fork\n");
		pthread_mutex_unlock(philos->time);
		pthread_mutex_lock(&(philos->right));
		pthread_mutex_lock(philos->time);
		gettimeofday(&(take_fork), 0);
		t1 = (take_fork.tv_sec - philos->global_time.tv_sec) * 1000 + (take_fork.tv_usec - philos->global_time.tv_usec) / 1000;
		printf("%d %d ",t1, philos->index);
		put_message("has taken fork\n");
		pthread_mutex_unlock(philos->time);
	}
	else
	{
		pthread_mutex_lock(&(philos->right));
		pthread_mutex_lock(philos->time);
		gettimeofday(&(take_fork), 0);
		t1 = (take_fork.tv_sec - philos->global_time.tv_sec) * 1000 + (take_fork.tv_usec - philos->global_time.tv_usec) / 1000;
		printf("%d %d ",t1, philos->index);
		put_message("has taken fork\n");
		pthread_mutex_unlock(philos->time);
		pthread_mutex_lock((philos->left));
		pthread_mutex_lock(philos->time);
		gettimeofday(&(take_fork), 0);
		t1 = (take_fork.tv_sec - philos->global_time.tv_sec) * 1000 + (take_fork.tv_usec - philos->global_time.tv_usec) / 1000;
		printf("%d %d ",t1, philos->index);
		put_message("has taken fork\n");
		pthread_mutex_unlock(philos->time);
	}
}

void	philo_game(void *phil)
{
	t_philos *philos;

	philos = phil;
    if (philos->index % 2 != 0) {
        usleep(1000);
    }
	gettimeofday(&(philos->start_time), 0);
    while (1)
    {
		check_fork(philos);
		pthread_mutex_lock(philos->time);
		gettimeofday(&(philos->eating_time), 0);
		philos->ms_eat = (philos->eating_time.tv_sec - philos->global_time.tv_sec) * 1000 + (philos->eating_time.tv_usec - philos->global_time.tv_usec) / 1000;
        printf ("ms = %d index = %d\n", philos->ms_eat, philos->index);
		printf("Eating # %d\n", philos->index);
		gettimeofday(&(philos->eating_time), 0);
		philos->ms_eat = (philos->eating_time.tv_sec - philos->global_time.tv_sec) * 1000 + (philos->eating_time.tv_usec - philos->global_time.tv_usec) / 1000;
		philos->start_time = philos->eating_time;
		pthread_mutex_unlock(philos->time);
		ft_usleep(philos->time_to_eat);
//        printf ("check_time!!! %ld\n", philos->eating_time.tv_sec);
//        if (philos->max != 0) {
//            pthread_mutex_unlock(&(philos->right));
//            pthread_mutex_unlock((philos->left));
//        }
//        else
//        {
            pthread_mutex_unlock((philos->left));
            pthread_mutex_unlock(&(philos->right));
//        }
		pthread_mutex_lock(philos->time);
		printf ("sleep # %d\n", philos->index);
		pthread_mutex_unlock(philos->time);
		ft_usleep(philos->time_to_sleep);
		pthread_mutex_lock(philos->time);
		printf ("thinking # %d\n", philos->index);
		pthread_mutex_unlock(philos->time);
	}
}

int	create_list(t_philos *philos, t_main_philo *philo_main)
{
	int	i;

	i = -1;
	if (pthread_mutex_init(&(philo_main->time), 0))
		return (1);
	while (++i < philo_main->num_of_philo)
	{
		philos[i].time_to_die = philo_main->time_to_die * 1000;
		philos[i].time_to_eat = philo_main->time_to_eat * 1000;
		philos[i].time_to_sleep = philo_main->time_to_sleep * 1000;
		philos[i].max = 0;
		philos[i].ms_eat = 0;
		philos[i].index = i;
		philos[i].global_time = philo_main->global_time;
		philos[i].time = &(philo_main->time);
		if (pthread_mutex_init(&(philos[i].right), 0))
			return (1);
	}
	philos[i - 1].max = i;
	i = -1;
	while (++i < philo_main->num_of_philo - 1)
		philos[i].left = &(philos[i + 1].right);
	philos[i].left = &(philos[0].right);
	return (0);
}

int	is_died(t_philos *philos, t_main_philo *philo_main)
{
	int			i;
	struct 		timeval tmp;
	long int	timer;

	i = 0;
	while (1)
	{
		gettimeofday(&(tmp), 0);
		timer = (tmp.tv_sec - philo_main->global_time.tv_sec) * 1000 + (tmp.tv_usec - philo_main->global_time.tv_usec) / 1000;
		while (i < philo_main->num_of_philo)
		{
//			printf ("TIMER = %d\n", timer - philos[i].ms_eat);
			if (timer - philos[i].ms_eat > philo_main->time_to_die)
			{
				printf ("philo is died # %d\n", (philos[i].index));
//				printf ("main_usec_start = %ld\n", philos[i].start_time.tv_usec);
//				printf ("philo_usec_eat = %ld\n", philos[i].eating_time.tv_usec);
//				printf ("main_sec = %ld\n", philos[i].start_time.tv_sec);
//				printf ("philo_sec = %ld\n", philos[i].eating_time.tv_sec);
				printf ("check_die = %ld, time_to_die = %d \n", timer - philos[i].ms_eat, philo_main->time_to_die);
				i = 0;
				while (i < philo_main->num_of_philo)
				{
				//	pthread_mutex_lock(&(philos[i].time));
					printf ("philo_time [%d] = %ld\n", i, timer - philos[i].ms_eat);
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
		usleep(900);
	}
	return (0);
}

int philo_create(t_main_philo *philo_main)
{
	t_philos	philos[philo_main->num_of_philo];
	int			i;
	
	i = 0;
	gettimeofday(&(philo_main->global_time), 0);
	if (create_list(philos, philo_main))
		return (1);
	while (i < philo_main->num_of_philo)
	{
//		gettimeofday(&(philos[i].start_time), 0);
//		printf ("time_init %ld index = %d\n", philos[i].start_time.tv_usec, i);
		if (pthread_create(&(philos[i].id), 0, (void *) philo_game, (void *)&philos[i]))
			return (0);
		if (pthread_detach((philos[i].id)))
			return (-1);
		i++;
	}
	if (is_died(philos, philo_main))
		return (0);
	return (1);
}