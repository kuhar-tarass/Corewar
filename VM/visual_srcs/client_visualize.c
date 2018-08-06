/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkiselev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 16:02:56 by tkiselev          #+#    #+#             */
/*   Updated: 2018/07/22 16:02:58 by tkiselev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*------------- VISUALIZATION on client side -------------*/

static void	redraw_client(t_win *win, int key, int socket_fd, fd_set read_fds)
{
	win->cursor_x = X_BEGIN;
	win->cursor_y = Y_BEGIN;
	(key == RESIZE) ? prepare_window(win) : 0;
	get_data_from_server(socket_fd, read_fds);
	draw_map(win);
	show_sidebar(win);
	if (g_vm->winner)
	{
		print_winner(win);
		nodelay(stdscr, false);
	}
	wrefresh(win->window);
}

void		client_visualize(int socket_fd, fd_set read_fds)
{
	t_win	*win;
	int 	key;

	initscr();
	noecho();
	raw();
	color_preparation();
	win = init_win();
	win->speed = 1000;
	win->paused = 0;
	nodelay(stdscr, true);
	prepare_window(win);
	while ((key = getch()) != 3 && !g_vm->winner)
		redraw_client(win, key, socket_fd, read_fds);
	delwin(win->window);
	endwin();
}
