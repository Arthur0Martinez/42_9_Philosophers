/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 22:15:50 by artmarti          #+#    #+#             */
/*   Updated: 2023/10/16 22:15:52 by artmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_philosoph
{
	int				place;
	int				nbrfork;
	int				fork;
	int				left_fork_int;
	int				right_fork_int;
	int				deadd;
	size_t			die;
	size_t			eat;
	size_t			sleep;
	size_t			eaten_enough;
	size_t			nbr_meals;
	size_t			last_meal;
	pthread_t		philo;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*waiting;
	pthread_mutex_t	*dead;
}	t_philosoph;

typedef struct s_data
{
	int				nbr_phil;
	int				nbr_phil2;
	int				endeath;
	size_t			time;
	size_t			ddie;
	size_t			deat;
	size_t			dsleep;
	size_t			nbr_meals_needed;
	size_t			get_time;
	pthread_t		monitoring;
	pthread_mutex_t	*fork;
	pthread_mutex_t	waiting;
	pthread_mutex_t	dead;
	t_philosoph		*philosoph;
}	t_data;

int		check_death(t_data *data, int i);
int		can_eat(t_data *data, int i);
int		ft_atoi(const char *nptr);
void	add_philo(t_data *data, int i, int *nbr_fork);
void	launch_dinner(t_data *data);
void	*during_dinner(void *vdata);
void	*monitor(void *vdata);
void	check_if_one_died(t_data	*data, int i, int y);
void	kill_all(t_data	*data);
void	destroy_all(t_data	*data, int *nbr_fork);
void	sleeping(t_data *data, int i);
void	eating(t_data *data, int i);
void	thinking(t_data *data, int i);
void	one_philo(t_data *data, int i);
void	lock_fork(t_data *data, int i, int a);
void	check_write(t_data *data, int i);
size_t	get_time(void);

#endif