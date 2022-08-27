/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_int_field_advance.c                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/23 15:39:24 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/08/27 13:20:41 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "input/input_structs.h"
#include "utils/utils.h"
#include "libft.h"

static int is_space_or_comma(int c)
{
	return ((c >= '\t' && c <= '\r') || c == ' ' || c == ',');
}

static void	rt_atoi_strict_skipper(char *str, size_t *skip, size_t *non_digits)
{
	while (ft_isspace(str[*skip]))
	{
		(*non_digits)++;
		(*skip)++;
	}
	if (str[*skip] == '+' || str[*skip] == '-')
	{
		(*non_digits)++;
		(*skip)++;
	}
	while (ft_isdigit(str[*skip]))
		(*skip)++;
}

t_status	parse_int_field_advance(char **line, int *i)
{
	size_t	skipped;
	size_t	non_digits;
	bool	had_overflow;

	*i = 0;
	skipped = 0;
	non_digits = 0;
	rt_atoi_strict_skipper(*line, &skipped, &non_digits);
	if (skipped == non_digits || (!is_space_or_comma((*line)[skipped]) \
	&& (*line)[skipped] != '\0'))
		return (rt_set_error(E_EXPECTED_INTEGER, NULL));
	*i = ft_atoi(*line, &had_overflow);
	if (had_overflow)
		return (rt_set_error(E_EXPECTED_INTEGER, NULL));
	*line = &(*line)[skipped];
	return (OK);
}
