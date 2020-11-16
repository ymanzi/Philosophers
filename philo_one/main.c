/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 19:39:06 by ymanzi            #+#    #+#             */
/*   Updated: 2020/10/24 16:26:18 by ymanzi           ###   ########.fr       */
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

int		ft_free(int i, t_glob *gen)
{
	if (i >= 3 && gen->lock)
		free(gen->lock);
	if (i >= 2 && gen->write)
		free(gen->write);
	if (i >= 4 && gen->list_philo)
		free(gen->list_philo);
	free(gen);
	if (i >= 4)
		return (1);
	return (0);
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
		if (!(gen = (t_glob*)malloc(sizeof(t_glob))))
			return (0);
		memset(gen, 0, sizeof(t_glob));
		if (!(gen->write = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t))))
			return (ft_free(1, gen));
		if (!(gen->lock = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t)
						* size)))
			return (ft_free(2, gen));
		if (!(gen->list_philo = (t_philo*)malloc(sizeof(t_philo) * size)))
			return (ft_free(3, gen));
		memset(gen->list_philo, 0, sizeof(t_philo) * size);
		lunch_thread(argc, argv, gen, size);
		return (ft_free(4, gen));
	}
	return (0);
}
