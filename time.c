/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlong <jlong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 14:51:33 by jlong             #+#    #+#             */
/*   Updated: 2022/02/08 15:04:55 by jlong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_check_time(t_philo *philo)
{
	if ((philo->data->time_to_eat - philo->data->time_to_sleep >= 50
			|| philo->data->time_to_eat - philo->data->time_to_sleep <= -50))
		return (1);
	return (0);
}

void	ft_usleep_bis(long int time_in_ms, t_philo philo)
{
	long int	start_time;

	start_time = 0;
	start_time = timestamp();
	while ((timestamp() - start_time) < time_in_ms
		&& timestamp() - philo.time_l_eat < philo.data->time_to_die
		&& !philo.data->isdead)
		usleep(time_in_ms / 100);
}
