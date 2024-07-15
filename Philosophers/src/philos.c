/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehammoud <ehammoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 19:08:05 by ehammoud          #+#    #+#             */
/*   Updated: 2024/07/14 20:34:35 by ehammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philos.h>

void	*one_philo(t_pass *s, t_philo *p)
{
	print_act(s, p->id, FORKING, 0);
	ft_sleep(s, p, p->dt * 2, p->le);
	return (NULL);
}

void	init_philo(t_pass *s, t_philo *p)
{
	p->le = militime();
	p->ec = 0;
	pthread_mutex_lock(&(s->m_info));
	p->np = s->info[NP];
	p->dt = s->info[DT];
	p->st = s->info[ST];
	p->et = s->info[ET];
	p->tte = s->info[TTE];
	pthread_mutex_unlock(&(s->m_info));
}

void	*routine(void *data)
{
	t_pass		*s;
	t_philo		p;

	s = (t_pass *)data;
	pthread_mutex_lock(&(s->m_tid));
	p.id = s->id++;
	if (!s->start)
		s->start = militime();
	pthread_mutex_unlock(&(s->m_tid));
	init_philo(s, &p);
	if (p.np == 1)
		return (one_philo(s, &p));
	while ((p.ec < p.tte || p.tte == -1) && !dead_philo(s))
	{
		if (p.ec)
			print_act(s, p.id, THINKING, 3);
		if (!wait_for_fork(s, &p) || !wait_for_fork(s, &p))
			return (NULL);
		if (!eating(s, &p) || !sleeping(s, &p))
			return (NULL);
	}
	return (NULL);
}

int	run_threads(pthread_t *philos, t_pass *shared, void *(*f)(void *))
{
	int	i;

	i = 0;
	while (i < shared->info[NP])
	{
		if (pthread_create(philos + i++, NULL, f, shared) != 0)
			return (ERR_PTC);
	}
	i = 0;
	while (i < shared->info[NP])
	{
		if (pthread_join(philos[i++], NULL))
			return (ERR_PTJ);
	}
	return (0);
}

void	handle_philos(int *info)
{
	t_pass		shared;
	pthread_t	*philos;
	int			ret;
	int			i;

	if (!ft_malloc((void **)&philos, info[NP], sizeof(pthread_t)))
		free_and_exit(NULL, NULL, ERR_MEM, 1);
	shared.info = info;
	if (!init_shared_info(&shared))
		free_and_exit(&shared, philos, ERR_MEM, EXIT_FAILURE);
	ret = run_threads(philos, &shared, routine);
	i = 0;
	while (i < info[NP])
		pthread_mutex_destroy(&shared.m_forks[i++]);
	pthread_mutex_destroy(&shared.m_info);
	pthread_mutex_destroy(&shared.m_tid);
	pthread_mutex_destroy(&shared.m_fed);
	pthread_mutex_destroy(&shared.m_death);
	pthread_mutex_destroy(&shared.m_write);
	if (ret)
		free_and_exit(&shared, philos, ret, EXIT_FAILURE);
	else if (shared.dead_philo)
		free_and_exit(&shared, philos, FAILURE, EXIT_SUCCESS);
	free_and_exit(&shared, philos, SUCCESS, EXIT_SUCCESS);
}
