/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_actions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udumas <udumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 08:48:15 by druina            #+#    #+#             */
/*   Updated: 2024/08/18 16:22:53 by udumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_message(char *str, t_philo *philo, int id)
{
	size_t	time;

	if (check_var(philo->stop_lock, &philo->stop, 0) == 0
		|| check_var(philo->meal_lock, &philo->meal_count,
			philo->program->ntimes) == 1)
		return ;
	sem_wait(philo->program->write_lock);
	time = get_current_time() - philo->program->tstart + 5;
	printf("%ld %d %s\n", time, id, str);
	sem_post(philo->program->write_lock);
}

void	think(t_philo *philo)
{
	if (check_var(philo->stop_lock, &philo->stop, 0) == 0
		|| check_var(philo->meal_lock, &philo->meal_count,
			philo->program->ntimes) == 1)
		return ;
	print_message("is thinking", philo, philo->id);
	if (philo->nphilos % 2 != 0)
		ft_usleep(philo->program->tteat / 1000);
	return ;
}

void	dream(t_philo *philo)
{
	if (check_var(philo->stop_lock, &philo->stop, 0) == 0
		|| check_var(philo->meal_lock, &philo->meal_count,
			philo->program->ntimes) == 1)
		return ;
	print_message("is sleeping", philo, philo->id);
	ft_usleep(philo->program->ttsleep);
}

void	eat(t_philo *philo)
{
	if (check_var(philo->stop_lock, &philo->stop, 0) == 0
		|| check_var(philo->meal_lock, &philo->meal_count,
			philo->program->ntimes) == 1)
		return ;
	sem_wait(philo->program->forks);
	print_message("has taken a fork", philo, philo->id);
	sem_wait(philo->program->forks);
	print_message("has taken a fork", philo, philo->id);
	if (check_var(philo->stop_lock, &philo->stop, 0) == 0)
		return ;
	sem_wait(philo->meal_lock);
	philo->last_meal = get_current_time();
	sem_post(philo->meal_lock);
	print_message("is eating", philo, philo->id);
	ft_usleep(philo->program->tteat);
	sem_post(philo->program->forks);
	sem_post(philo->program->forks);
	ft_incr_int(philo->meal_lock, &philo->meal_count);
}
