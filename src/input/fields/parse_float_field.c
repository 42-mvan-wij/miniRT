/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_float_field.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/23 15:43:41 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/08/27 13:55:45 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "input/input_structs.h"
#include "utils/utils.h"
#include "libft.h"

static void	rt_atodl_strict_skipper(char *str, size_t *skip, size_t *non_digits)
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
	if (str[*skip] == '.')
	{
		(*skip)++;
		(*non_digits)++;
	}
	while (ft_isdigit(str[*skip]))
		(*skip)++;
}

static t_status	parse_float_advance(char **line, long double *f)
{
	size_t	skipped;
	size_t	non_digits;

	*f = 0;
	skipped = 0;
	non_digits = 0;
	rt_atodl_strict_skipper(*line, &skipped, &non_digits);
	if (skipped == non_digits || (!ft_isspace((*line)[skipped]) \
	&& (*line)[skipped] != '\0'))
		return (rt_set_error(E_EXPECTED_FLOAT, NULL));
	*f = ft_atodl(*line);
	*line = &(*line)[skipped];
	return (OK);
}

t_status	parse_float_field(char **line, long double *f)
{
	if (parse_float_advance(line, f) != OK)
		return (FAIL);
	while (ft_isspace(**line))
		(*line)++;
	return (OK);
}
