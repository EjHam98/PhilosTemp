/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehammoud <ehammoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 19:18:54 by ehammoud          #+#    #+#             */
/*   Updated: 2024/06/30 14:25:29 by ehammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

void	free_and_exit(t_pass *shared, pthread_t *philos, int msg, int status)
{
	if (msg == SUCCESS)
		write(2, GREEN_BOLD"\nSuccess!\nSimulation over!\n"RESET, 38);
	if (msg == ERR_MEM)
		write(2, RED_BOLD"\nError\nMemory allocation failed!\n"RESET, 44);
	if (msg == ERR_PTC)
		write(2, RED_BOLD"\nError\nPThread creation failed!\n"RESET, 43);
	if (msg == ERR_PTJ)
		write(2, RED_BOLD"\nError\nPThread joining failed!\n"RESET, 42);
	if (msg == ERR_GEN)
		write(2, RED_BOLD"\nError\nUnexpected error occurred!\n"RESET, 45);
	if (msg == FAILURE)
		write(2, PURPLE_BOLD"\nFailure!\nA philosopher has died!\n"RESET, 45);
	if (shared->forks)
		free(shared->forks);
	if (shared->m_forks)
		free(shared->m_forks);
	if (philos)
		free(philos);
	exit (status);
}

t_bool	init_shared_info(t_pass *shared)
{
	int	i;

	shared->id = 0;
	shared->fed = 0;
	shared->start = 0;
	shared->dead_philo = False;
	ft_malloc((void **)&(shared->forks), shared->info[NP], sizeof(int));
	ft_malloc((void **)&(shared->m_forks), shared->info[NP],
		sizeof(pthread_mutex_t));
	if (!shared->forks || !shared->m_forks)
		return (False);
	i = 0;
	while (i < shared->info[NP])
	{
		pthread_mutex_init(shared->m_forks + i, NULL);
		shared->forks[i++] = -1;
	}
	pthread_mutex_init(&(shared->m_info), NULL);
	pthread_mutex_init(&(shared->m_tid), NULL);
	pthread_mutex_init(&(shared->m_fed), NULL);
	pthread_mutex_init(&(shared->m_write), NULL);
	pthread_mutex_init(&(shared->m_death), NULL);
	return (True);
}

void	print_act(t_pass *s, int philo_id, char *act, int font)
{
	pthread_mutex_lock(&(s->m_write));
	if (!dead_philo(s))
	{
		if (font == 3)
			printf(YELLOW"%-5lu %-3d %s\n"RESET, militime() - s->start, \
			philo_id + 1, act);
		if (font == 1)
			printf(GREEN"%-5lu %-3d %s\n"RESET, militime() - s->start, \
			philo_id + 1, act);
		if (font == 2)
			printf(BLUE"%-5lu %-3d %s\n"RESET, militime() - s->start, \
			philo_id + 1, act);
		if (font == 0)
			printf(CYAN"%-5lu %-3d %s\n"RESET, militime() - s->start, \
			philo_id + 1, act);
	}
	pthread_mutex_unlock(&(s->m_write));
}

t_bool	dead_philo(t_pass *s)
{
	t_bool	ret;

	pthread_mutex_lock(&(s->m_death));
	ret = s->dead_philo;
	pthread_mutex_unlock(&(s->m_death));
	return (ret);
}

t_bool	ft_sleep(t_pass *s, t_philo *p, unsigned long ms, unsigned long last)
{
	unsigned long	start;

	start = militime();
	while (militime() - start < ms)
	{
		if ((int)(militime() - last) >= p->dt)
			return (kill_philo(s, p->id));
		if (dead_philo(s))
			return (False);
		usleep(50);
	}
	return (True);
}
