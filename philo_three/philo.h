/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 16:46:52 by ymanzi            #+#    #+#             */
/*   Updated: 2020/12/16 13:44:15 by ymanzi           ###   ########.fr       */
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
#include <signal.h>
#include <sys/types.h>

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
#define MEAL_STR "                   finished to eat\n"
#define SEM_NAME "fork"
#define SEM_WRITE "write"
#define SEM_QUIT "quit"
#define SEM_EAT "eat"

struct s_philo;

typedef struct	s_list
{
	int				i;
	struct s_list	*next;
}				t_list;

typedef struct	s_glob
{
	int				all_eat;
	int				indice;
	int				alive;
	int				alive_w;
	int				argc;
	int				nb_philo;
	int				nb_eat;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	long			time_current;
	long			time_start;
	int				indice_wr;
	int				indice_msg;
	pthread_t		t[2];
	sem_t			*write;
	sem_t			*lock;
	sem_t			*quit;
	sem_t			*eat;
	pid_t			pid;
	struct s_philo	*philo;
}				t_glob;

typedef struct	s_philo
{
	int		my_meal;
	int		indice;
	long	start_sleep;
	long	start_sleep2;
	long	end_sleep;
	long	start_eat;
	long	start_eat2;
	long	end_eat;
	long	start;
	t_glob	*info;
	long	start_boucle;
	long	end_boucle;
	long	last_meal;
	t_list	*print;
}				t_philo;

/*
** main.c
*/
long			get_time(void);
void			ft_free(int i, char *str, t_glob *gen);

/*
** init.c
*/
void			init_all(int argc, char **argv, t_glob *gen);
void			lunch_thread(int argc, char **argv, t_glob *gen);
void			semaphore_end(t_glob *gen, int indice);

/*
** check.c
*/
void			check_nb_eat(t_glob *gen);
void			*check_death(void *elem);

/*
** main_loop.c
*/
t_glob			*eat_fct(t_glob *gen);
t_glob			*sleep_fct(t_glob *gen);
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

/*
** List.c
*/
t_list			*ft_lstnew(int content);
t_list			*ft_lstlast(t_list *lst);
void			ft_lstadd_back(t_list **alst, t_list *new);
void			ft_lstclear(t_list **lst);
void			add_write(int elem, t_glob *gen);

#	endif
