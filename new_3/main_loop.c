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



t_glob	*sleep_fct(int ind, t_glob *gen)
{
	gen->time_current = get_time() - gen->time_start;
	gen->philo->end_eat = gen->time_current - gen->philo->start_eat -
		gen->time_eat + gen->philo->end_eat;
	gen->philo->start_sleep = gen->time_current;
	sem_wait(gen->write);
	write_message(SLEEP_MSG, ind + 1, gen);
	usleep((gen->time_sleep - gen->philo->end_sleep - (gen->philo->end_boucle / 2) -
				(gen->philo->end_boucle % 2)) * 1000);
	return (gen);
}

static	void memzero_philo(t_glob *gen)
{
	gen->philo->end_eat = 0;
	gen->philo->end_sleep = 0;
	gen->philo->start_eat = 0;
	gen->philo->start_sleep = 0;
	gen->philo->start_boucle = 0;
	gen->philo->end_boucle = 0;
}

t_glob	*eat_fct(int ind, t_glob *gen)
{
	gen->time_current = get_time() - gen->time_start;
	sem_wait(gen->lock);
	if (gen->nb_philo > 1)
		sem_wait(gen->lock);
	gen->time_current = get_time() - gen->time_start;
	gen->philo->last_meal = gen->time_current;
	sem_wait(gen->write);

	write_message(EAT_MSG, ind + 1, gen);

	gen->philo->my_meal += 1;
	if (gen->philo->start_boucle)
		gen->philo->end_boucle = gen->time_current - gen->philo->start_boucle +
			gen->philo->end_boucle;
	gen->philo->start_eat = gen->time_current;
//printf("%30.5s eat=%d end_eat=%d end_boucle=%d\n", "(1)", gen->time_eat, gen->philo->end_eat, gen->philo->end_boucle);		
	usleep((gen->time_eat - gen->philo->end_eat - (gen->philo->end_boucle / 2)) * 1000);

	sem_post(gen->lock);

	if (gen->nb_philo > 1)
		sem_post(gen->lock);
	return (gen);
}

void	*lunch_philo(void *elem)
{
	int		ind;
	t_glob	*gen;

	gen = (t_glob*)elem;
	memzero_philo(gen);
	ind = gen->indice;
	gen->time_start = get_time();
	while (gen->alive)
	{
		gen = eat_fct(ind, gen);
//printf("%30.5s\n", "(2)");
		if (!gen->alive)
			break ;
		gen = sleep_fct(ind, gen);
		gen->time_current = get_time() - gen->time_start;
		gen->philo->end_sleep = gen->time_current - gen->philo->start_sleep -
			gen->time_sleep + gen->philo->end_sleep;
		gen->philo->start_boucle = gen->time_current;
		if (!gen->alive)
			break ;
		sem_wait(gen->write);
		write_message(THINK_MSG, ind + 1, gen);
	}
	return (elem);
}