/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 22:27:06 by artmarti          #+#    #+#             */
/*   Updated: 2023/10/16 22:27:07 by artmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_atoi(const char *nptr)
{
	int	i;
	int	resultat;

	i = 0;
	resultat = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == 43 || nptr[i] == 45)
	{
		if (nptr[i] == '-')
			return (-1);
		i++;
	}
	if (!(nptr[i] >= '0' && nptr[i] <= '9'))
		return (-1);
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		resultat *= 10;
		resultat += (nptr[i] - 48);
		i++;
	}
	if (resultat == 0)
		return (0);
	return (resultat);
}

int	can_eat(t_data *data, int i)
{
	if (check_death(data, i) == 1)
		return (0);
	else if (data->nbr_phil == 1)
		one_philo(data, i);
	while (check_death(data, i) == 0)
	{
		if (data->philosoph[i].left_fork_int == 1
			&& data->philosoph[i].right_fork_int == 1)
		{
			if (data->philosoph[i].place % 2 == 0 && check_death(data, i) == 0)
				lock_fork(data, i, 1);
			if (data->philosoph[i].place % 2 != 0 && check_death(data, i) == 0)
				lock_fork(data, i, 1);
			if (data->philosoph[i].place % 2 != 0 && check_death(data, i) == 0)
				lock_fork(data, i, 2);
			if (data->philosoph[i].place % 2 == 0 && check_death(data, i) == 0)
				lock_fork(data, i, 2);
			check_write(data, i);
			check_write(data, i);
			return (0);
		}
	}
	return (0);
}

void	thinking(t_data *data, int i)
{
	pthread_mutex_lock(data->philosoph[i].waiting);
	if (check_death(data, i) == 0)
		printf("[%li] Philo %i is thinking\n",
			(get_time()), data->philosoph[i].place + 1);
	pthread_mutex_unlock(data->philosoph[i].waiting);
}

void	eating(t_data *data, int i)
{
	pthread_mutex_lock(data->philosoph[i].waiting);
	if (check_death(data, i) == 0)
		printf("[%li] Philo %i is eating\n",
			(get_time()), data->philosoph[i].place + 1);
	data->philosoph[i].last_meal = (get_time() - data->get_time);
	data->philosoph[i].nbr_meals++;
	pthread_mutex_unlock(data->philosoph[i].waiting);
	usleep(data->philosoph[i].eat * 1000);
	if (data->philosoph[i].left_fork_int == 0)
		pthread_mutex_unlock(data->philosoph[i].left_fork);
	data->philosoph[i].left_fork_int = 1;
	if (data->philosoph[i].right_fork_int == 0)
		pthread_mutex_unlock(data->philosoph[i].right_fork);
	data->philosoph[i].right_fork_int = 1;
}

void	sleeping(t_data *data, int i)
{
	pthread_mutex_lock(data->philosoph[i].waiting);
	if (check_death(data, i) != 1)
		printf("[%li] Philo %i is sleeping\n",
			(get_time()), data->philosoph[i].place + 1);
	pthread_mutex_unlock(data->philosoph[i].waiting);
	usleep(data->philosoph[i].sleep * 1000);
}
