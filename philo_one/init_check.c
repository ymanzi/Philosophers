/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 19:41:36 by ymanzi            #+#    #+#             */
/*   Updated: 2020/10/24 16:28:28 by ymanzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	check_nb_eat(t_glob *g, int *alive)
{
	int	i;
	int	cond;

	if (g->argc == 6)
	{
		cond = 1;
		i = -1;
		while (++i < g->nb_philo)
		{
			if (g->list_philo[i].my_meal < g->nb_eat)
				cond = 0;
		}
		if (cond)
		{
			pthread_mutex_lock(g->write);
			g->indice_wr = i;
			g->indice_msg = MEAL_MSG;
			pthread_mutex_unlock(g->write);
			*alive = 0;
		}
	}
}

void	*check_death(void *data)
{
	t_glob	*g;
	int		i;

	g = (t_glob*)data;
	while (g->alive)
	{
		usleep(500);
		i = -1;
		while (++i < g->nb_philo)
		{
			g->time_current = get_time() - g->time_start;
			if (g->time_current - g->list_philo[i].last_meal > g->time_die)
			{
				g->alive = 0;
				pthread_mutex_lock(g->write);
				g->indice_wr = i + 1;
				g->indice_msg = DEATH_MSG;
				break ;
			}
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
	while (++i < size)
	{
		gen->list_philo[i].my_meal = 0;
		gen->list_philo[i].info = gen;
		gen->list_philo[i].last_meal = 0;
		pthread_mutex_init(&(gen->lock[i]), NULL);
		gen->list_philo[i].indice = i;
	}
	pthread_mutex_init(gen->write, NULL);
	gen->indice_wr = -1;
	gen->indice_msg = -1;
}

void	lunch_thread(int argc, char **argv, t_glob *gen, int size)
{
	pthread_t	t[size + 2];
	int			i;

	i = -1;
	init_all(argc, argv, gen, size);
	gen->time_start = get_time();
	while (++i < size)
	{
		pthread_create(&t[i], NULL, lunch_philo, &gen->list_philo[i]);
		usleep(42);
	}
	pthread_create(&t[i], NULL, check_death, gen);
	usleep(42);
	pthread_create(&t[i + 1], NULL, write_message, gen);
	while (gen->alive)
		;
}
