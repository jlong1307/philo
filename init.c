/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlong <jlong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 09:24:18 by jlong             #+#    #+#             */
/*   Updated: 2022/02/08 16:04:28 by jlong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_data(char **av, t_data *data)
{
	data->number_of_philo = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->isdead = 0;
	data->dead = 1;
	data->dead_check = 1;
	data->all_eat = 0;
	if (data->number_of_philo < 1 || data->number_of_philo > 250
		|| data->time_to_die < 1
		|| data->time_to_eat < 1
		|| data->time_to_sleep < 1)
		return (0);
	if (av[5])
	{
		data->number_eat = ft_atoi(av[5]);
		if (data->number_eat < 1)
			return (0);
	}
	else
		data->number_eat = -1;
	return (1);
}

void	init_fork(int id, int number_philo, t_philo *philo)
{
	int	n;

	n = id + 1;
	if (n == number_philo)
	{
		philo->left_fork = id;
		philo->right_fork = 0;
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
	philo->philo_id = id + 1;
	philo->nbr_eat = data->number_eat;
	philo->data = data;
	philo->time_l_eat = 0;
	philo->start = data->start;
}

int	init_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philo)
	{
		if (pthread_mutex_init(&data->fork[i], NULL))
			return (0);
		i++;
	}
	if (pthread_mutex_init(&(data->death), NULL))
		return (0);
	if (pthread_mutex_init(&(data->death_check), NULL))
		return (0);
	if (pthread_mutex_init(&(data->write), NULL))
		return (0);
	return (1);
}

int	end_mutex(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < data->number_of_philo)
	{
		if (pthread_join(philo[i].thread, NULL))
			return (0);
		i++;
	}
	i = 0;
	while (i < data->number_of_philo)
	{
		if (pthread_mutex_destroy(&data->fork[i]))
			return (0);
		i++;
	}
	if (pthread_mutex_destroy(&(data->death_check)))
		return (0);
	if (pthread_mutex_destroy(&(data->death)))
		return (0);
	if (pthread_mutex_destroy(&(data->write)))
		return (0);
	return (1);
}
