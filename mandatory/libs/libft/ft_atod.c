/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 05:37:04 by ohalim            #+#    #+#             */
/*   Updated: 2023/07/19 16:49:43 by ohalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../../includes/miniRT.h" 

static void	initialize_utils(t_atod_utils *utils)
{
	utils->decimal = 0.0;
	utils->hasdecimal = 0;
	utils->result = 0.0;
	utils->sign = 1;
}

double ft_atod(char* str)
{
	t_atod_utils	utils;

	initialize_utils(&utils);
    if (*str == '-') 
	{
        utils.sign = -1;
        str++;
    }
    while (*str)
	{
        if (*str >= '0' && *str <= '9') 
		{
            if (utils.hasdecimal) 
			{
                utils.decimal *= 10.0;
                utils.result += (*str - '0') / utils.decimal;
            } 
			else 
                utils.result = utils.result * 10.0 + (*str - '0');
        } 
		else if (*str == '.') 
		{
            utils.hasdecimal = 1;
            utils.decimal = 1.0;
        } 
		else
            break ;
        str++;
    }
    return (utils.sign * utils.result);
}
