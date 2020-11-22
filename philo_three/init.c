/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 16:14:19 by ymanzi            #+#    #+#             */
/*   Updated: 2020/11/22 16:14:21 by ymanzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_all(int argc, char **argv, t_glob *gen)
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
	gen->philo->my_meal = 0;
	gen->philo->last_meal = 0;
	gen->philo->indice = i;
	gen->indice_wr = -1;
	gen->indice_msg = -1;
}

void	lunch_thread(int argc, char **argv, t_glob *gen)
{
	int		i;
	pid_t	pid;

	pid = 0;
	i = -1;
	init_all(argc, argv, gen);
	sem_post(gen->write);
	while (!pid && ++i < gen->nb_philo)
		pid = fork();
	if (i)
	{
		gen->indice = i - 1;
		pthread_create(&gen->t[0], NULL, lunch_philo, gen);
		usleep(42);
		pthread_create(&gen->t[1], NULL, check_death, gen);
		sem_wait(gen->quit);
		sem_post(gen->quit);
		exit(BON);
	}
	waitpid(pid, 0, 0);
}
