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
	gen->philo->start_sleep = gen->philo->start_eat + gen->time_eat;
	write_message(SLEEP_MSG, ind + 1, gen);
	while (1)
	{
		usleep(500);
		if (gen->time_current - gen->philo->start_sleep >= (gen->time_sleep))
			return (gen);
	}
	return (gen);
}

static void	memzero_philo(t_glob *gen)
{
	gen->philo->end_eat = 0;
	gen->philo->end_sleep = 0;
	gen->philo->start_eat = 0;
	gen->philo->start_sleep = 0;
	gen->philo->start_boucle = 0;
	gen->philo->end_boucle = 0;
	gen->philo->start = -1;
}

static void	eat_time_start(t_glob *gen)
{
	if (gen->philo->start == -1)
	{
		gen->philo->start = gen->time_current -
			(gen->time_current % gen->time_eat);
		gen->philo->start_eat = gen->philo->start;
	}
	else
	{
		if (((gen->time_current - gen->philo->start_eat) %
		(gen->time_eat + gen->time_sleep) < 20))
			gen->philo->start_eat = gen->philo->start_eat +
				gen->time_eat + gen->time_sleep;
		else
			gen->philo->start_eat = gen->philo->start_eat +
				2 * gen->time_eat + gen->time_sleep;
	}
}

t_glob		*eat_fct(int ind, t_glob *gen)
{
	sem_wait(gen->lock);
	sem_wait(gen->lock);
	eat_time_start(gen);
	gen->time_current = get_time() - gen->time_start;
	gen->philo->last_meal = gen->time_current;
	write_message(EAT_MSG, ind + 1, gen);
	while (1)
	{
		usleep(500);
		if (gen->time_current - gen->philo->start_eat >= (gen->time_eat))
			break ;
	}
	gen->philo->my_meal += 1;
	sem_post(gen->lock);
	sem_post(gen->lock);
	if (gen->argc == 6 && gen->philo->my_meal >= gen->nb_eat)
		sem_wait(gen->eat);
	return (gen);
}

void		*lunch_philo(void *elem)
{
	int		ind;
	t_glob	*gen;

	gen = (t_glob*)elem;
	memzero_philo(gen);
	ind = gen->indice;
	if (ind == gen->nb_philo - 1)
		sem_post(gen->eat);
	else
	{
		sem_wait(gen->eat);
		sem_post(gen->eat);
	}
	gen->time_start = get_time();
	gen->time_current = get_time() - gen->time_start;
	while (gen->alive)
	{
		gen = eat_fct(ind, gen);
		if (!gen->alive)
			break ;
		gen = sleep_fct(ind, gen);
		gen->time_current = get_time() - gen->time_start;
		write_message(THINK_MSG, ind + 1, gen);
	}
	return (elem);
}
