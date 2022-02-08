/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_untils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlong <jlong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 13:49:56 by jlong             #+#    #+#             */
/*   Updated: 2022/02/08 16:27:32 by jlong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_argument(int argc)
{
	if (argc < 5 || argc > 6)
	{
		printf("Number of argument is not correct !\n");
		return (0);
	}
	return (1);
}

int	check_fork(t_philo *philo, t_data *data)
{
	int	nbr_philo;
	int	id;

	nbr_philo = philo->data->number_of_philo;
	id = philo->philo_id;
	if (nbr_philo < 2)
	{
		pthread_mutex_lock(&(data->fork[philo->left_fork]));
		check_write(philo, id, "take left fork");
		pthread_mutex_unlock(&(data->fork[philo->left_fork]));
		data->isdead = philo->philo_id;
		return (1);
	}
	return (0);
}

int	check_is_dead(t_philo *philo)
{
	long long	dif;

	pthread_mutex_lock(&(philo->data->death_check));
	dif = (timestamp() - philo->time_l_eat);
	if (!philo->data->isdead && philo->data->dead_check
		&& philo->time_l_eat == 0)
	{
		if (timestamp() - philo->start > philo->data->time_to_die)
		{
			philo->data->dead_check = 0;
			philo->data->isdead = philo->philo_id;
		}
	}
	else if (!philo->data->isdead && philo->data->dead_check
		&& (dif >= philo->data->time_to_die))
	{
		philo->data->dead_check = 0;
		philo->data->isdead = philo->philo_id;
	}
	pthread_mutex_unlock(&(philo->data->death_check));
	if (philo->data->dead_check)
		return (1);
	return (0);
}

int	check_all_eat(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	if (data->number_eat == -1)
		return (1);
	if (philo->nbr_eat > 0)
		return (1);
	else if (philo->nbr_eat == 0)
		philo->data->all_eat++;
	return (0);
}
