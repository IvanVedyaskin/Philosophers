//
// Created by Mohamed Meredith on 4/10/22.
//
#include	"philo.h"

// int free_lists(t_philos **philos)
// {
//     t_philos *tmp;

//     tmp = *philos;
//     while (!tmp)
//     {
//         *philos = (*philos)->next;
//         free(tmp);
//         tmp = *philos;
//     }
//     free(tmp);
//     return (0);
// }

// t_philos    *list_init(t_main_philo *data)
// {
//     t_philos    *tmp;

//     tmp = (t_philos *) malloc(sizeof(t_philos));
//     if (!tmp)
//         return (NULL);
//     tmp->num_must_eat = data->num_must_eat;
//     tmp->time_to_die = data->time_to_die * 1000;
//     tmp->time_to_eat = data->time_to_eat * 1000;
//     tmp->time_to_sleep = data->time_to_sleep * 1000;
//     tmp->next = NULL;
//     pthread_mutex_init(&(tmp->right), NULL);
//     return (tmp);
// }

// int create_list(t_philos **philos, t_main_philo *data)
// {
//     t_philos *tmp;
//     t_philos *head;

//     tmp = list_init(data);
//     if (!tmp)
//         return (free_lists(philos));
//     head = *philos;
//     if (!head)
//         *philos = tmp;
//     else
//     {
//         while (head->next != NULL)
//             head = head->next;
//         head->next = tmp;
//     }
//     return (1);
// }

// void    print_list(t_philos *philos)
// {
//     t_philos	*tmp;

//     tmp = philos;
//     while (tmp != NULL)
//     {
//         printf ("%d\n", tmp->time_to_die);
//         tmp = tmp->next;
//     }
// }

// void    mut_init(t_philos **philos)
// {
//     t_philos    *tmp;
//     t_philos    *tmp2;

//     tmp2 = *philos;
//     if (tmp2->next != NULL)
//     {
//         tmp = (*philos)->next;
//         while (tmp->next != NULL)
//         {
//             tmp2->left = tmp->right;
//             tmp = tmp->next;
//             tmp2 = tmp2->next;
//         }
//         tmp->left = (*philos)->right;
//     }
// }

// void    *philo_game(void *philos)
// {
//     return ;
// }

// int philo_create(t_main_philo *philo_main)
// {
//     int i;
//     t_philos *philos;
//     t_philos *tmp;

//     philos = NULL;
//     i = 1;
//     while (i++ <= philo_main->num_of_philo)
//     {
//         if (!create_list(&philos, philo_main))
//             return (0);
//     }
//     mut_init(&philos);
//     tmp = philos;
//     i = 1;
//     while (i++ <= philo_main->num_of_philo)
//     {
//         pthread_create(&(tmp->id), 0, &philo_game, (void *)tmp);
//         pthread_detach(&(tmp->id));
//         tmp = tmp->next;
//     }
//     return (1);
// }

// (eat.tv_sec - philos->eating_time.tv_sec) * 1000 + (eat.tv_usec - philos->eating_time.tv_usec) / 1000 > philos->time_to_die


void	philo_game(t_philos *philos)
{
	while (1)
	{
		pthread_mutex_lock(&(philos->time));
		if (philos->num != 0)
		{
			pthread_mutex_lock((philos->left));
			printf("Vzyal levyu vilku  № %d\n", philos->num);
			pthread_mutex_lock(&(philos->right));
			printf("Vzyal pravyu vilku  № %d\n", philos->num);
		}
		else
		{
			pthread_mutex_lock(&(philos->right));
			printf("Vzyal pravyu vilku  № %d\n", philos->num);
			pthread_mutex_lock((philos->left));
			printf("Vzyal levyu vilku  № %d\n", philos->num);
		}
		printf("Eating № %d\n", philos->num);
		gettimeofday(&(philos->eating_time), 0);
		pthread_mutex_unlock(&(philos->time));
		usleep(philos->time_to_eat / 2);
		printf ("check_time!!! %ld\n", philos->eating_time.tv_sec);
		pthread_mutex_unlock((philos->left));
		pthread_mutex_unlock(&(philos->right));
		printf ("sleep № %d\n", philos->num);
		usleep(philos->time_to_sleep / 2);
		printf ("thinking № %d\n", philos->num);
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
		philos[i].num = 0;
		pthread_mutex_init(&(philos[i].right), 0);
		pthread_mutex_init(&(philos[i].time), 0);
		i++;
	}
	philos[i - 1].num = i;
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
		// со временем явно что-то не так

		pthread_mutex_lock(&(philos[i].time));
		if (((philos[i].eating_time.tv_sec - philos[i].start_time.tv_sec) * 1000 + \
				(philos[i].eating_time.tv_usec - philos[i].start_time.tv_usec) / 1000) > philo_main->time_to_die)
		{
			printf ("philo is died № %d\n", (philos[i].num));
			printf ("main = %d\n", philos[i].start_time.tv_usec);
			printf ("philo = %d\n", philos[i].eating_time.tv_usec);
			printf ("main = %ld\n", philos[i].start_time.tv_sec);
			printf ("philo = %ld\n", philos[i].eating_time.tv_sec);
			printf ("check_die = %ld \n", (philos[i].eating_time.tv_sec - philos[i].start_time.tv_sec) * 1000 + \
				(philos[i].eating_time.tv_usec - philos[i].start_time.tv_usec) / 1000 + philo_main->time_to_sleep);
			i = 0;
			while (i < philo_main->num_of_philo)
			{
			//	pthread_mutex_lock(&(philos[i].time));
				printf ("philo_time [%d] = %ld\n", i, philos[i].eating_time.tv_sec);
				i++;
			}
			exit(0);
			return (1);
		}
		philos[i].start_time = philos[i].eating_time;
		pthread_mutex_unlock(&(philos[i].time));
		i++;
	}
	i = 0;
	// while (i < philo_main->num_of_philo)
	// {
	// 	pthread_mutex_unlock(&(philos[i].time));
	// 	i++;
	// }
	// i = 0;
	// if ((philo_main->start_time->tv_sec - philos[i].eating_time->tv_sec) * 1000 + (philo_main->start_time->tv_usec - philos[i].eating_time->tv_usec) / 1000 > philos[i].time_to_die)
	// 	printf ("gg\n");
	// while (i < philo_main->num_of_philo)
	// {
		
	// 	// if ((philo_main->start_time->tv_sec - philos[i].eating_time->tv_sec) * 1000 + (philo_main->start_time->tv_usec - philos[i].eating_time->tv_usec) / 1000 > philos[i].time_to_die)
	// 	// {
	// 	// 	printf ("lasdloasdl\n");
	// 	// 	printf ("philo is died № %d\n", i);
	// 	// 	return (1);
	// 	// }
	// 	printf ("%ld\n", philos[i].eating_time.tv_sec);
	// 	pthread_mutex_unlock(&(philos[i].time));
	// 	i++;
	// }
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
		if (i % 2 != 0)
			usleep(20);
		gettimeofday(&(philos[i].start_time), 0);
		pthread_create(&(philos[i].id), 0, (void *) philo_game, (void *)&philos[i]);
		pthread_detach((philos[i].id));
		i++;
	}
	while (1)
	{
		if (is_died(philos, philo_main) == 1)
			return (0);
	}
	return (1);
}