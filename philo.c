/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlong <jlong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 09:23:59 by jlong             #+#    #+#             */
/*   Updated: 2022/02/08 16:28:31 by jlong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	creat_philo(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	data->start = timestamp();
	while (i < data->number_of_philo)
	{
		init_struct_philo(&philo[i], data, i);
		usleep(1000);
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
