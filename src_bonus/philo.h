/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udumas <udumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 14:20:06 by druina            #+#    #+#             */
/*   Updated: 2024/08/18 16:36:05 by udumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <fcntl.h>
# include <limits.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <unistd.h>

# define PHILO_MAX 300

typedef struct s_program
{
	int			dead_flag;

	int			nphilos;
	int			ntimes;

	long		ttdie;
	long		tteat;
	long		ttsleep;

	long long	tstart;

	sem_t		*dead_lock;
	sem_t		*write_lock;
	sem_t		*forks;
	sem_t		*start_lock;
}				t_program;

typedef struct s_philo
{
	t_program	*program;
	pid_t		*pid;

	long		last_meal;
	int			meal_count;
	int			eating;
	int			dead;
	int			id;

	int			nphilos;
	int			ntimes;
	int			stop;
	long		ttdie;
	long		tteat;
	long		ttsleep;

	sem_t		*meal_lock;
	sem_t		*stop_lock;
}				t_philo;

// Main functions
int				check_argcontent(char *arg);
int				check_valid_args(char **argv);
void			destroy_all(t_philo **philos, int exit_number);

// Initialization

void			close_semaphore(t_program *program);
t_philo			*init_program(t_program *program, char **argv);
void			init_input(t_program *program, char **argv);
void			init_semaphore(t_program *program);
void			init_philo(t_program *program, t_philo **philos);

// PROCESS
void			ft_create_process(t_philo *philo);
void			*monitor(void *pointer);
void			philo_routine(t_philo *philo);

// Actions
void			eat(t_philo *philo);
void			dream(t_philo *philo);
void			think(t_philo *philo);

// Monitor utils
int				dead_loop(t_philo *philo);
int				check_if_all_ate(t_philo *philos);
int				check_if_dead(t_philo *philos);
int				philosopher_dead(t_philo *philo, size_t time_to_die);

// Utils
int				ft_atoi(char *str);
int				ft_usleep(size_t microseconds);
int				ft_strlen(char *str);
void			print_message(char *str, t_philo *philo, int id);
long			get_current_time(void);
int				only_digit(char **av);
void			destroy_all_main(t_philo **philo);

// Utils2
void			ft_incr_int(sem_t *semaphore, int *dest);
void			ft_set_int(sem_t *semaphore, int *dest, int value);
void			ft_set_long(sem_t *semaphore, long *dest, long value);
int				check_var(sem_t *semaphore, int *dest, int valut_check);
long			get_var_time(sem_t *semaphore, long dest);
#endif
