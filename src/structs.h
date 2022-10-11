/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   structs.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/22 14:48:02 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/10/11 16:04:55 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <stdbool.h>
# include <stdint.h>

# define COS 0
# define SIN 1
# define MAX_BOUNCES 8
# define MOVEMENT_SPEED 1
# define ANGLE_FACTOR 0.8
# define DIST_FALLOFF 0.03

# include "vec3/vec3_structs.h"
# include "utils/utils_structs.h"
# include "render/render_structs.h"
# include "input/input_structs.h"
# include "utils/error_structs.h"

#endif
