/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlong <jlong@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 17:53:08 by jlong             #+#    #+#             */
/*   Updated: 2021/12/13 19:06:43 by jlong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_error()
{
    printf("Number of arguments is not correct !\n");
}
int	get_data(int argc, char **av, t_data *data)
{
    &data->number_of_philo = ft_atoi(av[1]);
    &data->time_to_die = ft_atoi(av[2]);
    &data->time_to_eat = ft_atoi(av[3]);
    &data->time_to_sleep = ft_atoi(av[4]);
    &data->number_eat = ft_atoi(av[5]);
    return (1);
}

void	init_struct_philo(t_philo *philo)
{
	philo->left_fork = 0;
	philo->right_fork = 0;
	philo->philo = 0;
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
		init_struct_philo(philo[i]);
		philo->philo = i;
        pthread_create(&philo[i]->thread, NULL, &routine, NULL);
        //verif le tread 
		i++;
	}
    i = 0;
    while (i < data->number_of_philo)
	{
        pthread_join(&philo[i]->thread, NULL);
        //verif le tread 
		i++;
	}
    return (1);
}

int	init_mutex(int argc, t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < data->number_of_philo)
	{
        pthread_mutex_init(philo[i]->fork, NULL);
        if (data->number_eat > 0)
            pthread_mutex_init(philo[i]->eat, NULL);
		i++;
	}
	return (1);
}

int main(int argc, char **av)
{
    t_data	data;
    t_philo	*philo;

    philo = NULL;
    data.number_of_philo = 0;
    data.time_to_die = 0;
    data.time_to_sleep = 0;
    data.time_to_eat = 0;
    data.number_eat = 0;
    if (!get_data(argc, av, &data))
        return (1);
    philo = malloc(sizeof(t_philo) * data.number_of_philo);
    if (!philo)
    {
        free(philo);
        return (1);
    }
	if (!init_mutex(argc, &data, philo))
	{
		
		return (1);
	}
	if (!creat_philo(&data, philo))
	{
		//free la struct
		return (1);
	}
    return (0);
}
