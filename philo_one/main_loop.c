/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 19:18:15 by ymanzi            #+#    #+#             */
/*   Updated: 2020/10/24 15:18:54 by ymanzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_glob		*sleep_fct(int ind, t_glob *gen)
{
	gen->philo[ind].start_sleep = gen->philo[ind].start_eat + gen->time_eat;
	write_message(SLEEP_MSG, ind + 1, gen);
	while (1)
	{
		usleep(500);
		if (gen->time_current - gen->philo[ind].start_sleep
			>= (gen->time_sleep))
			return (gen);
	}
	return (gen);
}

static void	init_eat(int ind, t_glob *gen, int mode)
{
	if (mode == 0)
	{
		pthread_mutex_lock(&(gen->lock[ind]));
		if ((ind + 1) == gen->nb_philo)
			pthread_mutex_lock(&(gen->lock[0]));
		else
			pthread_mutex_lock(&(gen->lock[ind + 1]));
	}
	else
	{
		pthread_mutex_unlock(&(gen->lock[ind]));
		if ((ind + 1) == gen->nb_philo)
			pthread_mutex_unlock(&(gen->lock[0]));
		else
			pthread_mutex_unlock(&(gen->lock[ind + 1]));
		if (gen->argc == 6 && gen->philo[ind].my_meal >= gen->nb_eat)
			pthread_mutex_lock(gen->eat);
	}
}

static void	eat_time_start(int ind, t_glob *gen)
{
	if (gen->philo[ind].start == -1)
	{
		gen->philo[ind].start = gen->time_current -
			(gen->time_current % gen->time_eat);
		gen->philo[ind].start_eat = gen->philo[ind].start;
	}
	else
	{
		if (gen->nb_philo % 2)
			gen->philo[ind].start_eat = gen->philo[ind].start_eat +
				2 * gen->time_eat + gen->time_sleep;
		else
			gen->philo[ind].start_eat = gen->philo[ind].start_eat +
				gen->time_eat + gen->time_sleep;
	}
}

int			eat_fct(int ind, t_glob *gen)
{
	init_eat(ind, gen, 0);
	eat_time_start(ind, gen);
	gen->time_current = get_time() - gen->time_start;
	gen->philo[ind].last_meal = gen->time_current;
	write_message(EAT_MSG, ind + 1, gen);
	while (1)
	{
		usleep(500);
		if (gen->time_current - gen->philo[ind].start_eat >= (gen->time_eat))
			break ;
	}
	gen->philo[ind].my_meal += 1;
	init_eat(ind, gen, 1);
	return (1);
}

void		*lunch_philo(void *elem)
{
	int		ind;
	t_glob	*gen;

	gen = (t_glob*)elem;
	ind = gen->indice;
	pthread_mutex_unlock((gen->quit));
	gen->time_start = get_time();
	gen->time_current = get_time() - gen->time_start;
	while (gen->alive)
	{
		if (!(eat_fct(ind, gen)))
			return (elem);
		gen = sleep_fct(ind, gen);
		if (gen->argc == 6 && gen->philo[ind].my_meal >= gen->nb_eat)
			return (gen);
		gen->time_current = get_time() - gen->time_start;
		write_message(THINK_MSG, ind + 1, gen);
	}
	return (elem);
}
