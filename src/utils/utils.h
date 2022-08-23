/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/22 16:31:15 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/08/23 15:42:14 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "structs.h"

t_error_data	rt_get_error_data(void);
t_status		rt_set_error(t_error error, char *error_data_text);

#endif
