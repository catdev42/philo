
#ifndef PHILO_H
# define PHILO_H

// # include <fcntl.h>
# include <errno.h>
# include <limits.h>
# include <math.h>
# include <pthread.h>
# include <semaphore.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

/***COLORS***/
# define RED "\x1b[31m"
# define GREEN "\x1b[32m"
# define YELLOW "\x1b[33m"
# define BLUE "\x1b[34m"
# define MAGENTA "\x1b[35m"
# define CYAN "\x1b[36m"
# define RESET "\x1b[0m"

# define BOLD_RED "\x1b[1;31m"
# define BOLD_GREEN "\x1b[1;32m"
# define BOLD_YELLOW "\x1b[1;33m"
# define BOLD_BLUE "\x1b[1;34m"
# define BOLD_MAGENTA "\x1b[1;35m"
# define BOLD_CYAN "\x1b[1;36m"
# define BOLD_RESET "\x1b[1;0m"

# define LOCK 0
# define UNLOCK 1
# define INIT 2
# define DESTROY 3
# define CREATE 4
# define JOIN 5
# define DETACH 6

typedef struct s_table	t_table;
typedef pthread_mutex_t	t_mtx;
/***FORK***/
typedef struct s_fork
{
	t_mtx				fork;
	int					fork_id;
}						t_fork;
/***STRUCTS***/
typedef struct s_philo
{
	int					id;
	long				meals_counter;
	bool				full;
	long				last_meal_time;
	t_fork				*first_fork;
	t_fork				*second_fork;
	pthread_t			thread_id;
	t_table				*table;
	t_mtx				philo_mutex;

	char** sem_names;
}						t_philo;

/***TABLE****/
struct					s_table
{
	long				philo_num;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	long				meals_limit_num;
	//-1 means no input
	long				start_simulation;
	long				active_threads;
	bool				end_simulation;
	bool				all_threads_ready;
	t_mtx				table_mutex;
	t_mtx				write_mutex;
	pthread_t			monitor;

	t_fork				*forks;
	t_philo				*philos;
};

typedef enum e_action
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DIED,
}						t_action;

/*** MAIN ***/
void					wait_all_threads(t_table *table);
void					*monitor_thread(void *data);

/********************/
/***    DINNER.C   ***/
/********************/
void					dinner_start(t_table *table);
void					*dinner_each_philo(void *data);
void					eat(t_philo *philo);
void					philo_sleep(t_philo *philo);
void					philo_think(t_philo *philo);

/********************/
/***   PARSE_INIT ***/
/********************/
void					philo_init(t_table *table);
int						data_init(t_table *table);
int						parse_argv(t_table *table, char **argv);
int						ft_strisnumeric(char *str);

/*****MINILIB_C******/
void					*ft_memset(void *s, int c, size_t n);
long					ft_atol(const char *nptr);
void					*ft_calloc(size_t nmemb, size_t size);

void					ft_bzero(void *s, size_t n);
int						ft_isspace(int c);

size_t					ft_strlen(const char *s);
/********************/
/***   SAFE_FUN   ***/
/********************/
void					*safe_calloc(size_t nmemb, size_t size, t_table *table);
void					handle_mutex_error(int status, int oper,
							t_table *table);
void					safe_mutex_call(t_mtx *mutex, int operation,
							t_table *table);
void					handle_thread_error(int status, int oper,
							t_table *table);

/********************/
/*** ERROR_EXIT.C ***/
/********************/

void					error_exit(const char *error, int error_num,
							t_table *table);
void					clean(t_table *table);
/********************/
/***   SET_GET.C  ***/
/********************/

void					set_bool(t_mtx *mutex, bool *item, bool value,
							t_table *table);
bool					get_bool(t_mtx *mutex, bool *item, t_table *table);
void					set_long(t_mtx *mutex, long *item, long value,
							t_table *table);
long					get_long(t_mtx *mutex, long *item, t_table *table);
bool					sim_finished(t_table *table);

/********************/
/***    UTILS.C   ***/
/********************/
void					precise_usleep(long milsec, t_table *table);
uint64_t				get_time(void);
void					wait_all_threads(t_table *table);
void					write_status(t_philo *philo, t_action action);
#endif
