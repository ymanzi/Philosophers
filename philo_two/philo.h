/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 16:46:42 by ymanzi            #+#    #+#             */
/*   Updated: 2020/12/01 16:46:46 by ymanzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#	ifndef PHILO_H
#	define PHILO_H

#include <sys/time.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>

#define ERROR 1
#define BON 0
#define FORK_MSG 0
#define FORK_STR " has taken a fork\n"
#define EAT_MSG 1
#define EAT_STR " eating\n"
#define SLEEP_MSG 2
#define SLEEP_STR " sleeping\n"
#define THINK_MSG 3
#define THINK_STR " thinking\n"
#define DEATH_MSG 4
#define DEATH_STR " died\n"
#define MEAL_MSG 5
#define MEAL_STR " finished to eat\n"
#define SEM_NAME "fork"
#define SEM_WRITE "write"
#define SEM_QUIT "quit"
#define SEM_EAT "eat"

struct s_philo;

typedef struct	s_glob
{
	int					all_eat;
	int					indice;
	int					alive;
	int					alive_w;
	int					argc;
	int					nb_philo;
	int					nb_eat;
	int					time_die;
	int					time_eat;
	int					time_sleep;
	long				time_current;
	long				time_start;
	int					indice_wr;
	int					indice_msg;
	sem_t				*write;
	sem_t				*lock;
	sem_t				*quit;
	sem_t				*eat;
	pthread_t			*t;
	struct s_philo		*philo;
}				t_glob;

typedef struct	s_philo
{
	int		start;
	int		my_meal;
	int		indice;
	long	start_sleep;
	long	end_sleep;
	long	start_eat;
	long	end_eat;
	t_glob	*info;
	long	start_boucle;
	long	end_boucle;
	long	last_meal;
}				t_philo;

/*
** main.c
*/
long			get_time(void);
t_glob			*unlink_fct(int size);
t_glob			*ft_free(int i, char *str, t_glob *gen);

/*
** init.c
*/
void			init_all(int argc, char **argv, t_glob *gen);
void			lunch_thread(int argc, char **argv, t_glob *gen);

/*
** check.c
*/
void			check_nb_eat(t_glob *gen, int ind, int *f_to_eat);
void			*check_death(void *elem);

/*
** main_loop.c
*/
int				eat_fct(int ind, t_glob *gen);
t_glob			*sleep_fct(int ind, t_glob *gen);
void			*lunch_philo(void *elem);

/*
** write_fct.c
*/
void			write_status_message(int msg, int wr, t_glob *gen);
void			write_message(int msg, int wr, t_glob *gen);

/*
**utils.c
*/
int				ft_strlen(char *str);
void			ft_putnbr_fd(long long n, int fd);
int				ft_atoi(const char *nptr);

#	endif
