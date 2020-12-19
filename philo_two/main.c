/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 19:39:06 by ymanzi            #+#    #+#             */
/*   Updated: 2020/12/19 11:06:59 by ymanzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long		get_time(void)
{
	struct timeval	tp;
	long			milliseconds;

	gettimeofday(&tp, NULL);
	milliseconds = tp.tv_sec * 1000;
	milliseconds += tp.tv_usec / 1000;
	return (milliseconds);
}

t_glob		*ft_free(int i, char *str, t_glob *gen)
{
	if (i)
		;
	
	sem_unlink(SEM_WRITE);
	sem_unlink(SEM_NAME);
	sem_unlink(SEM_QUIT);
	sem_unlink(SEM_EAT);
	
	if (gen && gen->t)
	{
		free(gen->t);
	}
	if (gen && gen->philo)
	 	free(gen->philo);
	if (gen)
		free(gen);
	write(1, str, ft_strlen(str));
	return (NULL);
}

t_glob		*unlink_fct(int size)
{
	t_glob	*gen;

	sem_unlink(SEM_WRITE);
	sem_unlink(SEM_NAME);
	sem_unlink(SEM_QUIT);
	sem_unlink(SEM_EAT);
	if (!(gen = (t_glob*)malloc(sizeof(t_glob))))
		return (ft_free(-1, "Malloc Error\n", gen));
	memset(gen, 0, sizeof(t_glob));
	if ((gen->quit = sem_open(SEM_QUIT, O_CREAT, 0660, size)) == SEM_FAILED)
		return (ft_free(0, "Error Semaphore\n", gen));
	if ((gen->write = sem_open(SEM_WRITE, O_CREAT, 0660, 1)) == SEM_FAILED)
		return (ft_free(1, "Error Semaphore\n", gen));
	if ((gen->lock = sem_open(SEM_NAME, O_CREAT, 0660, size)) == SEM_FAILED)
		return (ft_free(2, "Error Semaphore\n", gen));
	if ((gen->eat = sem_open(SEM_EAT, O_CREAT, 0660, 1)) == SEM_FAILED)
		ft_free(2, "Error Semaphore\n", gen);
	if (!(gen->philo = (t_philo*)malloc(sizeof(t_philo) * size)) ||
	!(gen->t = (pthread_t*)malloc(sizeof(pthread_t) * (size + 2))))
		return (ft_free(3, "Malloc Error\n", gen));
	sem_wait(gen->eat);
	return (gen);
}

int			main(int argc, char **argv)
{
	t_glob	*gen;
	int		i;

	gen = 0;
	i = 0;
	if (argc < 5 || argc > 6)
		ft_free(-1, "Error nbr of arguments\n", gen);
	else if (ft_atoi(argv[1]) <= 1)
		ft_free(-1, "2 philosopher is the minimum\n", gen);
	else if (argc == 6 && ft_atoi(argv[5]) <= 0)
		ft_free(-1, "", gen);
	else
	{
		if (!(gen = unlink_fct(ft_atoi(argv[1]))))
			return (ERROR);
		gen->nb_philo = ft_atoi(argv[1]);
		lunch_thread(argc, argv, gen);
		ft_free(4, "", gen);
		return (BON);
	}
	return (ERROR);
}
