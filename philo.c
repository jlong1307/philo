/* ************************************************************************** */
/*	*/
/*	:::	  ::::::::   */
/*   philo.c	:+:	  :+:	:+:   */
/*	+:+ +:+	 +:+	 */
/*   By: jlong <jlong@student.42.fr>	+#+  +:+	   +#+	*/
/*	+#+#+#+#+#+   +#+	   */
/*   Created: 2021/10/25 17:53:08 by jlong	 #+#	#+#	 */
/*   Updated: 2022/01/31 13:23:49 by jlong	###   ########.fr	   */
/*	*/
/* ************************************************************************** */

#include "philo.h"

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
	usleep(data->time_to_eat * 1000);
	philo->time_l_eat = timestamp();
	philo->nbr_eat--;
	pthread_mutex_unlock(&(data->fork[philo->left_fork]));
	pthread_mutex_unlock(&(data->fork[philo->right_fork]));
}

void	check_is_dead(t_philo *philo)
{
	int	start;
	int	last_meal;
	int	dif;

	start = philo->start;
	last_meal = philo->time_l_eat;
	dif = last_meal - start;
	if (dif > philo->data->time_to_die)
	{
		philo->data->isdead = philo->philo_id;
	}
	else
	{
		philo->start = philo->time_l_eat;
	}
}

int	check_all_eat(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	if (data->number_eat == -1)
		return (1);
	if (philo->nbr_eat > 0)
		return (1);
	return (0);
}

void	*routine(void *test_philo)
{
	t_philo	*philo;

	philo = (t_philo *)test_philo;
	if (philo->philo_id % 2 && philo->data->number_of_philo > 1)
		usleep(1500);
	while (!philo->data->isdead && check_all_eat(philo))
	{
		routine_eat(philo);
		check_is_dead(philo);
		if (philo->data->isdead != 0)
			break ;
		check_write(philo, philo->philo_id, "is sleeping");
		usleep(philo->data->time_to_sleep * 1000);
		check_write(philo, philo->philo_id, "is thinking");
	}
	usleep(1000);
	if (philo->data->isdead != 0 && philo->data->dead)
	{
		pthread_mutex_lock(&(philo->data->write));
		philo->data->dead = 0;
		printf("%lli %d is dead\n", timestamp() - philo->data->start, philo->philo_id);
		pthread_mutex_unlock(&(philo->data->write));
	}
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
	if (argc < 5 || argc > 6)
	{
		printf("Number of argument is not correct !\n");
		return (1);
	}
	if (!get_data(av, &data))
	{
		printf("Problem argument !\n");
		return (1);
	}
	philo = malloc(sizeof(t_philo) * data.number_of_philo);
	if (!(philo))
	{
		return (1);
	}
	if (!init_mutex(&data))
	{
		free(philo);
		return (1);
	}
	if (!creat_philo(&data, philo))
	{
		free(philo);
		return (1);
	}
	free(philo);
	return (0);
}
