/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lst.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/06 18:19:21 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/09/13 14:07:09 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "input/input_structs.h"
#include "utils/utils.h"
#include <stdlib.h>

t_shape_list	*rt_lstlast_shapes(t_shape_list *node)
{
	if (node == NULL)
		return (NULL);
	while (node->next != NULL)
		node = node->next;
	return (node);
}

t_shape_list	*rt_lstnew(t_object shape)
{
	t_shape_list	*new;

	new = malloc(sizeof(t_shape_list));
	if (new == NULL)
	{
		rt_set_error(E_MALLOC, NULL);
		return (NULL);
	}
	new->shape = shape;
	new->next = NULL;
	return (new);
}

t_shape_list	*rt_lstnew_back(t_shape_list **head, t_object shape)
{
	t_shape_list	*last;

	if (*head == NULL)
	{
		*head = rt_lstnew(shape);
		return (*head);
	}
	last = rt_lstlast_shapes(*head);
	last->next = rt_lstnew(shape);
	return (last->next);
}
