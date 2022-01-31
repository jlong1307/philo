/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlong <jlong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 17:50:00 by jlong             #+#    #+#             */
/*   Updated: 2022/01/31 13:20:14 by jlong            ###   ########.fr       */
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
	int				number_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_eat;
	long long		start;
	int				isdead;
	int				dead;
	int				all_eat;
	pthread_mutex_t	fork[250];
	pthread_mutex_t	eat;
	pthread_mutex_t	write;
	pthread_mutex_t	death;
}				t_data;

typedef struct s_philo
{
	int				left_fork;
	int				philo_id;
	pthread_t		thread;
	int				right_fork;
	int				nbr_eat;
	long long		time_l_eat;
	long long		start;
	t_data			*data;
}				t_philo;

int			main(int argc, char **av);
int			ft_atoi(const char *s);
long long	timestamp(void);
void		check_write(t_philo *philo, int id, char *str);
int			get_data(char **av, t_data *data);
int			init_mutex(t_data *data);
void		init_struct_philo(t_philo *philo, t_data *data, int id);
int			end_mutex(t_data *data, t_philo *philo);

#endif
