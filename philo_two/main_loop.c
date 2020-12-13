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
		if (gen->time_current - gen->philo[ind].start_sleep >= (gen->time_sleep))
			return (gen);
	}
	return (gen);
}

int			eat_fct(int ind, t_glob *gen)
{
	sem_wait(gen->lock);
	sem_wait(gen->lock);
	if (gen->philo[ind].start == -1)
		gen->philo[ind].start = gen->time_current - (gen->time_current % gen->time_eat);
	gen->philo[ind].start_eat = gen->time_current - (gen->time_current % (gen->time_eat + gen->time_sleep)) + gen->philo[ind].start; // gen->time_current;
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
	sem_post(gen->lock);
	sem_post(gen->lock);
	if (gen->argc == 6 && gen->philo[ind].my_meal >= gen->nb_eat)
		sem_wait(gen->eat);
	return (1);
}

static void	unlock_semaphore(t_glob *gen)
{
	int	i;

	i = -1;
	while (++i < gen->nb_philo)
		sem_post(gen->quit);
}

static void	memzero_philo(t_glob *gen, int i)
{
	gen->philo[i].my_meal = 0;
	gen->philo[i].info = gen;
	gen->philo[i].last_meal = 0;
	gen->philo[i].end_eat = 0;
	gen->philo[i].end_sleep = 0;
	gen->philo[i].start_eat = 0;
	gen->philo[i].start_sleep = 0;
	gen->philo[i].start_boucle = 0;
	gen->philo[i].end_boucle = 0;
	gen->philo[i].start = -1;
}

void		*lunch_philo(void *elem)
{
	int		ind;
	t_glob	*gen;

	gen = (t_glob*)elem;
	ind = gen->indice;
	unlock_semaphore(gen);
	memzero_philo(gen, ind);
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
