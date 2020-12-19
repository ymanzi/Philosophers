/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 19:18:15 by ymanzi            #+#    #+#             */
/*   Updated: 2020/12/16 12:37:12 by ymanzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"

static void	memzero_philo(t_glob *gen)
{
	gen->philo->end_eat = 0;
	gen->philo->end_sleep = 0;
	gen->philo->start_eat = 0;
	gen->philo->start_sleep = 0;
	gen->philo->start_boucle = 0;
	gen->philo->end_boucle = 0;
	gen->philo->start = -1;
	gen->philo->print = 0;
}

static void	eat_time_start(t_glob *gen)
{
	gen->time_current = get_time() - gen->time_start;
	if (gen->philo->start == -1)
	{
		gen->philo->start = gen->time_current + 40 -
			((gen->time_current + 40) % gen->time_eat);
		gen->philo->start_eat = gen->philo->start;
	}
	else
	{
		if (((gen->time_current - gen->philo->start_eat) %
		(gen->time_eat + gen->time_sleep) < 40))
			gen->philo->start_eat = gen->philo->start_eat +
				gen->time_eat + gen->time_sleep;
		else
			gen->philo->start_eat = gen->philo->start_eat +
				2 * gen->time_eat + gen->time_sleep;
	}
}

t_glob		*eat_fct(t_glob *gen)
{
	gen->time_current = get_time() - gen->time_start;
	sem_wait(gen->lock);
	sem_wait(gen->lock);
	gen->time_current = get_time() - gen->time_start;
	eat_time_start(gen);
	gen->philo->last_meal = gen->philo->start_eat;
	add_write(EAT_MSG, gen);
	while (gen->philo->start_eat + gen->time_eat > gen->time_current)
		usleep(500);
	gen->philo->my_meal += 1;
	sem_post(gen->lock);
	sem_post(gen->lock);
	if (gen->argc == 6 && gen->philo->my_meal >= gen->nb_eat)
		sem_wait(gen->eat);
	return (gen);
}

t_glob		*sleep_fct(t_glob *gen)
{
	gen->time_current = get_time() - gen->time_start;
	gen->philo->start_sleep = gen->philo->last_meal + gen->time_eat;
	add_write(SLEEP_MSG, gen);
	while (gen->philo->start_sleep + gen->time_sleep > gen->time_current)
	{
		gen->time_current = get_time() - gen->time_start;
		usleep(500);
	}
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
	while (gen->alive)
	{
		gen = eat_fct(gen);
		gen = sleep_fct(gen);
		add_write(THINK_MSG, gen);
	}
	return (elem);
}
