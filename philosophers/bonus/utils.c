/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eshakhge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 14:11:58 by eshakhge          #+#    #+#             */
/*   Updated: 2022/06/12 14:12:03 by eshakhge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

int	ft_atoi(const char *s)
{
	int	n;
	int	i;
	int	m;

	m = 1;
	n = 0;
	i = 0;
	if (!s)
		return (0);
	while (s[i] == ' ')
		i++;
	if (s[i] == '+' || s[i] == '-')
		if (s[i++] == '-')
			m = -1;
	while (s[i] && s[i] >= '0' && s[i] <= '9')
		n = n * 10 + s[i++] - 48;
	if (!s || s[i] != 0)
		return (0);
	return (n * m);
}

long	gettimenow(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return (t.tv_sec * 1000 + t.tv_usec / 1000);
}

long	gettime_ms(long zero)
{
	return (gettimenow() - zero);
}

char	*ft_join_strnum(char *str, int num)
{
	int		i;
	int		j;
	char	temp[12];
	char	*ret;

	i = 0;
	while (str && str[i])
		i++;
	j = 0;
	while (num / 10)
	{
		temp [j++] = num % 10 + 48;
		num /= 10;
	}
	ret = malloc (sizeof(char) * (j + i + 1));
	i = -1;
	while (str && str[++i])
		ret[i] = str[i];
	while (--j >= 0)
		ret[i++] = temp [j];
	ret[i] = 0;
	return (ret);
}
