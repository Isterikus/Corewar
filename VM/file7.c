/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file7.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkovalen <dkovalen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 16:22:40 by dkovalen          #+#    #+#             */
/*   Updated: 2017/04/19 16:32:39 by dkovalen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	start_viz(void)
{
	check_size();
	initscr();
	start_color();
	set_colors();
}

void	check_bot_size(int fd, int size)
{
	char	*test;
	int		rd;

	test = (char *)malloc(sizeof(char) * (size + 2));
	lseek(fd, PROG_NAME_LENGTH + COMMENT_LENGTH + 16, 0);
	rd = read(fd, test, size + 1);
	if (rd != size)
		error(15);
}

void	winners(int champs, int winer, t_player *players)
{
	if (winer == -1)
	{
		if (champs == 1)
		{
			ft_printf("Contestant %d, ", 1);
			ft_printf("\"%s\", has won !\n", players[0].name);
		}
		else
			ft_printf("Draw!\n");
	}
	else
	{
		ft_printf("Contestant %d, ", winer);
		ft_printf("\"%s\", has won !\n", players[winer - 1].name);
	}
}
