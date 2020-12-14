/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 08:15:42 by ymanzi            #+#    #+#             */
/*   Updated: 2020/11/22 08:15:44 by ymanzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_nb_eat(t_glob *gen, int ind, int *f_to_eat)
{
	if (gen->argc == 6 && gen->philo[ind].my_meal >= gen->nb_eat)
	{
		if (!f_to_eat[ind])
		{
			write_message(MEAL_MSG, ind, gen);
			pthread_mutex_unlock(&(gen->quit[ind]));
			f_to_eat[ind] = 1;
		}
	}
}

void	*check_death(void *elem)
{
	t_glob	*g;
	int		i;
	int		f[((t_glob*)elem)->nb_philo];

	g = elem;
	while (g->alive)
	{
		usleep(500);
		g->time_current = get_time() - g->time_start;
		i = -1;
		while (++i < g->nb_philo)
		{
			if (g->time_current - g->philo[i].last_meal > g->time_die
			&& (g->argc == 5 || g->philo[i].my_meal < g->nb_eat))
			{
				g->alive = 0;
				write_message(DEATH_MSG, i + 1, g);
				return (elem);
			}
			check_nb_eat(g, i, f);
		}
	}
	return (elem);
}
