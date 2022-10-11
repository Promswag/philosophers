/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 14:01:08 by gbaumgar          #+#    #+#             */
/*   Updated: 2022/10/11 14:25:44 by gbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

size_t	ft_strlen(const char *s)
{
	size_t	l;

	l = 0;
	while (s[l])
		l++;
	return (l);
}

int	ft_isdigit(int c)
{
	if ((c >= 48 && c <= 57))
		return (1);
	return (0);
}

int	ft_isanumber(char *str)
{
	int	i;
	int	l;

	if (!str)
		return (0);
	i = 0;
	l = ft_strlen(str);
	if ((str[i] == '-' || str[i] == '+') && l == 1)
		return (0);
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (i < l)
		if (!ft_isdigit(str[i++]))
			return (0);
	return (1);
}

int	ft_atoi(const char *str)
{
	int					i;
	unsigned long long	r;
	int					sign;

	r = 0;
	sign = 1;
	i = 0;
	while (*(str + i) == '\t' || *(str + i) == '\n' || *(str + i) == '\v'
		|| *(str + i) == '\f' || *(str + i) == '\r' || *(str + i) == ' ')
		i++;
	if (*(str + i) == '+' || *(str + i) == '-')
		if (*(str + i++) == '-')
			sign = -1;
	while (*(str + i) >= 48 && *(str + i) <= 57)
		r = r * 10 + *(str + i++) - 48;
	if (r > 0x7fffffffffffffff && sign == 1)
		return (-1);
	if (r > 0x7fffffffffffffff && sign == -1)
		return (0);
	return (r * sign);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (s)
		write(fd, s, ft_strlen(s));
}
