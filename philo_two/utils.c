/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 16:05:26 by ymanzi            #+#    #+#             */
/*   Updated: 2020/10/22 14:42:50 by ymanzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static int	ft_isspace(char c)
{
	return (c == '\t' || c == '\n' || c == '\v' || c == '\f'
			|| c == '\r' || c == ' ');
}

int			ft_atoi(const char *nptr)
{
	int					moins;
	unsigned long long	nbr;

	moins = 1;
	nbr = 0;
	while (ft_isspace(*nptr))
		nptr++;
	if (*nptr == '+' || *nptr == '-')
	{
		if (*(nptr++) == '-')
			moins *= -1;
	}
	while (*nptr >= '0' && *nptr <= '9')
		nbr = (10 * nbr + (*(nptr++) - 48));
	if (nbr > 9223372036854775807)
		return ((moins > 0) ? -1 : 0);
	return ((int)(moins * nbr));
}

static void	affiche(long long n, int fd)
{
	char	c;

	if (n > 9)
	{
		affiche((n / 10), fd);
		affiche((n % 10), fd);
	}
	else
	{
		c = n + 48;
		write(fd, &c, 1);
	}
}

void		ft_putnbr_fd(long long n, int fd)
{
	if (n == -2147483648)
		write(fd, "-2147483648", 11);
	else
	{
		if (n < 0)
		{
			write(fd, "-", 1);
			affiche(-n, fd);
		}
		else
			affiche(n, fd);
	}
}

int			ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}
