/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 16:14:19 by ymanzi            #+#    #+#             */
/*   Updated: 2020/12/09 17:31:38 by ymanzi           ###   ########.fr       */
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

void	semaphore_end(t_glob *gen, int indice)
{
	if (indice)
	{
		sem_wait(gen->quit);
		sem_post(gen->quit);
	}
	else
	{
		sem_wait(gen->eat);
		sem_post(gen->eat);
	}
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
		gen->pid = pid;
		pthread_create(&gen->t[0], NULL, lunch_philo, gen);
		semaphore_end(gen, 0);
		pthread_create(&gen->t[1], NULL, check_death, gen);
		if (i == gen->nb_philo)
			sem_wait(gen->eat);
		semaphore_end(gen, 1);
		exit(BON);
	}
	waitpid(pid, 0, 0);
}
