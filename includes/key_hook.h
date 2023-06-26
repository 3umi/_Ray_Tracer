/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 04:03:14 by brahim            #+#    #+#             */
/*   Updated: 2023/06/20 18:45:04 by ohalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEY_HOOK_H
# define KEY_HOOK_H

# define ESC 53
# define ESC_LINUX 65307
# define W_KEY 13
# define A_KEY 0
# define S_KEY 1
# define D_KEY 2
# define Q_KEY 12
# define E_KEY 14
# define LEFT_AROW 123
# define RIGHT_AROW 124
# define UP_AROW 126
# define DOWN_AROW 125


int	close_win(t_data *mlx);
int	key_hook(int keycode, t_data *mlx);
int	lock_key_hook(int keycode, t_data *mlx);

#endif

