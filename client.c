/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicoter <lnicoter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 17:53:35 by dabi-rac          #+#    #+#             */
/*   Updated: 2023/03/21 19:53:24 by lnicoter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	bitto(pid_t pid, char c)
{
	int		byte;

	byte = 0;
	while (byte < 8)
	{
		if (c & (1 << byte))
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(2000);
		byte++;
	}
}

void	itto(pid_t pid, char *str)
{
	int		i;

	i = 0;
	while (str[i] != '\0')
	{
		bitto(pid, str[i]);
		usleep(2000);
		i++;
	}
}

void	msg(int i)
{
	(void)i;
	ft_printf("message received\n");
}

int	main(int ac, char **av)
{
	int	pid;

	if (ac == 3)
	{
		pid = ft_atoi(av[1]);
		itto(pid, av[2]);
		signal(SIGUSR1, msg);
		bitto(pid, '\n');
		bitto(pid, '\0');
	}
	else
	{
		ft_printf("\33[93mError: Not enough arguments.\033[0m\n");
		return (0);
	}
	return (0);
}
/*
&
10010101
11000101
10000101
|
10010101
11000101
11010101
^
10010101
11000101
11010101
~
10010101
01101010

00000111 << 2

00011100
*/
