/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlong <jlong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 12:38:04 by jlong             #+#    #+#             */
/*   Updated: 2022/02/08 16:27:44 by jlong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	routine_think(t_philo *philo)
{
	check_write(philo, philo->philo_id, "is thinking");
	if (ft_check_time(philo))
		ft_usleep_bis(10, *philo);
}

void	routine_sleep(t_philo *philo)
{
	check_write(philo, philo->philo_id, "is sleeping");
	ft_usleep(philo->data->time_to_sleep);
}

void	routine_eat(t_philo *philo)
{
	int		id;
	t_data	*data;

	data = philo->data;
	id = philo->philo_id;
	if (check_fork(philo, data))
		return ;
	pthread_mutex_lock(&(data->fork[philo->left_fork]));
	check_write(philo, id, "take left fork");
	pthread_mutex_lock(&(data->fork[philo->right_fork]));
	check_write(philo, id, "take right fork");
	check_write(philo, id, "is eating");
	philo->time_l_eat = timestamp();
	if (!philo->data->isdead)
		ft_usleep(data->time_to_eat);
	philo->nbr_eat--;
	pthread_mutex_unlock(&(data->fork[philo->left_fork]));
	pthread_mutex_unlock(&(data->fork[philo->right_fork]));
}

void	*routine(void *test_philo)
{
	t_philo	*philo;

	philo = (t_philo *)test_philo;
	if (philo->philo_id % 2 && philo->data->number_of_philo > 1)
		ft_usleep(10);
	while (check_is_dead(philo))
	{
		routine_eat(philo);
		check_all_eat(philo);
		if ((philo->data->all_eat == philo->data->number_of_philo)
			|| philo->data->isdead)
			break ;
		routine_sleep(philo);
		routine_think(philo);
	}
	pthread_mutex_lock(&(philo->data->death));
	if (philo->data->isdead != 0 && philo->data->dead)
	{
		philo->data->dead = 0;
		printf("%lli ", timestamp() - philo->data->start);
		printf("%d is dead\n", philo->data->isdead);
	}
	pthread_mutex_unlock(&(philo->data->death));
	return (NULL);
}
