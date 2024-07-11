/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 17:19:31 by artmarti          #+#    #+#             */
/*   Updated: 2023/10/17 17:19:32 by artmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

size_t	get_time(void)
{
	struct timeval	tv;
	size_t			i;

	gettimeofday(&tv, NULL);
	i = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (i);
}

void	lock_fork(t_data *data, int i, int a)
{
	if (a == 1)
	{
		pthread_mutex_lock(data->philosoph[i].left_fork);
		data->philosoph[i].left_fork_int = 0;
	}
	else if (a == 2)
	{
		pthread_mutex_lock(data->philosoph[i].right_fork);
		data->philosoph[i].right_fork_int = 0;
	}
}

void	check_write(t_data *data, int i)
{
	pthread_mutex_lock(data->philosoph[i].waiting);
	if (check_death(data, i) == 0)
		printf("[%li] Philo %i has taken a fork\n",
			(get_time()), data->philosoph[i].place + 1);
	pthread_mutex_unlock(data->philosoph[i].waiting);
}

void	one_philo(t_data *data, int i)
{
	pthread_mutex_lock(data->philosoph[i].left_fork);
	printf("[%li] Philo %i has taken a fork\n",
		(get_time()), data->philosoph[i].place + 1);
	usleep(data->philosoph[i].die * 1000);
	pthread_mutex_unlock(data->philosoph[i].left_fork);
}

void	destroy_all(t_data	*data, int *nbr_fork)
{
	int	i;

	i = 0;
	while (i < data->nbr_phil)
	{
		pthread_mutex_destroy(&data->fork[i]);
		i++;
	}
	pthread_mutex_destroy(&data->waiting);
	pthread_mutex_destroy(&data->dead);
	free(data->fork);
	free(data->philosoph);
	free(nbr_fork);
	printf("The dinner end\n");
	return ;
}
