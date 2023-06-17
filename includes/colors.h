/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 15:20:37 by ohalim            #+#    #+#             */
/*   Updated: 2023/06/16 15:24:07 by ohalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLORS_H
# define COLORS_H

typedef struct s_color
{
    double  r;
    double  g;
    double  b;
}   t_color;

t_color new_color(double r, double g, double b);
#endif