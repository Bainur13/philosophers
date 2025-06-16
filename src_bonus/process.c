/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udumas <udumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 14:01:57 by druina            #+#    #+#             */
/*   Updated: 2024/08/18 16:38:29 by udumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*check_monitor(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	while (1)
	{
		usleep(100);
		sem_wait(philo->meal_lock);
		if (get_current_time() - philo->last_meal > philo->ttdie)
		{
			sem_wait(philo->program->write_lock);
			ft_set_int(philo->stop_lock, &philo->stop, 1);
			printf("%lld %d %s\n", get_current_time() - philo->program->tstart
				+ 5, philo->id, "died");
			break ;
		}
		if (philo->ntimes != -1 && philo->meal_count >= philo->ntimes)
		{
			ft_set_int(philo->stop_lock, &philo->stop, 2);
			break ;
		}
		sem_post(philo->meal_lock);
	}
	sem_post(philo->meal_lock);
	ft_usleep(10);
	return (NULL);
}

void	one_philo_routine(t_philo *philo)
{
	sem_wait(philo->program->forks);
	print_message("has taken a fork", philo, philo->id);
	ft_usleep(philo->program->ttdie);
	return ;
}

void	philo_routine(t_philo *philo)
{
	pthread_t	thread;

	philo->stop_lock = sem_open("stop_lock", O_CREAT, 0644, 1);
	philo->meal_lock = sem_open("meal_lock", O_CREAT, 0644, 1);
	sem_wait(philo->program->start_lock);
	philo->last_meal = get_current_time();
	pthread_create(&thread, NULL, check_monitor, philo);
	if (philo->id % 2 == 0)
		ft_usleep(25);
	if (philo->program->nphilos == 1)
		one_philo_routine(philo);
	while (check_var(philo->stop_lock, &philo->stop, 0) == 1)
	{
		eat(philo);
		dream(philo);
		think(philo);
	}
	pthread_join(thread, NULL);
	if (check_var(philo->stop_lock, &philo->stop, 1) == 1)
		destroy_all(&philo, 1);
	else
		destroy_all(&philo, 0);
}

void	ft_create_process(t_philo *philo)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	philo->pid = (int *)malloc(sizeof(int) * philo->program->nphilos);
	philo->program->tstart = get_current_time() + 1005;
	while (i < philo->program->nphilos)
	{
		philo->pid[i] = fork();
		if (philo->pid[i] == 0)
		{
			philo->id = i + 1;
			philo_routine(philo);
		}
		i++;
	}
	ft_usleep(1000);
	while (i-- >= 0)
		sem_post(philo->program->start_lock);
}
