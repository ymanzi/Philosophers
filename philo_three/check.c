/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 16:14:14 by ymanzi            #+#    #+#             */
/*   Updated: 2020/11/22 16:14:16 by ymanzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"

void	write_list(t_glob *gen)
{
	t_list	*elem;
	t_list	*nxt;

	sem_wait(gen->write);
	elem = gen->philo->print;
	while (elem)
	{
		nxt = elem->next;
		write_message(elem->i, gen->indice + 1, gen);
		free(elem);
		elem = nxt;
	}
	gen->philo->print = 0;
	sem_post(gen->write);
}

void	check_nb_eat(t_glob *gen)
{
	if (gen->philo->my_meal >= gen->nb_eat)
	{
		add_write(MEAL_MSG, gen);
		write_list(gen);
		ft_free(4, "", gen);
		exit(BON);
	}
}

void	*check_death(void *elem)
{
	t_glob	*g;
	int		i;

	g = elem;
	i = g->indice;
	while (g->alive)
	{
		usleep(500);
		g->time_current = get_time() - g->time_start;
		write_list(g);
		if (g->time_current - g->philo->last_meal > g->time_die
			&& (g->argc == 5 || g->philo->my_meal < g->nb_eat))
		{
			g->alive = 0;
			add_write(DEATH_MSG, g);
			write_list(g);
			break ;
		}
		if (g->argc == 6)
			check_nb_eat(g);
	}
	return (elem);
}
