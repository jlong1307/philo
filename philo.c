/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlong <jlong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 17:53:08 by jlong             #+#    #+#             */
/*   Updated: 2021/12/20 12:47:30 by jlong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_error()
{
    printf("Number of arguments is not correct !\n");
}

t_data  *get_data(int argc, char **av)
{
    t_data *data;

    data = malloc(sizeof(t_data));
    if (!data)
        return (NULL);
    if (argc == 5 || argc == 6)
    {
        data->number_of_philo = ft_atoi(av[1]);
        data->time_to_die = ft_atoi(av[2]);
        data->time_to_eat = ft_atoi(av[3]);
        data->time_to_sleep = ft_atoi(av[4]);
        if (argc == 6)
            data->number_eat = ft_atoi(av[5]);
        else
            data->number_eat = 1;
    }
    //verifie les donnes 
    return (data);
}

void    init_fork(int id, int number_philo, t_philo *philo)
{
    if (id == number_philo)
    {
        philo->left_fork = id;
        philo->right_fork = 1;
    }
    else
    {
        philo->left_fork = id;
        philo->right_fork = id + 1;
    }
}

void	init_struct_philo(t_philo *philo, t_data *data, int id)
{
    init_fork(id, data->number_of_philo, philo);
	philo->philo_id = id;
    philo->nbr_eat = data->number_eat;
    philo->data = data;
}

void    routine_eat(t_philo *philo)
{
    //Faire le mutex fourchette gauche
    //faire le mutex fourchette droite
    //Quand il a les deux fourchette il peut manger
    //Puis il dort quqnd il a fini et il libere les fourchette
    int id;
    t_data *data;

    data = philo->data;
    id = philo->philo_id;
    pthread_mutex_lock(&(data->fork[philo->left_fork]));
    //printf("%lli ", timestamp() - data->start);
   // printf("philosopher %d take left fork\n", id);
    check_write(philo, id, "take left fork");
    pthread_mutex_lock(&(data->fork[philo->right_fork]));
   // printf("%lli ", timestamp() - data->start);
   // printf("philosopher %d take right fork\n", id);
    check_write(philo, id, "take right fork");
    pthread_mutex_lock(&(data->eat));
   // printf("%lli ", timestamp() - data->start);
   // printf("philosopher %d is eating\n", id);
    check_write(philo, id, "is eating");
    usleep(data->time_to_eat);
    pthread_mutex_unlock(&(data->eat));
   // printf("%lli ", timestamp() - data->start);
   // printf("philosopher %d is sleeping\n", id);
    check_write(philo, id, "is sleeping");
    usleep(data->time_to_sleep);
    pthread_mutex_unlock(&(data->fork[philo->left_fork]));
    pthread_mutex_unlock(&(data->fork[philo->right_fork]));
}

void    *routine(void *test_philo)
{
    t_philo *philo;
    //int     id;

    philo = (t_philo *)test_philo;
    //id = philo->philo_id;
    if (philo->philo_id % 2)
        usleep(50);
    while (philo->nbr_eat)
    {
        routine_eat(philo);
        //apres manger on doit dormir et penser
        //calculer le temps
        printf("%lli ", timestamp() - philo->data->start);
        printf("%d is thinking\n", philo->philo_id);
        usleep(50);
        philo->nbr_eat--;
    }
    return (NULL);
}

int creat_philo(t_data *data, t_philo *philo)
{
	int	i;

	i = 1;
    data->start = timestamp();
	while (i <= data->number_of_philo)
	{
		init_struct_philo(&philo[i], data, i);
        pthread_create(&(philo[i].thread), NULL, routine, &(philo[i]));
        philo[i].time_l_eat = timestamp();
        i++;
        //verif le tread 
	}
    i = 1;
    while (i <= data->number_of_philo)
	{
        pthread_join(philo[i].thread, NULL);
        //verif le tread 
		i++;
	}
    return (1);
}

int	init_mutex(int argc, t_data *data, t_philo *philo)
{
	int	i;
    (void)argc;
    (void)philo;

	i = 1;
	while (i <= data->number_of_philo)
	{
        pthread_mutex_init(&data->fork[i], NULL);
        //if (data->number_eat > 0)
            //pthread_mutex_init(&philo[i].eat, NULL);
		i++;
	}
    pthread_mutex_init(&(data->write), NULL);
	pthread_mutex_init(&(data->eat), NULL);
	return (1);
}

int main(int argc, char **av)
{
    t_data	*data;
    t_philo	*philo;

    philo = NULL;
    data = NULL;
    if (!(data = get_data(argc, av)))
        return (1);
    philo = malloc(sizeof(t_philo) * data->number_of_philo);
    if (!philo)
    {
        printf("error ici\n");
        return (1);
    }
	if (!init_mutex(argc, data, philo))
	{
		printf("error dwdwdw\n");
		return (1);
	}
	if (!creat_philo(data, philo))
	{
        printf("error llqlq\n");
		//free la struct
		return (1);
	}
    return (0);
}
