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

#include "philo_one.h"

long	get_time(void)
{
	struct timeval	tp;
	long			milliseconds;

	gettimeofday(&tp, NULL);
	milliseconds = tp.tv_sec * 1000;
	milliseconds += tp.tv_usec / 1000;
	return (milliseconds);
}

t_glob	*ft_free(int i, t_glob *gen)
{
	if (i >= 1)
		sem_close(gen->quit);
	if (i >= 3)
		sem_close(gen->lock);
	if (i >= 2 && gen->write)
		sem_close(gen->write);
	if (i >= 4 && gen->list_philo)
		free(gen->list_philo);
	sem_unlink(SEM_WRITE);
	sem_unlink(SEM_NAME);
	sem_unlink(SEM_QUIT);
	free(gen);
	gen = 0;
	return (0);
}

t_glob	*unlink_fct(int size)
{
	t_glob *gen;

	sem_unlink(SEM_WRITE);
	sem_unlink(SEM_NAME);
	sem_unlink(SEM_QUIT);
	if (!(gen = (t_glob*)malloc(sizeof(t_glob))))
		return (0);
	memset(gen, 0, sizeof(t_glob));
	if ((gen->quit = sem_open(SEM_QUIT, O_CREAT, 0660, 1)) == SEM_FAILED)
		return (ft_free(0, gen));
	if ((gen->write = sem_open(SEM_WRITE, O_CREAT, 0660, 1)) == SEM_FAILED)
		return (ft_free(1, gen));
	if ((gen->lock = sem_open(SEM_NAME, O_CREAT, 0660, size)) == SEM_FAILED)
		return (ft_free(2, gen));
	if (!(gen->list_philo = (t_philo*)malloc(sizeof(t_philo) * size)))
		return (ft_free(3, gen));
	return (gen);
}

int		main(int argc, char **argv)
{
	int		size;
	t_glob	*gen;

	if (argc < 5 || argc > 6)
		write(1, "Error number of params\n", 23);
	else if (ft_atoi(argv[1]) == 0)
		write(1, "0 philosopher requested\n", 24);
	else
	{
		size = ft_atoi(argv[1]);
		if (!(gen = unlink_fct(size)))
			return (0);
		sem_wait(gen->quit);
		lunch_thread(argc, argv, gen, size);
		ft_free(4, gen);
		return (1);
	}
	return (0);
}
