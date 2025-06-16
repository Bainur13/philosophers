/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udumas <udumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 14:23:28 by druina            #+#    #+#             */
/*   Updated: 2024/08/18 16:35:50 by udumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_all_main(t_philo **philo)
{
	t_philo	*tmp;
	int		i;
	int		status;

	tmp = *philo;
	status = 0;
	i = -1;
	while (++i < tmp->program->nphilos)
	{
		waitpid(-1, &status, 0);
		if (status != 0)
		{
			i = -1;
			while (++i < tmp->program->nphilos)
				kill(tmp->pid[i], SIGKILL);
			break ;
		}
	}
	close_semaphore(tmp->program);
	free((*philo)->pid);
	free(*philo);
}

void	destroy_all(t_philo **philo, int exit_number)
{
	t_philo	*tmp;

	tmp = *philo;
	sem_close(tmp->program->write_lock);
	sem_close(tmp->program->forks);
	sem_close(tmp->program->start_lock);
	sem_close(tmp->meal_lock);
	sem_close(tmp->stop_lock);
	sem_unlink("dead_lock");
	sem_unlink("meal_lock");
	sem_unlink("write_lock");
	sem_unlink("forks");
	free((*philo)->pid);
	free(*philo);
	exit(exit_number);
}

int	check_argcontent(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] != '\0')
	{
		if (arg[i] < '0' || arg[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

int	setup_information(int ac, char **av)
{
	int	nphilo;
	int	ttdie;
	int	tteat;
	int	ttsleep;
	int	ntimes;

	if (!only_digit(av + 1))
		return (printf("Error: wrong arguments\n"), -1);
	nphilo = ft_atoi(av[1]);
	ttdie = ft_atoi(av[2]);
	tteat = ft_atoi(av[3]);
	ttsleep = ft_atoi(av[4]);
	if (ac == 6)
		ntimes = ft_atoi(av[5]);
	else
		ntimes = -1;
	if (nphilo < 1 || ttdie < 60 || tteat < 60 || ttsleep < 60 || (ac == 6
			&& ntimes < 1))
		return (printf("Error: wrong arguments\n"), -1);
	if (ttdie > INT_MAX || tteat > INT_MAX || ttsleep > INT_MAX)
		return (printf("Error: arguments to big\n"), -1);
	return (0);
}

int	main(int ac, char **av)
{
	t_program	program;
	t_philo		*philos;

	if (ac != 5 && ac != 6)
	{
		printf("Error: wrong number of arguments\n");
		return (0);
	}
	if (setup_information(ac, av) == -1)
		return (0);
	philos = init_program(&program, av);
	ft_create_process(philos);
	destroy_all_main(&philos);
	return (0);
}
