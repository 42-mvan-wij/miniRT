/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/22 16:26:00 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/09/27 12:57:24 by rvan-duy      ########   odam.nl         */
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

void	rt_print_error(void)
{
	const t_error_data	error = rt_get_error_data();
	const char			*error_texts[] = {
	[E_NO_ERROR] = "lol, get rekt",
	[E_OPEN] = "Could not open file: ",
	[E_MALLOC] = "Malloc failed",
	[E_GNL] = "Failed to get next line",
	[E_EXPECTED_FLOAT] = "Expected float",
	[E_EXPECTED_INTEGER] = "Expected integer",
	[E_EXPECTED_VEC] = "Expected vector",
	[E_EXPECTED_RGB] = "Expected RGB",
	[E_EXPECTED_NORMAL] = "Expected normalized vector",
	[E_EXPECTED_IDENTIFIER] = "Expected identifier",
	[E_EXPECTED_RT_FILE] = "Expected .rt file",
	[E_DUPLICATE_UNIQUE_ELEMENT] = "Duplicate unique element: ",
	[E_MISSING_REQUIRED_ELEMENT] = "Missing required element: ",
	[E_EXTRA_TEXT] = "Unexpected text: ",
	[E_MLX] = "MLX Error: ",
	[E_TOO_FEW_ARGS] = "Supplied to few arguments",
	[E_TOO_MANY_ARGS] = "Supplied to many arguments",
	};

	ft_putendl_fd("Error", STDERR_FILENO);
	ft_putstr_fd((char *)error_texts[error.error], STDERR_FILENO);
	ft_putendl_fd((char *)error.data_text, STDERR_FILENO);
}
