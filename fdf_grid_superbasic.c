#include "libs/minilibx_macos/mlx.h"
#include "libs/libft/libft.h"
#include <math.h>

typedef struct	s_xy
{
	float		x;
	float		y;
}				t_xy;

int		main()
{

    void *mlx_ptr; /*struct*/
    void *win_ptr; /*struct*/
    //void *img_ptr; /*struct*/
    //int *data_addr; /*struct*/
    int x1 = 150;
    int y1 = 150;
	int x2 = 1000;
	int y2 = 151;
	float x = (float)x1;
	float y = (float)y1;
	float slope;
    float dy;
    float dx;
    // int endx = 10; /*struct: from read*/
    // int endy = 10; /*struct: from read*/
    // int size = 33; /*struct: set after read*/
    // int offset = 25; /*struct: set after read*/
    //int bits_per_pixel = 32; /*define*/
    int img_wid = 1920; /*define*/
    int img_hgt = 980; /*define*/
    //int endian = 1; /*define*/
    // float ax = 0;
    // float ay = 0.52;
    // float az = 1.57;



    mlx_ptr = mlx_init();
    // img_ptr = mlx_new_image(mlx_ptr, img_wid, img_hgt);
    // data_addr = mlx_get_data_addr(img_ptr, &bits_per_pixel, &img_wid, &endian);
    //
	// x = ((x * cos(ay) * cos(az)) - (y * cos(ay) * sin(az)) + (z * sin(ay))) * size + offset;
	// y = ((x * (sin(ax) * sin(ay) * cos(az) + cos(ax) * sin(az))) + (y * (sin(az) * sin(ax) * sin(ay))) - (z * cos(ay) * sin(ax)))
    // while (1)
    // {
	//
    // }
	win_ptr = mlx_new_window(mlx_ptr, img_wid, img_hgt, "Butt");
    // while (1)
    // {
    //     x = 0;
    //     if (y > endy * size * Dy)
    //         break ;
    //     while (x <= (endx * size * Dx) + (Dx * y) + 1)
    //     {
    //         if (((!((x - (Dx * y)) % (size * Dx)) || ((x - (Dx * y)) % (size * Dx)) == 1 || !(y % size * Dy))) && x >= (Dx * y))
    //             mlx_pixel_put(mlx_ptr, win_ptr, x + offset, y + offset, 0xffffff);
    //         x += 1;
    //     }
    //     y += 1;
    // }
	dy = y2 - y1;
	dx = x2 - x1;

	slope = dy > dx ? dx/dy : dy/dx;
    // if (dy > dx)
    // {
    //     while (y <= y2)
    //     {
    //         mlx_pixel_put(mlx_ptr, win_ptr, x, y, 0x00c3ff);
    //         y++;
    //         x += slope;
    //     }
    // }
    // else
    // {
	while (x <= x2 && y <= y2)
	{
			if (x >= 0 && y >= 0 && x < img_wid && y < img_hgt)
				mlx_pixel_put(mlx_ptr, win_ptr, (int)x, (int)y, 0xffffff);
			x += dy > dx ? slope : 1;
			y += dy > dx ? 1 : slope;
	}
	mlx_pixel_put(mlx_ptr, win_ptr, x1, y1, 0xff00ff);
	mlx_pixel_put(mlx_ptr, win_ptr, x2, y2, 0xff00ff);
	mlx_loop(mlx_ptr);
}
