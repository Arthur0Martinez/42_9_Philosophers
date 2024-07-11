/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 22:26:56 by artmarti          #+#    #+#             */
/*   Updated: 2023/10/16 22:26:58 by artmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	finish(t_data *data, int a, int i)
{
	if (a == 1)
	{
		kill_all(data);
		printf("[%li] Philo %i has died\n",
			(get_time()), i + 1);
		data->endeath = 1;
	}
	if (a == 2)
	{
		kill_all(data);
		printf("[%li] All philo have eaten\n",
			(get_time()));
		data->endeath = 1;
	}
}

void	kill_all(t_data	*data)
{
	int	i;

	pthread_mutex_lock(&data->dead);
	i = 0;
	while (i < data->nbr_phil)
	{
		data->philosoph[i].deadd = 1;
		i++;
	}
	pthread_mutex_unlock(&data->dead);
	return ;
}

void	check_if_one_died(t_data	*data, int i, int y)
{
	int		nbr_phil_finish_eat;
	size_t	lst_meal;

	nbr_phil_finish_eat = 0;
	while (++i < data->nbr_phil && data->endeath == 0)
	{
		pthread_mutex_lock(&data->waiting);
		lst_meal = data->philosoph[i].last_meal;
		pthread_mutex_unlock(&data->waiting);
		if ((get_time() - data->get_time) - lst_meal >= data->ddie)
			finish(data, 1, i);
		while (++y < data->nbr_phil && data->nbr_meals_needed > 0
			&& data->endeath == 0)
		{
			pthread_mutex_lock(&data->waiting);
			if (data->philosoph[y].nbr_meals >= data->nbr_meals_needed)
				nbr_phil_finish_eat++;
			pthread_mutex_unlock(&data->waiting);
			if (nbr_phil_finish_eat == data->nbr_phil)
				finish(data, 2, i);
		}
		y = -1;
		nbr_phil_finish_eat = 0;
	}
}

void	*monitor(void *vdata)
{
	t_data	*data;

	data = (t_data *)vdata;
	while (data->endeath != 1)
		check_if_one_died(data, -1, -1);
	return (NULL);
}

int	check_death(t_data *data, int i)
{
	int	a;

	pthread_mutex_lock(data->philosoph[i].dead);
	a = 0;
	if (data->philosoph[i].deadd == 1)
		a = 1;
	pthread_mutex_unlock(data->philosoph[i].dead);
	return (a);
}
