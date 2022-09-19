/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_structs.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/22 16:26:40 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/09/19 11:43:46 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_STRUCTS_H
# define ERROR_STRUCTS_H

# define ERROR_TEXT_SIZE 256

typedef enum e_status {
	OK = 0,
	FAIL,
}	t_status;

typedef enum e_error {
	E_NO_ERROR = 0,
	E_OPEN,
	E_MALLOC,
	E_GNL,
	E_EXPECTED_FLOAT,
	E_EXPECTED_INTEGER,
	E_EXPECTED_IDENTIFIER,
	E_EXPECTED_RT_FILE,
	E_EXPECTED_NORMAL,
	E_MLX,
}	t_error;

typedef struct s_error_data {
	char			data_text[ERROR_TEXT_SIZE];
	enum e_error	error;
}	t_error_data;

#endif
