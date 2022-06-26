/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 13:25:39 by vaghazar          #+#    #+#             */
/*   Updated: 2022/06/26 19:43:08 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

static char	*ft_strjoin(char *s1, char const s2)
{
	char	*ptr;
	char	*ptr1;
	char	*s1_ptr;

	s1_ptr = s1;
	ptr = (char *) malloc(ft_strlen((char *)s1) + 2);
	if (ptr == 0)
		return (0);
	ptr1 = ptr;
	while (s1 && *s1 != '\0')
		*ptr++ = *s1++;
	*ptr++ = s2;
	*ptr = '\0';
	if (s1_ptr)
	{
		free(s1_ptr);
		s1_ptr = NULL;
	}
	return (ptr1);
}

static void	sig_handler(int signum)
{
	static int	bit;
	static char	*str = NULL;
	static char	c;

	if (bit == 0)
	{
		c = 0;
		bit = 8;
	}
	bit--;
	if (signum == SIGUSR1)
		c |= (1 << bit);
	if (c != 127 && bit == 0)
		str = ft_strjoin(str, c);
	if (c == 127)
	{
		ft_printf("%s", str);
		if (str)
		{
			free(str);
			str = NULL;
		}
		str = 0;
	}
}

int	main(int ac, char **av)
{
	int					pid;
	struct sigaction	sa;

	(void) av;
	if (ac != 1)
	{
		ft_printf("usage: ./server\n");
		return (1);
	}
	sa.sa_handler = &sig_handler;
	sa.sa_flags = SA_RESTART;
	sa.sa_mask = 0;
	pid = getpid();
	ft_printf("%d\n", pid);
	while (1)
	{
		sigaction(SIGUSR1, &sa, NULL);
		sigaction(SIGUSR2, &sa, NULL);
	}
	return (0);
}
