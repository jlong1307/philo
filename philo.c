/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlong <jlong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 17:53:08 by jlong             #+#    #+#             */
/*   Updated: 2021/12/14 14:57:48 by jlong            ###   ########.fr       */
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
    return (data);
}

void	init_struct_philo(t_philo *philo, t_data *data)
{
	philo->left_fork = 0;
	philo->right_fork = 0;
	philo->philo_id = 0;
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
    
    id = philo->philo_id;
    pthread_mutex_lock(&(philo->data->fork[id]));
    printf("Fourchette id = %d\n", id);
    pthread_mutex_unlock(&(philo->data->fork[id]));
}

void    *routine(void *test_philo)
{
    t_philo *philo;
    int     id;

    philo = (t_philo *)test_philo;
    id = philo->philo_id;
    while (philo->nbr_eat)
    {
        routine_eat(philo);
        pthread_mutex_lock(&(philo->eat));
        printf("eat number == %d of philo number %d\n",philo->nbr_eat,  id);
        //philo->nbr_eat--;
        pthread_mutex_unlock(&(philo->eat));
        philo->nbr_eat--;
    }
    return (NULL);
}

int creat_philo(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
    if (data->number_of_philo < 1 || data->time_to_die < 1 || data->time_to_eat < 1
			|| data->time_to_sleep < 1)
        return 0;
	while (i < data->number_of_philo)
	{
		init_struct_philo(&philo[i], data);
		philo[i].philo_id = i;
        pthread_create(&(philo[i].thread), NULL, routine, &(philo[i]));
        i++;
        //verif le tread 
	}
    i = 0;
    while (i < data->number_of_philo)
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

	i = 0;
	while (i < data->number_of_philo)
	{
        pthread_mutex_init(&data->fork[i], NULL);
        if (data->number_eat > 0)
            pthread_mutex_init(&philo[i].eat, NULL);
		i++;
	}
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
