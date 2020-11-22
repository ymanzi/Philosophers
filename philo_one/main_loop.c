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
	gen->time_current = get_time() - gen->time_start;
	gen->philo[ind].end_eat = gen->time_current - gen->philo[ind].start_eat -
		gen->time_eat + gen->philo[ind].end_eat;
	gen->philo[ind].start_sleep = gen->time_current;
	pthread_mutex_lock((gen->write));
	write_message(SLEEP_MSG, ind + 1, gen);
	usleep((gen->time_sleep - gen->philo[ind].end_sleep
		- (gen->philo[ind].end_boucle / 2)
		- (gen->philo[ind].end_boucle % 2)) * 1000);
	return (gen);
}

int			eat_fct(int ind, t_glob *gen)
{
	gen->time_current = get_time() - gen->time_start;
	pthread_mutex_lock(&(gen->lock[ind]));
	if (gen->nb_philo > 1 && (ind + 1) == gen->nb_philo)
		pthread_mutex_lock(&(gen->lock[0]));
	else if (gen->nb_philo > 1 && (ind + 1) < gen->nb_philo)
		pthread_mutex_lock(&(gen->lock[ind + 1]));
	gen->time_current = get_time() - gen->time_start;
	gen->philo[ind].last_meal = gen->time_current;
	pthread_mutex_lock((gen->write));
	write_message(EAT_MSG, ind + 1, gen);
	if (gen->philo[ind].start_boucle)
		gen->philo[ind].end_boucle = gen->time_current -
		gen->philo[ind].start_boucle + gen->philo[ind].end_boucle;
	gen->philo[ind].start_eat = gen->time_current;
	usleep((gen->time_eat - gen->philo[ind].end_eat -
	(gen->philo[ind].end_boucle / 2)) * 1000);
	gen->philo[ind].my_meal += 1;
	pthread_mutex_unlock(&(gen->lock[ind]));
	if (gen->nb_philo > 1 && (ind + 1) == gen->nb_philo)
		pthread_mutex_unlock(&(gen->lock[0]));
	else if (gen->nb_philo > 1 && (ind + 1) < gen->nb_philo)
		pthread_mutex_unlock(&(gen->lock[ind + 1]));
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
	while (gen->alive)
	{
		if (!(eat_fct(ind, gen)))
			return (elem);
		gen = sleep_fct(ind, gen);
		if (gen->argc == 6 && gen->philo[ind].my_meal >= gen->nb_eat)
			return (gen);
		gen->time_current = get_time() - gen->time_start;
		gen->philo[ind].end_sleep = gen->time_current -
	gen->philo[ind].start_sleep - gen->time_sleep + gen->philo[ind].end_sleep;
		gen->philo[ind].start_boucle = gen->time_current;
		pthread_mutex_lock((gen->write));
		write_message(THINK_MSG, ind + 1, gen);
	}
	return (elem);
}
