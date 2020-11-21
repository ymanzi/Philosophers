#include "philo.h"

static void	lock_mutex(int argc, t_glob *gen)
{
	int	i;

	i = -1;
	while (++i < gen->nb_philo)
		pthread_mutex_lock(&gen->quit[i]);
}

void	init_all(int argc, char **argv, t_glob *gen)
{
	int	i;

	i = -1;
	if (argc == 6)
		gen->nb_eat = ft_atoi(argv[5]);
	gen->alive = 1;
	gen->argc = argc;
	gen->time_die = ft_atoi(argv[2]);
	gen->time_eat = ft_atoi(argv[3]);
	gen->time_sleep = ft_atoi(argv[4]);
	gen->all_eat = 0;
	while (++i < gen->nb_philo)
	{
		pthread_mutex_init(&(gen->quit[i]), NULL);
		pthread_mutex_init(&(gen->lock[i]), NULL);
	}
	pthread_mutex_init(gen->write, NULL);
	lock_mutex(argc, gen);
	pthread_mutex_unlock(gen->quit);
}

void	lunch_thread(int argc, char **argv, t_glob *gen)
{
	int			i;
	pthread_t	t[gen->nb_philo + 1];

	i = -1;
	init_all(argc, argv, gen);
	gen->time_start = get_time();
	while (++i < gen->nb_philo)
	{
		gen->indice = i;
		pthread_mutex_lock(gen->quit);
		pthread_create(&t[i], NULL, lunch_philo, gen);
	}
	pthread_create(&t[++i], NULL, check_death, gen);
	lock_mutex(argc, gen);
}
