/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 13:25:36 by vaghazar          #+#    #+#             */
/*   Updated: 2022/06/26 19:41:41 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int	ft_atoi(const char *nptr)
{
	int	num;
	int	temp;

	num = 0;
	temp = 1;
	while (*nptr == ' ' || *nptr == '\t' || *nptr == '\n'
		|| *nptr == '\v' || *nptr == '\f' || *nptr == '\r')
	nptr++;
	if (*nptr == '-')
	{
		temp *= -1;
		nptr++;
	}
	else if (*nptr == '+')
		nptr++;
	while (*nptr >= '0' && *nptr <= '9')
	{
		num = (num * 10) + (*nptr - '0');
		if (!(*(nptr + 1) >= '0' && *(nptr + 1) <= '9'))
			return (num * temp);
		nptr++;
	}
	return (num * temp);
}

static int	send_end_str(int server_pid)
{
	int	bit;

	bit = 8;
	while (bit--)
	{
		if (bit == 7)
		{
			if (kill(server_pid, SIGUSR2) == -1 && ft_printf("Error: kill\n"))
				return (1);
		}
		else if (kill(server_pid, SIGUSR1) == -1 && ft_printf("Error: kill\n"))
			return (1);
		usleep(100);
	}
	return (0);
}

static int	send_string(int server_pid, char *str)
{
	int	i;
	int	bit;

	bit = 8;
	i = -1;
	while (str[++i])
	{
		while (bit--)
		{
			if (str[i] & (1 << bit))
				kill(server_pid, SIGUSR1);
			else if (kill(server_pid, SIGUSR2) == -1
				&& ft_printf("Error: kill\n"))
				return (1);
			usleep(100);
		}
		bit = 8;
	}
	send_end_str(server_pid);
	return (0);
}

int	main(int ac, char **av)
{
	int	pid;

	if (ac != 3)
	{
		ft_printf("usage: ./client [pid server] [message]\n");
		return (1);
	}
	pid = ft_atoi(av[1]);
	if (pid == 0)
	{
		ft_printf("Unknow PID.\n");
		return (1);
	}
	send_string(pid, av[2]);
	return (0);
}
