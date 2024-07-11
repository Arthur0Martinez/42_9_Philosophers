/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 10:05:11 by artmarti          #+#    #+#             */
/*   Updated: 2023/10/16 10:05:18 by artmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_main(t_data *data, char **argv, int i, int argc)
{
	if (argc == 6)
		data->nbr_meals_needed = ft_atoi(argv[5]);
	else
		data->nbr_meals_needed = -1;
	data->fork = malloc(sizeof(pthread_mutex_t) * i);
	data->philosoph = malloc(sizeof(t_philosoph) * i);
	data->nbr_phil = i;
	data->nbr_phil2 = i;
	data->ddie = ft_atoi(argv[2]);
	if (ft_atoi(argv[2]) < 1)
		return (1);
	data->deat = ft_atoi(argv[3]);
	if (ft_atoi(argv[3]) < 1)
		return (1);
	data->dsleep = ft_atoi(argv[4]);
	if (ft_atoi(argv[4]) < 1)
		return (1);
	data->endeath = 0;
	pthread_mutex_init(&data->waiting, NULL);
	pthread_mutex_init(&data->dead, NULL);
	printf("\nThe dinner begin\n");
	return (0);
}

void	*during_dinner(void *vdata)
{
	t_data	*data;
	int		i;

	data = (t_data *)vdata;
	pthread_mutex_lock(&data->waiting);
	i = data->nbr_phil - data->nbr_phil2--;
	pthread_mutex_unlock(&data->waiting);
	while (check_death(data, i) == 0)
	{
		can_eat(data, i);
		eating(data, i);
		sleeping(data, i);
		thinking(data, i);
	}
	return (NULL);
}

void	launch_dinner(t_data *data)
{
	int	i;

	data->get_time = get_time();
	pthread_create(&data->monitoring, NULL, &monitor, data);
	i = 0;
	while (i < data->nbr_phil)
	{
		pthread_create(&data->philosoph[i].philo, NULL, &during_dinner, data);
		i++;
	}
	i = 0;
	while (i < data->nbr_phil)
	{
		pthread_join(data->philosoph[i].philo, NULL);
		i++;
	}
	pthread_join(data->monitoring, NULL);
}

void	add_philo(t_data *data, int i, int *nbr_fork)
{
	data->philosoph[i].place = i;
	data->philosoph[i].nbrfork = 0;
	data->philosoph[i].left_fork = &data->fork[i];
	data->philosoph[i].right_fork = &data->fork[(i + 1) % data->nbr_phil];
	data->philosoph[i].waiting = &data->waiting;
	data->philosoph[i].dead = &data->dead;
	data->philosoph[i].left_fork_int = nbr_fork[i];
	data->philosoph[i].right_fork_int = nbr_fork[(i + 1) % data->nbr_phil];
	data->philosoph[i].die = data->ddie;
	data->philosoph[i].eat = data->deat;
	data->philosoph[i].sleep = data->dsleep;
	data->philosoph[i].last_meal = 0;
	data->philosoph[i].nbr_meals = 0;
	data->philosoph[i].deadd = 0;
}

int	main(int argc, char **argv)
{
	t_data	data;
	int		i;
	int		y;
	int		*nbr_fork;

	if (argc != 5 && argc != 6)
		return (0);
	y = -1;
	i = ft_atoi(argv[1]);
	if (i < 1)
		return (1);
	if (init_main(&data, argv, i, argc) == 1)
		return (1);
	nbr_fork = malloc(sizeof(int) * i);
	while (++y < i)
	{
		pthread_mutex_init(&data.fork[y], NULL);
		nbr_fork[y] = 1;
	}
	y = -1;
	while (++y < i)
		add_philo(&data, y, nbr_fork);
	launch_dinner(&data);
	destroy_all(&data, nbr_fork);
	return (0);
}
