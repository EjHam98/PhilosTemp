/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehammoud <ehammoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 14:48:43 by ehammoud          #+#    #+#             */
/*   Updated: 2024/07/14 20:36:15 by ehammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# define AVAILABLE -1
# define NONE 0
# define LEFT 1
# define RIGHT 2
# define BOTH 3

# include <stdlib.h>
# include <limits.h>
# include <sys/time.h>
# include <unistd.h>

unsigned long	militime(void);
int				ft_atoi(char *str);
void			*ft_malloc(void **p, int elems, int size);
int				get_fork(int pid, int n, int fork);

#endif