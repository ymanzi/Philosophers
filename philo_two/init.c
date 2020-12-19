/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 08:15:50 by ymanzi            #+#    #+#             */
/*   Updated: 2020/11/22 08:15:52 by ymanzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	lock_semaphore(t_glob *gen)
{
	int	i;

	i = -1;
	while (++i < gen->nb_philo)
		sem_wait(gen->quit);
}

static void	memzero_philo(t_glob *gen)
{
	int	i;

	i = -1;
	while (++i < gen->nb_philo)
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
}

void		init_all(int argc, char **argv, t_glob *gen)
{
	int	i;

	i = -1;
	if (argc == 6)
		gen->nb_eat = ft_atoi(argv[5]);
	gen->alive = 1;
	gen->argc = argc;
	gen->time_die = ft_atoi(argv[2]);
	gen->time_eat = ft_atoi(argv[3]);
	gen->time_sleep = ft_atoi(argv[4]);
	gen->all_eat = 0;
	memzero_philo(gen);
}

void		lunch_thread(int argc, char **argv, t_glob *gen)
{
	int			i;

	i = -1;
	init_all(argc, argv, gen);
	gen->time_start = get_time();
	while (++i < gen->nb_philo)
	{
		lock_semaphore(gen);
		gen->indice = i;
		pthread_create(&(gen->t[i]), NULL, lunch_philo, gen);
	}
	pthread_create(&(gen->t[++i]), NULL, check_death, gen);
	i = -1;
	lock_semaphore(gen);
	lock_semaphore(gen);
}
