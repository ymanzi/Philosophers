#	ifndef PHILO_ONE_H
#	define PHILO_ONE_H

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
#define MEAL_STR " all the Philosophers finished\n"

#define SEM_NAME "fork"
#define	SEM_WRITE "write"
#define	SEM_QUIT "quit"

typedef struct	s_philo t_philo;

typedef struct	s_glob
{
	int				all_eat;
	int				indice;
	t_philo			*list_philo;
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
	pthread_t		t[4];
	sem_t			*write;
	sem_t			*lock;
	sem_t			*quit;
}				t_glob;

typedef struct	s_philo
{
	int		my_meal;
	int		indice;
	long	start_sleep;
	long	end_sleep;
	long	start_eat;
	long	end_eat;
	long	start_boucle;
	long	end_boucle;
	t_glob	*info;
	long	last_meal;
}				t_philo;

/*
 ** main.c
 */
long	get_time(void);
t_glob*	ft_free(int i, t_glob *gen);

/*
 ** init_check.c
 */
void	check_nb_eat(t_glob *g, int *alive);
void	*check_death(void *data);
void	init_all(int argc, char **argv, t_glob *gen, int size);
void	lunch_thread(int argc, char **argv, t_glob *gen, int size);

/*
 ** main_loop.c
 */
void	eat_fct(t_philo *p, int ind);
void	sleep_fct(t_philo *p, int ind);
void	*lunch_philo(void *philo);

/*
 ** write_fct.c
 */
void	write_status_message(t_glob *g);
void	*write_message(void *data);

/*
 **utils.c
 */
int		ft_strlen(char *str);
void	ft_putnbr_fd(long long n, int fd);
int		ft_atoi(const char *nptr);

#	endif
