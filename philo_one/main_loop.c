/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 19:18:15 by ymanzi            #+#    #+#             */
/*   Updated: 2020/10/24 16:17:57 by ymanzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	eat_fct(t_philo *p, int ind)
{
	p->info->time_current = get_time() - p->info->time_start;
	pthread_mutex_lock(&p->info->lock[ind]);
	if (p->info->nb_philo > 1 && (ind + 1) == p->info->nb_philo)
		pthread_mutex_lock(&p->info->lock[0]);
	if (p->info->nb_philo > 1 && (ind + 1) < p->info->nb_philo)
		pthread_mutex_lock(&p->info->lock[ind + 1]);
	p->info->time_current = get_time() - p->info->time_start;
	p->last_meal = p->info->time_current;
	pthread_mutex_lock(p->info->write);
	p->info->indice_wr = (ind + 1);
	p->info->indice_msg = 1;
	p->my_meal += 1;
	if (p->start_boucle)
		p->end_boucle = p->info->time_current - p->start_boucle +
			p->end_boucle;
	p->start_eat = p->info->time_current;
	usleep((p->info->time_eat - p->end_eat - (p->end_boucle / 2)) * 1000);
	pthread_mutex_unlock(&p->info->lock[ind]);
	if (p->info->nb_philo > 1 && (ind + 1) == p->info->nb_philo)
		pthread_mutex_unlock(&p->info->lock[0]);
	if (p->info->nb_philo > 1 && (ind + 1) < p->info->nb_philo)
		pthread_mutex_unlock(&p->info->lock[ind + 1]);
}

void	sleep_fct(t_philo *p, int ind)
{
	p->info->time_current = get_time() - p->info->time_start;
	p->end_eat = p->info->time_current - p->start_eat -
		p->info->time_eat + p->end_eat;
	p->start_sleep = p->info->time_current;
	pthread_mutex_lock(p->info->write);
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
		pthread_mutex_lock(p->info->write);
		p->info->indice_wr = (ind + 1);
		p->info->indice_msg = 3;
	}
	return (philo);
}
