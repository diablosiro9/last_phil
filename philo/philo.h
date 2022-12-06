/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dojannin <dojannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 12:46:42 by dojannin          #+#    #+#             */
/*   Updated: 2022/12/03 06:02:14 by dojannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>
// COMMENT FOR COMPIL : gcc -g -pthread main.c"

typedef struct s_philo
{
	pthread_t			*tab_philo;
	pthread_mutex_t		is_dead;
	pthread_mutex_t		*fork;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*r_fork;
	pthread_mutex_t		eat_msg;
	pthread_mutex_t		sleep_msg;
	pthread_mutex_t		think_msg;
	pthread_mutex_t		die_msg;
	unsigned long long	time_for_dead;
	long				time_for_eat;
	long				time_for_sleep;
	int					last_meal;
	useconds_t			last_time;
	
}t_philo;


typedef	struct	s_all 
{
			
	t_philo			philo;
	int				num_philo;
	unsigned long long	time_act;
	useconds_t		time_start;
	struct timeval	timeval;
	int				num_fork;
	int				actual_philo;
	int				actual_fork;
	int				first_round;
	int				number_eats;
	int				died_philo;
	int				eat_enough;
	/* data */
}t_all;


#endif