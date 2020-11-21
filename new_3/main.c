/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 19:39:06 by ymanzi            #+#    #+#             */
/*   Updated: 2020/10/24 17:33:24 by ymanzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval	tp;
	long			milliseconds;

	gettimeofday(&tp, NULL);
	milliseconds = tp.tv_sec * 1000;
	milliseconds += tp.tv_usec / 1000;
	return (milliseconds);
}

void	ft_free(int i, char *str, t_glob *gen)
{
	if (i >= 1)
		sem_close(gen->quit);
	if (i >= 3)
		sem_close(gen->lock);
	if (i >= 2)
		sem_close(gen->write);
	if (i >= 4 && gen->philo)
		free(gen->philo);
	sem_unlink(SEM_WRITE);
	sem_unlink(SEM_NAME);
	sem_unlink(SEM_QUIT);
	if (i >= 0)
		free(gen);
	gen = 0;
	write(1, str, ft_strlen(str));
	if (i < 4)
		exit(ERROR);
	exit(BON);
}

t_glob	*unlink_fct(int size)
{
	t_glob	*gen;
	
	sem_unlink(SEM_WRITE);
	sem_unlink(SEM_NAME);
	sem_unlink(SEM_QUIT);
	if (!(gen = (t_glob*)malloc(sizeof(t_glob))))
		ft_free(-1, "Malloc Error\n", gen);
	memset(gen, 0, sizeof(t_glob));
//	if ((gen->quit = sem_open(SEM_QUIT, O_CREAT, 0660, 0)) == SEM_FAILED)
//		ft_free(0, "Error Semaphore\n");
	if ((gen->write = sem_open(SEM_WRITE, O_CREAT, 0660, 1)) == SEM_FAILED)
		ft_free(1, "Error Semaphore\n", gen);
	if ((gen->lock = sem_open(SEM_NAME, O_CREAT, 0660, size)) == SEM_FAILED)
		ft_free(2, "Error Semaphore\n", gen);
	if (!(gen->philo = (t_philo*)malloc(sizeof(t_philo))))
		ft_free(3, "Malloc Error\n", gen);
	sem_wait(gen->write);
//	memset(gen->philo, 0, sizeof(t_philo));
	return (gen);
}

int		main(int argc, char **argv)
{
	t_glob	*gen;

	gen = 0;
	if (argc < 5 || argc > 6)
		ft_free(-1, "Error nbr of arguments\n", gen);
	else if (ft_atoi(argv[1]) == 0)
		ft_free(-1, "0 philosopher requested\n", gen);
	else
	{
		gen = unlink_fct(ft_atoi(argv[1]));
		gen->nb_philo = ft_atoi(argv[1]);
		lunch_thread(argc, argv, gen);
		ft_free(4, "Execution Terminee\n", gen);
		return (1);
	}
	return (0);
}