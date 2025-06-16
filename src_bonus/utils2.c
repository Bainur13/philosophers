/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udumas <udumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 18:25:05 by udumas            #+#    #+#             */
/*   Updated: 2024/07/23 17:09:03 by udumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_incr_int(sem_t *semaphore, int *dest)
{
	sem_wait(semaphore);
	(*dest)++;
	sem_post(semaphore);
}

void	ft_set_int(sem_t *semaphore, int *dest, int value)
{
	sem_wait(semaphore);
	*dest = value;
	sem_post(semaphore);
}

void	ft_set_long(sem_t *semaphore, long *dest, long value)
{
	sem_wait(semaphore);
	*dest = value;
	sem_post(semaphore);
}

int	check_var(sem_t *semaphore, int *dest, int valut_check)
{
	int	ret;

	sem_wait(semaphore);
	if (*dest == valut_check)
		ret = 1;
	else
		ret = 0;
	sem_post(semaphore);
	return (ret);
}

long	get_var_time(sem_t *semaphore, long dest)
{
	long	ret;

	sem_wait(semaphore);
	ret = dest;
	sem_post(semaphore);
	return (ret);
}
