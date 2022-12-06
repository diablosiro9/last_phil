/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dojannin <dojannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 14:45:23 by dojannin          #+#    #+#             */
/*   Updated: 2022/12/03 06:15:36 by dojannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(char *s)
{
	int	i;
	int	res;
	int	sign;
	
	i = 0;
	sign = 1;
	res = 0;
	while (s[i] == '\f' || s[i] == '\t' || s[i] == '\n'
		|| s[i] == '\r' || s[i] == '\v' || s[i] == ' ')
		i++;
	while (s[i] == '+' || s[i] == '-')
	{
		if (s[i] == '-')
			sign *= (-1);
		i++;
	}
	while (s[i] >= '0' && s[i] <= '9')
	{
		res = res * 10 + (s[i] - '0');
		i++;
	}
	return (res * sign);
}

int	ft_atol(char const *s)
{
	int	i;
	long	res;
	long	sign;

	i = 0;
	sign = 1;
	res = 0;
	while (s[i] == '\f' || s[i] == '\t' || s[i] == '\n'
		|| s[i] == '\r' || s[i] == '\v' || s[i] == ' ')
		i++;
	while (s[i] == '+' || s[i] == '-')
	{
		if (s[i] == '-')
			sign *= (-1);
		i++;
	}
	while (s[i] >= '0' && s[i] <= '9')
	{
		res = res * 10 + (s[i] - '0');
		i++;
	}
	return (res * sign);
}

int	do_atoi(char const *s, int i, int res, int new_res)
{	
	while (s[i] >= '0' && s[i] <= '9')
	{
		new_res = res * 10 + (s[i] - '0');
		if (new_res > res)
		{
			write(1, "Error\n", 6);
			exit(1);
		}
		res = new_res;
		i++;
	}
	return (res);
}

unsigned long long	philo_get_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void	error_atoi(int sign, int res)
{
	if (sign == 1 && res == -2147483648)
	{
		write(1, "Error\n", 6);
		exit(1);
	}
}

pthread_t	*tab_thread(pthread_t *tab, int	nombre)
{
	tab = (pthread_t *)malloc(sizeof(pthread_t) * nombre);
	return (tab);
}

pthread_mutex_t	*tab_mutex(pthread_mutex_t *tab, int nb)
{
	int	i;

	i = 0;
	tab = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * nb);
	if (!tab)
		return (NULL);
	while (i < nb)
	{
		pthread_mutex_init(&tab[i], NULL);
		i++;
	}
	return (tab);
}

int	parsing(int ac, char **av, t_all *all)
{
	int	i;

	i = 0;
	gettimeofday(&all->timeval, NULL);
	all->num_philo = ft_atoi(av[1]);
	if (all->num_philo < 0)
	{
		printf("Error: Number's Philos is negative.\n");
		return (0);
	}
	all->philo.tab_philo = tab_thread(all->philo.tab_philo, all->num_philo);
	all->philo.fork = tab_mutex(all->philo.fork, ft_atoi(av[1]));
	all->philo.left_fork = tab_mutex(all->philo.left_fork, ft_atoi(av[1]));
	all->philo.r_fork = tab_mutex(all->philo.r_fork, ft_atoi(av[1]));
	all->philo.time_for_dead = ft_atol(av[2]);
	all->philo.fork = tab_mutex(all->philo.fork, all->num_philo);
	all->philo.time_for_eat = ft_atol(av[3]);
	all->philo.time_for_sleep = ft_atol(av[4]);
	if (ac == 6)
		all->philo.last_meal = ft_atoi(av[5]);
	all->num_fork = ft_atoi(av[1]);
	all->time_start = philo_get_time();
	all->time_act = philo_get_time();
	all->actual_philo = 0;
	all->first_round = 1;
	all->died_philo = 0;
	all->eat_enough = 0;
	pthread_mutex_init(&all->philo.eat_msg, NULL);
	pthread_mutex_init(&all->philo.sleep_msg, NULL);
	pthread_mutex_init(&all->philo.think_msg, NULL);
	pthread_mutex_init(&all->philo.die_msg, NULL);
	return (1);
}

int	ft_usleep(useconds_t usec)
{
	useconds_t		start;
	useconds_t		after;

	start = philo_get_time();
	after = start;
	while (after - start < usec)
	{
		if (usleep(usec) == -1)
			return (-1);
		after = philo_get_time();
	}
	return (0);
}

void	*distrib_fork(void *all)
{
	useconds_t	end;

	end = 0;
	if (((t_all *)(all))->first_round == 1)
		((t_all *)(all))->time_act = ((t_all *)(all))->time_start;
	else
		((t_all *)(all))->time_act = philo_get_time();
	end = ((t_all *)(all))->time_act - ((t_all *)(all))->time_start;
	pthread_mutex_lock(&((t_all *)(all))->philo.r_fork[((t_all *)(all))->actual_fork]);
	pthread_mutex_lock(&((t_all *)(all))->philo.left_fork[((t_all *)(all))->actual_fork - 1]);
	printf("%u %d has taken a fork\n", end, ((t_all *)(all))->actual_philo);
	printf("%u %d has taken a fork\n", end, ((t_all *)(all))->actual_philo);



	return (all);
}

void	*eat(void *all)
{
	useconds_t	end;

	((t_all *)(all))->time_act = philo_get_time();
	end = ((t_all *)(all))->time_act - ((t_all *)(all))->time_start;
	pthread_mutex_lock(&((t_all *)(all))->philo.eat_msg);
	printf("%u %d is eating\n", end, ((t_all *)(all))->actual_philo);
	ft_usleep(((t_all *)(all))->philo.time_for_eat);
	pthread_mutex_unlock(&((t_all *)(all))->philo.r_fork[((t_all *)(all))->actual_fork]);
	pthread_mutex_unlock(&((t_all *)(all))->philo.left_fork[((t_all *)(all))->actual_fork - 1]);
	pthread_mutex_unlock(&((t_all *)(all))->philo.eat_msg);
	((t_all *)(all))->time_act = philo_get_time();
	return (all);

}

void	*philo_dead(void *data)
{
	t_all	*all;

	all = (t_all *)data;
	while (1)
	{
		printf("debut\n");
		printf("philo_get_time() == %llu\n", philo_get_time());
		printf("all->time_act == %llu\n",  all->time_act);
		printf("philo_get_time() - all->time_act == %llu\n", philo_get_time() - all->time_act );
		printf(" all->philo.time_for_dead == %llu\n",   all->philo.time_for_dead);
		if (philo_get_time() - all->time_act >= all->philo.time_for_dead)
		{
			
			all->died_philo = 1;
			if (all->eat_enough == 1)
			{
				printf("All philo eat_enough.\n");
				break ;
			}
			printf("Philo is died\n");
			return (NULL);
		}
		ft_usleep(2000);
		printf("fin\n");
	}
	return (NULL);
}

void	*routine(void *all)
{
	useconds_t	end;

	end = 0;
	distrib_fork(all);
	eat(all);
	printf("passage par la\n");
	((t_all *)(all))->time_act = philo_get_time();
	end = ((t_all *)(all))->time_act - ((t_all *)(all))->time_start;
	((t_all *)(all))->philo.last_time = ((t_all *)(all))->time_act - ((t_all *)(all))->time_start;
	pthread_mutex_lock(&((t_all *)(all))->philo.sleep_msg);
	// if (((t_all *)(all))->died_philo == 1)
	// {
	// 	pthread_mutex_lock(&((t_all *)(all))->philo.die_msg);			
	// 	pthread_mutex_lock(&((t_all *)(all))->philo.die_msg);
	// 	printf("Philo is died\n");
	// 	((t_all *)(all))->died_philo = 1;
	// 	pthread_mutex_unlock(&((t_all *)(all))->philo.die_msg);
	// 	printf("see u\n");
	// 	return (NULL);
	// }
	printf("%u %d is sleeping\n", end, ((t_all *)(all))->actual_philo);
	pthread_mutex_unlock(&((t_all *)(all))->philo.sleep_msg);
	ft_usleep(((t_all *)(all))->philo.time_for_sleep);
	pthread_mutex_lock(&((t_all *)(all))->philo.think_msg);
	printf("%u %d is thinking\n", end, ((t_all *)(all))->actual_philo);
	pthread_mutex_unlock(&((t_all *)(all))->philo.think_msg);
	return ((void *)all);
}

void	doing_all(t_all *all)
{
	int	i;
	int	y;

	i = 0;
	y = 1;
	all->first_round = 1;
	if (all->philo.tab_philo != NULL)
	{
		all->time_start = philo_get_time();
		printf("all->philo.last_meal == %d\n", all->philo.last_meal);
		if (all->philo.last_meal != 0)
		{
			while (all->eat_enough != 1 || all->died_philo != 1)
			{
				while ((all->eat_enough != 1 || all->died_philo != 1) && i <= all->num_philo)
				{
					all->actual_philo = i + 1;
					if (i % 2 == 0)
					{
						pthread_create(&all->philo.tab_philo[i], NULL, &routine, all);
						ft_usleep(30);
						pthread_create(&all->philo.tab_philo[i], NULL, &philo_dead, all);
						if (all->philo.tab_philo[i] == NULL)
							return ;
						if (all->died_philo == 1)
						{
							pthread_mutex_lock(&all->philo.die_msg);			
							pthread_mutex_lock(&all->philo.die_msg);
							printf("Philo is died\n");
							all->died_philo = 1;
							pthread_mutex_unlock(&all->philo.die_msg);
							return ;
						}
					}
					all->time_act = philo_get_time();
					i++;
				}
				ft_usleep(200);
				i = 1;
				while ((all->eat_enough != 1 || all->died_philo != 1) && i <= all->num_philo)
				{
					all->actual_philo = i + 1;
					if (i % 2 != 0)
					{
						pthread_create(&all->philo.tab_philo[i], NULL, &routine, all);
						ft_usleep(30);
						pthread_create(&all->philo.tab_philo[i], NULL, &philo_dead, all);
						if (all->philo.tab_philo[i] == NULL)
							return ;
					}
					i++;
				}
				i = 0;
			}
		}
		else
		{
			while (all->died_philo != 1)
			{
				while (all->died_philo != 1)
				{
					while (i <= all->num_philo)
					{
						all->actual_philo = i + 1;
						if (i % 2 == 0 || i == 0)
						{
							pthread_create(&all->philo.tab_philo[i], NULL, &routine, all);
							ft_usleep(30);
							pthread_create(&all->philo.tab_philo[i], NULL, &philo_dead, all);
							if (all->died_philo == 1)
								break ;
						}
						i++;
					}
				}
				ft_usleep(200);
				i = 1;
				while (all->died_philo != 1)
				{
					while (i <= all->num_philo)
					{
						all->actual_philo = i;
						if (i % 2 != 0)
						{
							pthread_create(&all->philo.tab_philo[i], NULL, &routine, all);
							ft_usleep(30);
							pthread_create(&all->philo.tab_philo[i], NULL, &philo_dead, all);
							if (all->died_philo == 1)
								break ;
						}
						i++;
					}
					i = 0;
				}
			}
		}
	}
}

int	main(int ac, char **av)
{
	t_all	*all;

	all = malloc(sizeof(t_all *));
	all->num_philo = 0;
	if (!all)
		return (0);
	if (ac != 5 && ac != 6)
	{
		printf("Error: Missing parameters\n");
		return (0);
	}
	if (parsing(ac, av, all) == 0)
		return (0);
	doing_all(all);

	return (0);
}