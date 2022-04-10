//
// Created by Mohamed Meredith on 4/10/22.
//
#include "philo.h"

int free_lists(t_philos **philos)
{
    t_philos *tmp;

    tmp = *philos;
    while (!tmp)
    {
        *philos = (*philos)->next;
        free(tmp);
        tmp = *philos;
    }
    free(tmp);
    return (0);
}

t_philos    *list_init(t_main_philo *data)
{
    t_philos    *tmp;

    tmp = (t_philos *) malloc(sizeof(t_philos));
    if (!tmp)
        return (NULL);
    tmp->num_must_eat = data->num_must_eat;
    tmp->time_to_die = data->time_to_die * 1000;
    tmp->time_to_eat = data->time_to_eat * 1000;
    tmp->time_to_sleep = data->time_to_sleep * 1000;
    tmp->next = NULL;
    pthread_mutex_init(&(tmp->right), NULL);
    return (tmp);
}

int create_list(t_philos **philos, t_main_philo *data)
{
    t_philos *tmp;
    t_philos *head;

    tmp = list_init(data);
    if (!tmp)
        return (free_lists(philos));
    head = *philos;
    if (!head)
        *philos = tmp;
    else
    {
        while (head->next != NULL)
            head = head->next;
        head->next = tmp;
    }
    return (1);
}

void    print_list(t_philos *philos)
{
    t_philos *tmp;

    tmp = philos;
    while (tmp != NULL)
    {
        printf ("%d\n", tmp->time_to_die);
        tmp = tmp->next;
    }
}

void    mut_init(t_philos **philos)
{
    t_philos    *tmp;
    t_philos    *tmp2;

    tmp2 = *philos;
    if (tmp2->next != NULL)
    {
        tmp = (*philos)->next;
        while (tmp->next != NULL)
        {
            tmp2->left = tmp->right;
            tmp = tmp->next;
            tmp2 = tmp2->next;
        }
        tmp->left = (*philos)->right;
    }
}

void    *philo_game(void *philos)
{
    return ;
}

int philo_create(t_main_philo *philo_main)
{
    int i;
    t_philos *philos;
    t_philos *tmp;

    philos = NULL;
    i = 1;
    while (i++ <= philo_main->num_of_philo)
    {
        if (!create_list(&philos, philo_main))
            return (0);
    }
    mut_init(&philos);
    tmp = philos;
    i = 1;
    while (i++ <= philo_main->num_of_philo)
    {
        pthread_create(&(tmp->id), 0, &philo_game, (void *)tmp);
        pthread_detach(&(tmp->id));
        tmp = tmp->next;
    }
    return (1);
}
