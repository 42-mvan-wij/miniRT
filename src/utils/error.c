/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/22 16:26:00 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/08/27 13:37:34 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "structs.h"

static t_error_data	*rt_get_error_data_ptr(void)
{
	static t_error_data	err = {
		.data_text = "\0",
		.error = E_NO_ERROR,
	};

	return (&err);
}

t_error_data	rt_get_error_data(void)
{
	return (*rt_get_error_data_ptr());
}

t_status	rt_set_error(t_error error, char *error_data_text)
{
	t_error_data	*error_data;

	error_data = rt_get_error_data_ptr();
	error_data->error = error;
	if (error_data_text != NULL)
		ft_strlcpy(error_data->data_text, error_data_text, ERROR_TEXT_SIZE);
	else
		error_data->data_text[0] = '\0';
	if (error == E_NO_ERROR)
		return (OK);
	return (FAIL);
}
