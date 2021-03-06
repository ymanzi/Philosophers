/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_fct.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 19:34:10 by ymanzi            #+#    #+#             */
/*   Updated: 2020/10/24 17:13:04 by ymanzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void		write_status_message(int msg, int wr, t_glob *gen)
{
	ft_putnbr_fd((long long)gen->time_current, 1);
	write(1, " ", 1);
	ft_putnbr_fd((long long)wr, 1);
	if (msg == 1)
	{
		write(1, FORK_STR, ft_strlen(FORK_STR));
		ft_putnbr_fd((long long)gen->time_current, 1);
		write(1, " ", 1);
		ft_putnbr_fd((long long)wr, 1);
		write(1, FORK_STR, ft_strlen(FORK_STR));
		ft_putnbr_fd((long long)gen->time_current, 1);
		write(1, " ", 1);
		ft_putnbr_fd((long long)wr, 1);
		write(1, EAT_STR, ft_strlen(EAT_STR));
	}
	else if (msg == 2)
		write(1, SLEEP_STR, ft_strlen(SLEEP_STR));
	else if (msg == 3)
		write(1, THINK_STR, ft_strlen(THINK_STR));
	else if (msg == 4)
		write(1, DEATH_STR, ft_strlen(DEATH_STR));
}

static void	inter_write(t_glob *gen)
{
	sem_post(gen->write);
	if (gen->pid)
		waitpid(gen->pid, 0, 0);
	ft_free(4, "", gen);
	exit(BON);
}

void		write_message(int msg, int wr, t_glob *gen)
{
	int	i;

	i = 0;
	if (msg == 5)
		inter_write(gen);
	else
		write_status_message(msg, wr, gen);
	if (msg == DEATH_MSG)
	{
		sem_post(gen->quit);
		if (gen->pid)
			waitpid(gen->pid, 0, 0);
		ft_free(4, "", gen);
		exit(BON);
	}
}
