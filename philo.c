/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlong <jlong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 09:23:59 by jlong             #+#    #+#             */
/*   Updated: 2022/02/01 14:21:09 by jlong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	ft_usleep(data->time_to_eat);
	philo->time_l_eat = timestamp();
	philo->nbr_eat--;
	pthread_mutex_unlock(&(data->fork[philo->left_fork]));
	pthread_mutex_unlock(&(data->fork[philo->right_fork]));
}

void	routine_sleep(t_philo *philo)
{
	check_write(philo, philo->philo_id, "is sleeping");
	ft_usleep(philo->data->time_to_sleep);
}

void	*routine(void *test_philo)
{
	t_philo	*philo;

	philo = (t_philo *)test_philo;
	if (philo->philo_id % 2 && philo->data->number_of_philo > 1)
		usleep(10000);
	while (!philo->data->isdead)
	{
		routine_eat(philo);
		check_is_dead(philo);
		check_all_eat(philo);
		if (philo->data->all_eat == philo->data->number_of_philo)
			break ;
		routine_sleep(philo);
		check_write(philo, philo->philo_id, "is thinking");
	}
	ft_usleep(1);
	pthread_mutex_lock(&(philo->data->death));
	if (philo->data->isdead != 0 && philo->data->dead)
	{
		philo->data->dead = 0;
		printf("%lli ", timestamp() - philo->data->start);
		printf("%d is dead\n", philo->philo_id);
	}
	pthread_mutex_unlock(&(philo->data->death));
	return (NULL);
}

int	creat_philo(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	data->start = timestamp();
	while (i < data->number_of_philo)
	{
		init_struct_philo(&philo[i], data, i);
		if (pthread_create(&(philo[i].thread), NULL, routine, &(philo[i])))
			return (0);
		i++;
	}
	if (!end_mutex(data, philo))
		return (0);
	return (1);
}

int	main(int argc, char **av)
{
	t_data	data;
	t_philo	*philo;

	philo = NULL;
	if (!check_argument(argc))
		return (1);
	if (!get_data(av, &data))
	{
		printf("Problem argument !\n");
		return (1);
	}
	philo = malloc(sizeof(t_philo) * data.number_of_philo);
	if (!(philo))
		return (1);
	if (!init_mutex(&data))
		return (check_error_free_init(philo));
	if (!creat_philo(&data, philo))
		return (check_error_free(philo));
	free(philo);
	return (0);
}
