#ifndef PHILOSOPHERS_PROTOS_H
# define PHILOSOPHERS_PROTOS_H
# include "philosophers_structs.h"
# include "philosophers.h"
# include <stdbool.h>

typedef unsigned long	t_ul;

/* PARSING */
bool		parsing(int ac, char **av, t_vars *vars);

/* INIT */
bool		init(t_vars *vars);

/* ATOI DEF */
bool		atoi_def(const char *str, int *val);

/* TIME */
bool		print_action(t_philo *philo, int action, t_vars *vars);
bool		ft_usleep(t_ul sleep_time);
bool		get_time(t_ul *val);

/* MEMORY */
bool		memory_cleaning(t_vars *vars);
void		free_philos(t_philo *philo);
int			join_philo_threads(t_vars *vars, int failed_nb);
bool		clean_forks(t_vars *vars, int fork_failed);

/* THREADS */
void		*simulation(void *arg);
void		*monitor(void *arg);

/* Actions */
bool		bedtime(t_philo *philo, t_vars *vars);
bool		eat(t_philo *philo, t_vars *vars);

#endif
