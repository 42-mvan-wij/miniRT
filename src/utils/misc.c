/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   misc.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/01 14:00:40 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/09/01 14:40:27 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "structs.h"

long double	sin_from_cos(long double cos_a)
{
	return (sinl(acosl(cos_a)));
	// return (sqrtl(1 - (cos_a * cos_a)));
}

bool	almost_equal(long double a, long double b)
{
	long double	diff;

	diff = a - b;
	return (diff <= __DBL_EPSILON__ * 10 && diff >= -__DBL_EPSILON__ * 10);
}
