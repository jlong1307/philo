/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlong <jlong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 17:50:00 by jlong             #+#    #+#             */
/*   Updated: 2021/12/20 12:11:47 by jlong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <assert.h> 
# include <limits.h>
# include <sys/time.h>


typedef struct s_data
{
	int number_of_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	number_eat;
	long long	start;
	pthread_mutex_t fork[250];
	pthread_mutex_t	eat;
	pthread_mutex_t	write;
}				t_data;

typedef struct	s_philo
{
	int				left_fork;
	int				philo_id;
	pthread_t		thread;
	int				right_fork;
	int				nbr_eat;
	long long		time_l_eat;
	t_data			*data;
}				t_philo;

int			main(int argc, char **av);
int			ft_atoi(const char *s);
long long	timestamp(void);
void		check_write(t_philo *philo, int id, char *str);
#endif
