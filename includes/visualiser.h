/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualiser.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 14:05:53 by wballaba          #+#    #+#             */
/*   Updated: 2019/03/09 17:08:46 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISUALISER_H
# define VISUALISER_H

# include "lem_in.h"
# include "draw.h"

# define KEY_UP				126
# define KEY_DOWN			125
# define KEY_RIGHT			123
# define KEY_LEFT			124
# define KEY_Q				12
# define KEY_W				13
# define KEY_E				14
# define KEY_S				1
# define KEY_A				0
# define KEY_D				2

# define STOP_DRAW			0
# define DRAWING			1
# define LAST_DRAW			2

# define WIN_SIZE			1250.0
# define VISUAL_SIZE		1070.0
# define NODE_RADIUS		17
# define LINE_WIDTH			2

# define COLOR_BG1			0x111237
# define COLOR_BG2			0x6f3292
# define COLOR_EDGE			0xD0006E
# define COLOR_NODE			COLOR_EDGE
# define COLOR_START		0xf2a2cc
# define COLOR_ANT			0xFFFFFF

# define SPEED_ANIMATION	4

typedef struct	s_ant
{
	int		x;
	int		y;
	int		x2;
	int		y2;
	double	sin_a;
	double	cos_a;
	double	length;
	int		drawing;
}				t_ant;

typedef struct	s_val
{
	double		max_x;
	double		max_y;
	double		min_x;
	double		min_y;
}				t_val;

typedef struct	s_visual_farm
{
	int			fd;
	t_mlx		*visual;
	t_img		*image;
	t_farm		*farm;
	t_ant		**ant;
	t_val		*val;
	double		abs_x;
	double		abs_y;
	double		indent_x;
	double		indent_y;
	int			step;
	int			count_func;
	int			count_line;
}				t_vfarm;

/*
**	Visualisation
*/

int				press_key_callback(int key, t_farm *farm);
void			draw_farm(t_farm *farm);
void			visual_farm(t_vfarm	*vfarm);
void			create_farm_image(t_vfarm *vfarm);
void			find_path_ant(t_vfarm *vfarm);
void			get_arr_ant(t_vfarm *vfarm);
void			move_ant(t_ant *ant, t_room *room, t_vfarm *vfarm);
void			draw_run_ant(t_vfarm *vfarm);
void			get_abs_val(t_farm *farm, t_vfarm *vfarm);
int				draw_ants(t_vfarm *vfarm);
void			move_farm(int key, t_vfarm *vfarm);
void			zoom_farm(int key, t_vfarm *vfarm);

int				ft_close(void);
int				ft_key_press_esc_close(int key);

int				end_ant_path(int key, t_vfarm *vfarm);

#endif
