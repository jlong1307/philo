/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_untils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlong <jlong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 13:49:56 by jlong             #+#    #+#             */
/*   Updated: 2022/02/03 11:18:45 by jlong            ###   ########.fr       */
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

void	check_is_dead(t_philo *philo)
{
	int	start;
	int	last_meal;
	int	dif;

	start = philo->start;
	last_meal = philo->time_l_eat;
	dif = last_meal - start;
	if (!philo->data->isdead && (dif > philo->data->time_to_die))
	{
		philo->data->isdead = philo->philo_id;
	}
	else
		philo->start = philo->time_l_eat;
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
