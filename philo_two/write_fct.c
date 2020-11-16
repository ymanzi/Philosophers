/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_fct.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 19:34:10 by ymanzi            #+#    #+#             */
/*   Updated: 2020/10/24 18:47:12 by ymanzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	write_status_message(t_glob *g)
{
	ft_putnbr_fd((long long)g->time_current, 1);
	write(1, " ", 1);
	ft_putnbr_fd((long long)g->indice_wr, 1);
	if (g->indice_msg == 1)
	{
		write(1, FORK_STR, ft_strlen(FORK_STR));
		ft_putnbr_fd((long long)g->time_current, 1);
		write(1, " ", 1);
		ft_putnbr_fd((long long)g->indice_wr, 1);
		write(1, FORK_STR, ft_strlen(FORK_STR));
		ft_putnbr_fd((long long)g->time_current, 1);
		write(1, " ", 1);
		ft_putnbr_fd((long long)g->indice_wr, 1);
		write(1, EAT_STR, ft_strlen(EAT_STR));
	}
	else if (g->indice_msg == 2)
		write(1, SLEEP_STR, ft_strlen(SLEEP_STR));
	else if (g->indice_msg == 3)
		write(1, THINK_STR, ft_strlen(THINK_STR));
	else if (g->indice_msg == 4)
	{
		write(1, DEATH_STR, ft_strlen(DEATH_STR));
		g->alive_w = 1;
		g->alive = 0;
	}
}

void	*write_message(void *data)
{
	t_glob	*g;
	int		ind;

	g = data;
	while (!g->alive_w)
	{
		if (g->indice_wr != -1 && g->indice_msg != -1)
		{
			if (g->indice_msg == 5)
			{
				ft_putnbr_fd((long long)g->time_current, 1);
				write(1, MEAL_STR, ft_strlen(MEAL_STR));
				g->alive_w = 1;
				break ;
			}
			else
				write_status_message(g);
			ind = g->indice_msg;
			g->indice_msg = -1;
			g->indice_wr = -1;
			sem_post(g->write);
		}
	}
	return (data);
}
