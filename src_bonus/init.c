/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udumas <udumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 12:05:40 by druina            #+#    #+#             */
/*   Updated: 2024/08/18 16:38:17 by udumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	close_semaphore(t_program *program)
{
	sem_close(program->write_lock);
	sem_close(program->forks);
	sem_close(program->start_lock);
	sem_unlink("write_lock");
	sem_unlink("forks");
	sem_unlink("start_lock");
}

void	init_input(t_program *program, char **av)
{
	program->ttdie = ft_atoi(av[2]);
	program->tteat = ft_atoi(av[3]);
	program->ttsleep = ft_atoi(av[4]);
	program->nphilos = ft_atoi(av[1]);
	if (av[5])
		program->ntimes = ft_atoi(av[5]);
	else
		program->ntimes = -1;
}

void	init_semaphore(t_program *program)
{
	sem_unlink("meal_lock");
	sem_unlink("write_lock");
	sem_unlink("forks");
	sem_unlink("stop_lock");
	sem_unlink("start_lock");
	program->start_lock = sem_open("start_lock", O_CREAT, 0644, 0);
	program->write_lock = sem_open("write_lock", O_CREAT, 0644, 1);
	program->forks = sem_open("forks", O_CREAT, 0644, program->nphilos);
}

t_philo	*init_program(t_program *program, char **av)
{
	t_philo	*philo;

	init_input(program, av);
	init_semaphore(program);
	philo = (t_philo *)malloc(sizeof(t_philo));
	philo->program = program;
	philo->eating = 0;
	philo->stop = 0;
	philo->nphilos = philo->program->nphilos;
	philo->ntimes = philo->program->ntimes;
	philo->ttdie = philo->program->ttdie;
	philo->tteat = philo->program->tteat;
	philo->ttsleep = philo->program->ttsleep;
	if (program->ntimes != -1)
		philo->meal_count = 0;
	else
		philo->meal_count = 0;
	return (philo);
}
