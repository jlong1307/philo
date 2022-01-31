/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_untils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlong <jlong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 10:34:50 by jlong             #+#    #+#             */
/*   Updated: 2022/01/31 13:21:57 by jlong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_write(t_philo *philo, int id, char *str)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&(data->write));
	if (philo->nbr_eat != 0 && !philo->data->isdead)
	{
		printf("%lli ", timestamp() - data->start);
		printf("%d ", id);
		printf("%s\n", str);
	}
	pthread_mutex_unlock(&(data->write));
}

long long	timestamp(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}
