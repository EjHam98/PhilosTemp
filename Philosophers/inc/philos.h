/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehammoud <ehammoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 10:48:23 by codespace         #+#    #+#             */
/*   Updated: 2024/07/07 14:30:59 by ehammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOS_H
# define PHILOS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <limits.h>
# include <sys/time.h>
# include "utils.h"
# include "general.h"

# define NP 0
# define DT 1
# define ET 2
# define ST 3
# define TTE 4

# define SUCCESS 0
# define FAILURE 1
# define ERR_MEM 2
# define ERR_PTC 3
# define ERR_PTJ 4
# define ERR_GEN 5

# define EATING " is eating"
# define THINKING " is thinking"
# define SLEEPING " is sleeping"
# define FORKING "has picked up a fork"
# define DYING "has died"

typedef struct s_passed_info
{
	unsigned long	start;
	int				id;
	int				fed;
	int				*info;
	int				*forks;
	t_bool			dead_philo;
	pthread_mutex_t	m_info;
	pthread_mutex_t	m_fed;
	pthread_mutex_t	m_tid;
	pthread_mutex_t	m_write;
	pthread_mutex_t	m_death;
	pthread_mutex_t	*m_forks;
}	t_pass;

typedef struct s_philo_info
{
	int				tte;
	int				id;
	int				ec;
	int				np;
	int				dt;
	int				et;
	int				st;
	unsigned long	le;
}	t_philo;

t_bool	init_shared_info(t_pass *shared);
t_bool	ft_sleep(t_pass *s, t_philo *p, unsigned long ms, unsigned long last);
void	print_act(t_pass *s, int philo_id, char *act, int font);
void	free_and_exit(t_pass *shared, pthread_t *philos, int msg, int status);
t_bool	dead_philo(t_pass *s);
t_bool	kill_philo(t_pass *s, int pid);
int		fork_available(t_pass *s, t_philo *p);
t_bool	wait_for_fork(t_pass *s, t_philo *p);
t_bool	sleeping(t_pass *s, t_philo *p);
t_bool	eating(t_pass *s, t_philo *p);
void	*routine(void *data);
void	handle_philos(int *info);
int		run_threads(pthread_t *philos, t_pass *shared, void *(*f)(void *));

#endif