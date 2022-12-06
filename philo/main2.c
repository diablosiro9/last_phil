/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dojannin <dojannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 12:49:54 by dojannin          #+#    #+#             */
/*   Updated: 2022/11/19 02:56:51 by dojannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int return_time_of_day()
{
	struct timeval current_time;
	
	gettimeofday(&current_time, NULL);
	printf("seconds : %ld micro seconds : %d\n", current_time.tv_sec, current_time.tv_usec);
	return (0);
}

pthread_t	*tab_thread(pthread_t *tab, int	nombre)
{
	tab = (pthread_t *)malloc(sizeof(pthread_t) * nombre);
	return (tab);
}

void	*function(void *data)
{
	printf("Philo se reveille\n");
	// printf("Thread est mort\n");
	return ((void *)data);
}

void	*eating(void *data)
{
	printf("Philo mange\n");
	return ((void *)data);
} 

pthread_mutex_t	*tab_mutex(int nb)
{
	int	i = 0;
	pthread_mutex_t	*tab;

	tab = malloc(sizeof(pthread_mutex_t) * nb + 1);
	if (!tab)
		return (NULL);
	while (i < nb)
	{
		tab[i] = pthread_mutex_init(&tab[i], NULL);
		i++;
	}
	return (tab);
}

int	main()
{
	pthread_t	*tab;
	int			i;
	int			x;

	i = 0;
	x = 10;
	printf("je te suis\n");
	printf("Return time at start = %d\n", return_time());
	tab = tab_thread(tab, x);
	printf("je te suis\n");
	while (i < x)
	{
		// printf("return time = %d\n", return_time());
		if (i % 2 == 0)
			pthread_create(&tab[i], NULL, &function, i);
		else if (i % 2 != 0)
			pthread_create(&tab[i], NULL, &eating, NULL);
		// printf("i == %d\n", i);
		i++;
	}
	printf("i = %d\n", i);
	pthread_join(tab[5], NULL);
	printf("Return time final = %d\n", return_time());
	return (0);
}
