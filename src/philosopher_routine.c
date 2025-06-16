/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_routine.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udumas <udumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 16:42:58 by udumas            #+#    #+#             */
/*   Updated: 2024/08/21 18:47:15 by udumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	make_philo_eat(t_philosopher *philo)
{
	if (philo->nphilo == 1)
	{
		pthread_mutex_lock(philo->l_fork);
		print_right_time("has taken a fork", philo);
		ft_usleep(philo->ttdie);
		pthread_mutex_unlock(philo->l_fork);
		return ;
	}
	pthread_mutex_lock(philo->l_fork);
	print_right_time("has taken a fork", philo);
	pthread_mutex_lock(philo->r_fork);
	print_right_time("has taken a fork", philo);
	print_right_time("is eating", philo);
	pthread_mutex_lock(philo->meal_lock);
	philo->eating = 1;
	philo->last_meal = get_time();
	pthread_mutex_unlock(philo->meal_lock);
	ft_usleep(philo->tteat);
	pthread_mutex_lock(philo->meal_lock);
	philo->eating = 0;
	philo->eaten++;
	pthread_mutex_unlock(philo->meal_lock);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}

void	make_philo_sleep_o_think(t_philosopher *philo, int status)
{
	if (status == 0)
	{
		print_right_time("is sleeping", philo);
		ft_usleep(philo->ttsleep);
	}
	else
	{
		print_right_time("is thinking", philo);
		if (philo->nphilo % 2 != 0)
			ft_usleep(philo->tteat / 100);
	}
}

void	*philosopher_routine(void *philo_void)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)philo_void;
	if (philo->id % 2 == 0)
		ft_usleep(1);
	while (dead_o_not_dead(philo) == 0)
	{
		make_philo_eat(philo);
		make_philo_sleep_o_think(philo, 0);
		make_philo_sleep_o_think(philo, 1);
	}
	return ((void *)philo);
}
