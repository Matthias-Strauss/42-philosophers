/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_to_int.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstrauss <mstrauss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 17:01:48 by mstrauss          #+#    #+#             */
/*   Updated: 2024/08/12 18:17:52 by mstrauss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/// @brief Checks if a character is an ASCII whitespace character
/// @param c character to check
/// @return 1 if c is a whitespace, 0 if c isn't a whitespace
static int	is_space(int c)
{
	if (c == '\t' || c == '\n' || c == '\r' || c == '\v' || c == '\f'
		|| c == ' ')
		return (1);
	return (0);
}

/// @brief checks if a character is a digit
/// @param num character to check
/// @return returns character if it IS a digit
/// 		returns 0 if character is NOT a digit
static int	is_digit(int num)
{
	if (num >= '0' && num <= '9')
		return (num);
	return (0);
}

/// @brief converts a number from individual characters to an int.
/// @param str the string to be converted
/// @return the converted integer value
int	str_to_int(const char *str)
{
	size_t	i;
	int		sign;
	int		sum;

	i = 0;
	sign = 1;
	sum = 0;
	while (is_space(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i++] == '-')
			sign = -1;
	}
	while (is_digit(str[i]))
		sum = (str[i++] - '0') + (sum * 10);
	return (sign * sum);
}
