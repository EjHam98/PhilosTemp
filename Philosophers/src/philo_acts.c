/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_acts.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehammoud <ehammoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 16:40:33 by ehammoud          #+#    #+#             */
/*   Updated: 2024/07/14 20:35:30 by ehammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

t_bool	kill_philo(t_pass *s, int pid)
{
	pthread_mutex_lock(&(s->m_death));
	if (s->dead_philo)
	{
		pthread_mutex_unlock(&(s->m_death));
		return (False);
	}
	s->dead_philo = True;
	pthread_mutex_unlock(&(s->m_death));
	pthread_mutex_lock(&(s->m_write));
	printf(PURPLE"%-5lu %-3d %s\n"RESET, militime() - s->start, pid + 1, DYING);
	pthread_mutex_unlock(&(s->m_write));
	return (False);
}

int	fork_available(t_pass *s, t_philo *p)
{
	int		ret;
	t_bool	skip;

	skip = False;
	ret = NONE;
	pthread_mutex_lock(&(s->m_forks[get_fork(p->id, s->info[NP], 1)]));
	pthread_mutex_lock(&(s->m_forks[get_fork(p->id, s->info[NP], 2)]));
	pthread_mutex_lock(&(s->m_fed));
	skip = (s->fed < p->np / 2
			&& (s->forks[get_fork(p->id, p->np, 1)] != AVAILABLE
				|| s->forks[get_fork(p->id, p->np, 2)] != AVAILABLE));
	pthread_mutex_unlock(&(s->m_fed));
	if (s->forks[get_fork(p->id, p->np, 1)] == AVAILABLE && !skip)
	{
		s->forks[get_fork(p->id, p->np, 1)] = p->id;
		ret += LEFT;
	}
	if (s->forks[get_fork(p->id, p->np, 2)] == AVAILABLE && !skip)
	{
		s->forks[get_fork(p->id, p->np, 2)] = p->id;
		ret += RIGHT;
	}
	pthread_mutex_unlock(&(s->m_forks[get_fork(p->id, s->info[NP], 2)]));
	pthread_mutex_unlock(&(s->m_forks[get_fork(p->id, s->info[NP], 1)]));
	return (ret);
}

t_bool	wait_for_fork(t_pass *s, t_philo *p)
{
	int	fork;

	pthread_mutex_lock(&(s->m_forks[get_fork(p->id, s->info[NP], 1)]));
	pthread_mutex_lock(&(s->m_forks[get_fork(p->id, s->info[NP], 2)]));
	fork = -1 * (s->forks[get_fork(p->id, p->np, 1)] == p->id
			&& s->forks[get_fork(p->id, p->np, 2)] == p->id);
	pthread_mutex_unlock(&(s->m_forks[get_fork(p->id, s->info[NP], 2)]));
	pthread_mutex_unlock(&(s->m_forks[get_fork(p->id, s->info[NP], 1)]));
	if (fork == -1)
		return (True);
	while (True)
	{
		fork = fork_available(s, p);
		if (dead_philo(s))
			return (False);
		if ((int)(militime() - p->le) >= p->dt)
			return (kill_philo(s, p->id));
		if (fork)
			break ;
		usleep(100);
	}
	print_act(s, p->id, FORKING, 0);
	if (fork == BOTH)
		print_act(s, p->id, FORKING, 0);
	return (True);
}

t_bool	eating(t_pass *s, t_philo *p)
{
	p->ec++;
	print_act(s, p->id, EATING, 1);
	pthread_mutex_lock(&(s->m_fed));
	s->fed++;
	pthread_mutex_unlock(&(s->m_fed));
	p->le = militime();
	if (!ft_sleep(s, p, p->et, p->le))
		return (False);
	return (True);
}

t_bool	sleeping(t_pass *s, t_philo *p)
{
	if (dead_philo(s))
		return (False);
	if (p->tte != p->ec)
		print_act(s, p->id, SLEEPING, 2);
	pthread_mutex_lock(&(s->m_forks[get_fork(p->id, s->info[NP], 1)]));
	pthread_mutex_lock(&(s->m_forks[get_fork(p->id, s->info[NP], 2)]));
	s->forks[get_fork(p->id, p->np, 1)] = AVAILABLE;
	s->forks[get_fork(p->id, p->np, 2)] = AVAILABLE;
	pthread_mutex_unlock(&(s->m_forks[get_fork(p->id, s->info[NP], 2)]));
	pthread_mutex_unlock(&(s->m_forks[get_fork(p->id, s->info[NP], 1)]));
	if (p->tte == p->ec)
		return (True);
	if (!ft_sleep(s, p, p->st, p->le))
		return (False);
	return (True);
}
