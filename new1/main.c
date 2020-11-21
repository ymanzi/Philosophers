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

int		ft_free(int i, char *str, t_glob *gen)
{
	if (gen->lock)
		free(gen->lock);
	if (gen->philo)
		free(gen->philo);
	if (gen->write)
		free(gen->write);
	if (gen->quit)
		free(gen->quit);
	if (gen)
		free(gen);
	write(1, str, ft_strlen(str));
	if (i >= 4)
		return (BON);
	return (ERROR);
}

static void	memzero_philo(t_glob *gen)
{
	int	i;

	i = -1;
	while (++i < gen->nb_philo)
	{
		gen->philo[i].my_meal = 0;
		gen->philo[i].info = gen;
		gen->philo[i].last_meal = 0;
		gen->philo[i].end_eat = 0;
		gen->philo[i].end_sleep = 0;
		gen->philo[i].start_eat = 0;
		gen->philo[i].start_sleep = 0;
		gen->philo[i].start_boucle = 0;
		gen->philo[i].end_boucle = 0;
	}
}

t_glob	*unlink_fct(int argc, int size)
{
	int		i;
	t_glob	*gen;

	if (!(gen = (t_glob*)malloc(sizeof(t_glob)))
	|| !(gen->philo = (t_philo*)malloc(sizeof(t_philo) * size)))
	{
		ft_free(-1, "Malloc Error\n", gen);
		return (NULL);
	}
	//memset(gen, 0, sizeof(t_glob));
	if (!(gen->write = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t))) ||
	!(gen->lock = (pthread_mutex_t*)
				malloc(sizeof(pthread_mutex_t) * size)) ||
	!(gen->quit = (pthread_mutex_t*)
				malloc(sizeof(pthread_mutex_t) * size)))
	{
		ft_free(3, "Malloc Error\n", gen);
		return (NULL);
	}
	return (gen);
}

int		main(int argc, char **argv)
{
	t_glob	*gen;
	int		i;

	gen = 0;
	i = 0;
	if (argc < 5 || argc > 6)
		ft_free(-1, "Error nbr of arguments\n", gen);
	else if (ft_atoi(argv[1]) == 0)
		ft_free(-1, "0 philosopher requested\n", gen);
	else
	{
		if (!(gen = unlink_fct(argc, ft_atoi(argv[1]))))
			return (ERROR);
		gen->nb_philo = ft_atoi(argv[1]);
		memzero_philo(gen);
		lunch_thread(argc, argv, gen);
		return (ft_free(4, "Execution Terminee\n", gen));
	}
	return (ERROR);
}
