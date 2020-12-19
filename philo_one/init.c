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


static void	lock_mutex(t_glob *gen, int nbr)
{
	int	i;

	i = -1;
	if (!nbr)
		i = 0;
	while (++i < gen->nb_philo)
		pthread_mutex_lock(&gen->quit[i]);
	if (nbr && gen->nb_philo == 1)
		pthread_mutex_lock(gen->quit);
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
	while (++i < gen->nb_philo)
	{
		pthread_mutex_init(&(gen->quit[i]), NULL);
		pthread_mutex_init(&(gen->lock[i]), NULL);
	}
	pthread_mutex_init(gen->write, NULL);
	pthread_mutex_init(gen->eat, NULL);
	lock_mutex(gen, 0);
}

void		lunch_thread(int argc, char **argv, t_glob *gen)
{
	int			i;

	i = -1;
	init_all(argc, argv, gen);
	gen->time_start = get_time();
	pthread_mutex_lock(gen->eat);
	while (++i < gen->nb_philo)
	{
		pthread_mutex_lock(gen->quit);
		gen->indice = i;
		pthread_create(&(gen->t[i]), NULL, lunch_philo, gen);
	}
	pthread_create(&(gen->t[++i]), NULL, check_death, gen);
	lock_mutex(gen, 1);
}
