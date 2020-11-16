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

#include "philo_one.h"

void	eat_fct(t_philo *p, int ind)
{
	p->info->time_current = get_time() - p->info->time_start;
	sem_wait(p->info->lock);
	if (p->info->nb_philo > 1)
		sem_wait(p->info->lock);
	p->info->time_current = get_time() - p->info->time_start;
	p->last_meal = p->info->time_current;
	sem_wait(p->info->write);
	p->info->indice_wr = (ind + 1);
	p->info->indice_msg = 1;
	p->my_meal += 1;
	if (p->start_boucle)
		p->end_boucle = p->info->time_current - p->start_boucle +
			p->end_boucle;
	p->start_eat = p->info->time_current;
	usleep((p->info->time_eat - p->end_eat - (p->end_boucle / 2)) * 1000);
	sem_post(p->info->lock);
	if (p->info->nb_philo > 1)
		sem_post(p->info->lock);
}

void	sleep_fct(t_philo *p, int ind)
{
	p->info->time_current = get_time() - p->info->time_start;
	p->end_eat = p->info->time_current - p->start_eat -
		p->info->time_eat + p->end_eat;
	p->start_sleep = p->info->time_current;
	sem_wait(p->info->write);
	p->info->indice_wr = (ind + 1);
	p->info->indice_msg = 2;
	usleep((p->info->time_sleep - p->end_sleep - (p->end_boucle / 2) -
				(p->end_boucle % 2)) * 1000);
}

void	*lunch_philo(void *philo)
{
	t_philo	*p;
	int		ind;

	p = philo;
	ind = p->indice;
	p->info->time_start = get_time();
	while (p->info->alive)
	{
		eat_fct(p, ind);
		if (!p->info->alive)
			break ;
		sleep_fct(p, ind);
		p->info->time_current = get_time() - p->info->time_start;
		p->end_sleep = p->info->time_current - p->start_sleep -
			p->info->time_sleep + p->end_sleep;
		p->start_boucle = p->info->time_current;
		if (!p->info->alive)
			break ;
		sem_wait(p->info->write);
		p->info->indice_wr = (ind + 1);
		p->info->indice_msg = 3;
	}
	return (philo);
}
