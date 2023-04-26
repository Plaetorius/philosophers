#ifndef PHILOSOPHERS_STRUCTS_H
# define PHILOSOPHERS_STRUCTS_H
# include "philosophers_protos.h"
# include "philosophers.h"
# include <pthread.h>
# include <stdbool.h>

enum e_fork_state
{
	NO_FORK,
	LEFT_FORK,
	RIGHT_FORK,
	BOTH_FORKS
};

typedef struct s_vars	t_vars;
typedef unsigned long	t_ul;

typedef struct s_philo
{
	pthread_t			thread;
	pthread_mutex_t		fork;
	int					nb;
	t_ul				last_eat;
	int					meal_number;
	bool				is_eating;
	enum e_fork_state	fork_state;
	struct s_philo		*next;
	struct s_philo		*prev;
	t_vars				*vars;
}				t_philo;

typedef struct s_vars
{
	int					nb_philo;
	int					ttd;
	int					tte;
	int					tts;
	int					ttf;
	t_philo				*philos;
	t_ul				start_time;
	bool				must_finish;
}						t_vars;

/*
	TTD: Time To Die
	TTE: Time To Eat
	TTS: Time To Sleep
	TTF: Times To Finish
	DP: Death Pronounced
	Start Time must be initialized when all threads are created
*/

#endif
