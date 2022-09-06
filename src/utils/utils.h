/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/22 16:31:15 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/09/06 18:18:41 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "structs.h"

t_error_data	rt_get_error_data(void);
t_status		rt_set_error(t_error error, char *error_data_text);
t_object		*rt_lstlast(t_object *node);
void			rt_lstadd_back(t_object **head, t_object *new);

#endif
