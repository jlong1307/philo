/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlong <jlong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 17:50:00 by jlong             #+#    #+#             */
/*   Updated: 2022/02/08 16:02:58 by jlong            ###   ########.fr       */
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
	int				dead_check;
	int				all_eat;
	pthread_mutex_t	fork[250];
	pthread_mutex_t	eat;
	pthread_mutex_t	write;
	pthread_mutex_t	death;
	pthread_mutex_t	death_check;
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
	int				die;
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
int			check_fork(t_philo *philo, t_data *data);
int			check_is_dead(t_philo *philo);
int			check_all_eat(t_philo *philo);
int			check_argument(int argc);
int			check_error_free(t_philo *philo);
int			check_error_free_init(t_philo *philo);
void		ft_usleep(long int time_in_ms);
void		routine_think(t_philo *philo);
void		routine_eat(t_philo *philo);
void		routine_sleep(t_philo *philo);
void		*routine(void *test_philo);
void		ft_usleep_bis(long int time_in_ms, t_philo philo);
int			ft_check_time(t_philo *philo);

#endif
