/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehammoud <ehammoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 14:48:29 by ehammoud          #+#    #+#             */
/*   Updated: 2024/07/07 15:29:04 by ehammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	*ft_malloc(void **p, int elems, int size)
{
	*p = malloc(elems * size);
	return (*p);
}

int	ft_atoi(char *str)
{
	long	x;

	x = 0;
	while (*str >= '0' && *str <= '9')
	{
		x = x * 10 + *str - '0';
		str++;
		if (x > INT_MAX)
			return (-1);
	}
	return (x);
}

unsigned long	militime(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int	get_fork(int pid, int n, int fork)
{
	int		left;

	left = pid - 1;
	if (pid == 0)
		left = n - 1;
	if ((pid % 2 == 0 && fork == 1) || (pid % 2 == 1 && fork == 2))
		return (pid);
	else
		return (left);
}
