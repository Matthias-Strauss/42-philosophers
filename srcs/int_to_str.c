/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_to_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstrauss <mstrauss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 18:51:49 by mstrauss          #+#    #+#             */
/*   Updated: 2024/08/30 22:35:00 by mstrauss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*c_alloc(size_t count, size_t size)
{
	unsigned char	*ptr;
	unsigned int	i;
	unsigned int	len;

	len = count * size;
	ptr = malloc(count * size);
	if (!ptr)
	{
		printf("malloc failed in c_alloc\n");
		return (NULL);
	}
	i = 0;
	while (i < len)
	{
		ptr[i] = '\0';
		i++;
	}
	return (ptr);
}

static int	count_digit(int n)
{
	int	char_count;

	char_count = 0;
	while (n != 0)
	{
		n = n / 10;
		char_count++;
	}
	return (char_count);
}

static uint64_t	is_pos_num(int n)
{
	if (n < 0)
		return ((uint64_t)n * -1);
	else
		return ((uint64_t)n);
}

static char	*int_to_str_conv(char *s, uint64_t n_unsg, uint64_t char_count,
		uint64_t neg)
{
	if (neg == 1)
		*s = '-';
	while (char_count > 0)
	{
		s[char_count - 1 + neg] = (n_unsg % 10) + '0';
		n_unsg = n_unsg / 10;
		char_count--;
	}
	return (s);
}

/// @brief 		Allocates (with malloc(3)) and returns a string
///				representing the integer received as an argument.
///				Negative numbers must be handled.
/// @param n	String representing the integer.
/// @return		NULL if the allocation fails.
char	*int_to_str(int n)
{
	uint64_t	char_count;
	uint64_t	neg;
	char		*ptr;
	uint64_t	n_unsg;

	neg = 0;
	if (n == 0)
	{
		ptr = c_alloc(1, 2);
		if (ptr == NULL)
			return (NULL);
		ptr[0] = '0';
		return (ptr);
	}
	if (n < 0)
		neg++;
	n_unsg = is_pos_num(n);
	char_count = count_digit(n);
	ptr = c_alloc(1, char_count + 1 + neg);
	if (ptr == NULL)
		return (NULL);
	int_to_str_conv(ptr, n_unsg, char_count, neg);
	return (ptr);
}
