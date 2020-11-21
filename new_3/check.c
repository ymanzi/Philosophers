#include "philo.h"

void	check_nb_eat(t_glob *gen)
{
	if (gen->philo->my_meal >= gen->nb_eat)
	{
		sem_wait(gen->write);
		write_message(MEAL_MSG, gen->indice, gen);
		exit(BON);
	}
}

void	*check_death(void *elem)
{
	t_glob	*g;
	int		i;

	g = elem;
	i = g->indice;
	while (g->alive)
	{
		usleep(500);
		g->time_current = get_time() - g->time_start;
		if (g->time_current - g->philo->last_meal > g->time_die)
		{
			g->alive = 0;
			sem_wait(g->write);
			write_message(DEATH_MSG, i + 1, g);
			break ;
		}
		if (g->argc == 6)
			check_nb_eat(g);
	}
	return (elem);
}