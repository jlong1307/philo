/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlong <jlong@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 17:53:08 by jlong             #+#    #+#             */
/*   Updated: 2022/01/27 15:53:44 by jlong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_error()
{
    printf("Number of arguments is not correct !\n");
}

void    routine_eat(t_philo *philo)
{
    int id;
    t_data *data;

    data = philo->data;
    id = philo->philo_id;
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

void    check_is_dead(t_philo *philo)
{
    int start;
    int last_meal;
    int dif;

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

int check_all_eat(t_philo *philo)
{
    t_data  *data;

    data = philo->data;
    if (data->number_eat == -1)
        return (1);
    if (philo->nbr_eat > 0)
        return (1);
    return (0);
}

void    *routine(void *test_philo)
{
    t_philo *philo;

    philo = (t_philo *)test_philo;
    if (philo->philo_id % 2)
        usleep(150);
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
        philo->data->dead = 0;
        printf("%lli %d is dead\n", timestamp() - philo->data->start, philo->philo_id);
    }
    return (NULL);
}

int creat_philo(t_data *data, t_philo *philo)
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
    i = 0;
    while (i < data->number_of_philo)
	{
        if (pthread_join(philo[i].thread, NULL))
            return (0);
		i++;
	}
    return (1);
}

int main(int argc, char **av)
{
    t_data	data;
    t_philo	*philo;

    philo = NULL;
    if (!get_data(av, &data))
        return (1);
    philo = malloc(sizeof(t_philo) * data.number_of_philo);
    if (!philo)
    {
        //free philo
        return (1);
    }
	if (!init_mutex(argc, &data, philo))
	{
        //free philo
        return (1);
    }
	if (!creat_philo(&data, philo))
	{
		//free la struct
        //free philo
		return (1);
	}
    return (0);
}
