/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehammoud <ehammoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 20:35:57 by ehammoud          #+#    #+#             */
/*   Updated: 2024/07/14 20:36:00 by ehammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

static int	valid_args(int argc, char **argv)
{
	int	i;
	int	j;

	if (argc < 5 || argc > 6)
		return (0);
	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

static int	print_restrictions(void)
{
	printf("Error: Invalid value given in arguments, ");
	printf("here are the limitations:\n");
	printf("Number of philosophers:\n\tBetween 1 and 200\n");
	printf("Time to die:\n\tBetween 0 and 2,147,483,647\n");
	printf("Time to eat:\n\tBetween 0 and 2,147,483,647\n");
	printf("Number of times each philosopher must eat:\n\t");
	printf("Between 0 and 2,147,483,647 (optional argument)\n");
	return (0);
}

static int	fill_info(int *info, int argc, char **argv)
{
	info[NP] = ft_atoi(argv[1]);
	info[DT] = ft_atoi(argv[2]);
	info[ET] = ft_atoi(argv[3]);
	info[ST] = ft_atoi(argv[4]);
	info[TTE] = -1;
	if (argc == 6)
	{
		info[TTE] = ft_atoi(argv[5]);
		if (info[TTE] == -1)
			return (print_restrictions());
	}
	if (info[NP] > 200 || info[NP] <= 0
		|| info[ET] <= -1 || info[ST] <= -1 || info[DT] <= -1)
		return (print_restrictions());
	return (1);
}

int	main(int argc, char **argv)
{
	int	info[5];

	if (!valid_args(argc, argv))
	{
		printf("Error: Invalid args!\n");
		if (argc < 5)
			printf("Not enough args, need at least 4 arguments.\n");
		else if (argc > 6)
			printf("Too many args, takes at most 5 arguments.\n");
		else
			printf("Must enter positive numerical values\n");
		return (1);
	}
	if (!fill_info(info, argc, argv))
		return (1);
	handle_philos(info);
}
