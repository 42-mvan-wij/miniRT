/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lst.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/06 18:19:21 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/09/06 18:23:03 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "input/input_structs.h"
#include "utils/utils.h"
#include <stdlib.h>

t_object	*rt_lstlast(t_object *node)
{
	if (node == NULL)
		return (NULL);
	while (node->next != NULL)
		node = node->next;
	return (node);
}

void	rt_lstadd_back(t_object **head, t_object *new)
{
	if (*head == NULL)
		*head = new;
	else
		rt_lstlast(*head)->next = new;
}
