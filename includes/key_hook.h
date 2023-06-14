/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brahim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 04:03:14 by brahim            #+#    #+#             */
/*   Updated: 2023/06/12 04:21:50 by brahim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEY_HOOK_H
# define KEY_HOOK_H

# define ESC 53
# define ESC_LINUX 65307


int	close_win(t_data *mlx);
int	key_hook(int keycode, t_data *mlx);

#endif

