/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 19:41:36 by ymanzi            #+#    #+#             */
/*   Updated: 2020/10/24 19:04:51 by ymanzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	check_nb_eat(t_glob *g, int *alive)
{
	if (g->argc == 6 && (g->list_philo[g->indice].my_meal >= g->nb_eat))
	{
		g->all_eat = 0;
		if (g->indice == (g->nb_philo - 1))
		{
			sem_wait(g->write);
			g->indice_wr = g->indice;
			g->indice_msg = MEAL_MSG;
			*alive = 0;
		}
	}
}

void	*check_death(void *data)
{
	t_glob	*g;
	int		i;

	g = (t_glob*)data;
	i = g->indice;
	while (g->alive)
	{
		usleep(500);
		g->time_current = get_time() - g->time_start;
		if (g->time_current - g->list_philo[i].last_meal > g->time_die)
		{
			g->alive = 0;
			sem_wait(g->write);
			g->indice_wr = i + 1;
			g->indice_msg = DEATH_MSG;
			break ;
		}
		check_nb_eat(g, &g->alive);
	}
	return (data);
}

void	init_all(int argc, char **argv, t_glob *gen, int size)
{
	int	i;

	i = -1;
	if (argc == 6)
		gen->nb_eat = ft_atoi(argv[5]);
	gen->alive = 1;
	gen->argc = argc;
	gen->nb_philo = size;
	gen->time_die = ft_atoi(argv[2]);
	gen->time_eat = ft_atoi(argv[3]);
	gen->time_sleep = ft_atoi(argv[4]);
	gen->all_eat = 0;
	while (++i < size)
	{
		gen->list_philo[i].my_meal = 0;
		gen->list_philo[i].info = gen;
		gen->list_philo[i].last_meal = 0;
		gen->list_philo[i].indice = i;
	}
	gen->indice_wr = -1;
	gen->indice_msg = -1;
}

void	*fct_quit(void *gen)
{
	t_glob *p;

	p = (t_glob*)gen;
	sem_wait(p->quit);
	p->alive = 0;
	p->alive_w = 1;
	sem_post(p->quit);
	return (gen);
}

void	lunch_thread(int argc, char **argv, t_glob *gen, int size)
{
	int		i;
	pid_t	pid;

	pid = 0;
	i = -1;
	init_all(argc, argv, gen, size);
	while (!pid && ++i < size)
		pid = fork();
	if (i)
	{
		gen->indice = i - 1;
		pthread_create(&gen->t[0], NULL, lunch_philo, &gen->list_philo[i - 1]);
		pthread_create(&gen->t[1], NULL, check_death, gen);
		usleep(42);
		pthread_create(&gen->t[2], NULL, write_message, gen);
		sem_wait(gen->quit);
		sem_post(gen->quit);
		pthread_detach(gen->t[0]);
		pthread_detach(gen->t[1]);
		pthread_detach(gen->t[2]);
		pthread_detach(gen->t[3]);
		exit(0);
	}
	waitpid(pid, 0, 0);
//	usleep(5000);
}
