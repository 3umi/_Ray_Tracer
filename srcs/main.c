/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 17:43:44 by ohalim            #+#    #+#             */
/*   Updated: 2023/07/03 15:38:01 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	__draw(t_data *data)
{
	t_vect ve;
	t_vect transval;
	t_vect scaleval;
	t_vect rotaxis;
	double rotangle;
	(void)data;

	ve = vect_new(1, 2, 3);
	transval = vect_new(-1, 2, 4);
	scaleval = vect_new(1, 1, 2);
	rotaxis = vect_new(1, 0, 0);
	rotangle = 90;
	t_mat4 mat;
	// print matrix
	// translate
	printf("\t|\t%.2f\t%.2f\t%.2f\t|\n", ve.x, ve.y, ve.z);
	mat = mat4_translate(transval);
	mat = mat4_mult(mat, mat4_scale(scaleval));
	ve = mat4_mult_vect(mat, ve);
	mat = mat4_mult(mat, mat4_rotate(vect_new(90, 0, 0)));
	print_mat4(mat);
	printf("vect:\n");
	printf("\t|\t%.2f\t%.2f\t%.2f\t|\n", ve.x, ve.y, ve.z);
}

int	main(int argc, char **argv)
{
	t_data	data;

	__parsing(argc, argv, &data);
	__init(&data);
	__draw(&data);
	/* mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.img.img, 0, 0);
	   mlx_hook(data.win_ptr, 17, 0, close_win, &data);
	   mlx_hook(data.win_ptr, 2, 0, key_hook, &data);
	   mlx_key_hook(data.win_ptr, key_hook, &data);
	   mlx_key_hook(data.win_ptr, lock_key_hook, &data);
	   mlx_loop(data.mlx_ptr); */
	return (0);

}
