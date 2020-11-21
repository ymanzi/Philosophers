#include "philo.h"

void	check_nb_eat(t_glob *gen, int ind)
{
	if (gen->argc == 6 && gen->philo[ind].my_meal >= gen->nb_eat)
	{
		pthread_mutex_lock((gen->write));
		write_message(MEAL_MSG, ind + 1, gen);
	}
}

void	*check_death(void *elem)
{
	t_glob	*g;
	int		i;

	g = elem;
	i = -1;
	while (g->alive)
	{
		usleep(500);
		g->time_current = get_time() - g->time_start;
		while (++i < g->nb_philo)
		{
			if (g->time_current - g->philo[i].last_meal > g->time_die)
			{
				g->alive = 0;
				pthread_mutex_lock((g->write));
				write_message(DEATH_MSG, i + 1, g);
				return (elem);
			}
	//		check_nb_eat(g, i);
		}
	}
	return (elem);
}
