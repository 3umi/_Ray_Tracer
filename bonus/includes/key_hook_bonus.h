/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 05:14:41 by belkarto          #+#    #+#             */
/*   Updated: 2023/07/21 01:17:22 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEY_HOOK_BONUS_H
# define KEY_HOOK_BONUS_H

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

void	put_text(t_data *data);
int		close_win(t_data *mlx);
int		key_hook(int keycode, t_data *mlx);
int		mouse_release(int key, int x, int y, t_data *data);

#endif
