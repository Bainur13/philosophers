/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udumas <udumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 12:48:26 by udumas            #+#    #+#             */
/*   Updated: 2024/08/18 16:02:14 by udumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	start_threads(t_data *data)
{
	int			i;
	pthread_t	arbitrator;

	i = 0;
	if (!data->philosophers)
		return ;
	if (pthread_create(&arbitrator, NULL, arbitrator_routine, data) != 0)
		return ;
	while (i < data->philosophers->nphilo)
	{
		if (pthread_create(&data->philosophers[i].thread, NULL,
				philosopher_routine, &data->philosophers[i]) != 0)
			return ;
		i++;
	}
	i = 0;
	if (pthread_join(arbitrator, NULL) != 0)
		return ;
	while (i < data->philosophers->nphilo)
	{
		if (pthread_join(data->philosophers[i].thread, NULL) != 0)
			return ;
		i++;
	}
	return ;
}
