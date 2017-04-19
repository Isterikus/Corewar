/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkovalen <dkovalen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 11:20:26 by dkovalen          #+#    #+#             */
/*   Updated: 2017/04/19 16:35:20 by dkovalen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	error(int num)
{
	(num == 0) ? ft_printf("{red}ERROR{eoc}\nNo champions.\n") : 0;
	(num == 1) ? ft_printf("{red}ERROR{eoc}\nInvalid file name.\n") : 0;
	(num == 2) ? ft_printf("{red}ERROR{eoc}\nToo many champions.\n") : 0;
	(num == 3) ? ft_printf("{red}ERROR{eoc}\nInvalid flag.\n") : 0;
	(num == 4) ? ft_printf("{red}ERROR{eoc}\nCan't open file.\n") : 0;
	(num == 5) ? ft_printf("{red}ERROR{eoc}\nToo big file.\n") : 0;
	(num == 6) ? ft_printf("{red}ERROR{eoc}\nCan't read source file.\n") : 0;
	(num == 7) ? ft_printf("{red}ERROR{eoc}\nBad magic number.\n") : 0;
	(num == 8) ? ft_printf("{red}ERROR{eoc}\nToo big champion name.\n") : 0;
	(num == 9) ? ft_printf("{red}ERROR{eoc}\nToo big comment.\n") : 0;
	(num == 10) ? ft_printf("{red}ERROR{eoc}\nProg \
size doesn't match real.\n") : 0;
	(num == 11) ? ft_printf("{red}ERROR{eoc}\nZero \
prog size(or too big name).\n") : 0;
	(num == 12) ? ft_printf("{red}ERROR{eoc}\nNo code.\n") : 0;
	(num == 13) ? ft_printf("{red}ERROR{eoc}\nToo big champion.\n") : 0;
	(num == 14) ? ft_printf("{red}ERROR{eoc}\nNo name/comment.\n") : 0;
	(num == 15) ? ft_printf("{red}ERROR{eoc}\nChampion\
size doesn't match real.\n") : 0;
	exit(0);
}

void	print_stars(void)
{
	int		i;

	i = 0;
	while (i < 120)
	{
		mvprintw(0, i * 2, "*");
		mvprintw(65, i * 2, "*");
		i++;
	}
	i = 0;
	while (i < 66)
	{
		mvprintw(i, 0, "*");
		mvprintw(i, 196, "*");
		mvprintw(i, 240, "*");
		i++;
	}
}

void	put_color(unsigned char col)
{
	if (col == 1)
		attron(BLUE);
	else if (col == 2)
		attron(RED);
	else if (col == 3)
		attron(GREEN);
	else if (col == 4)
		attron(YELLOW);
	else if (col == 0)
		attron(WHITE);
}

int		print_nbr_live(t_caret *carets, int num)
{
	int		cur;
	t_caret	*temp;
	int		i;

	cur = 0;
	i = 0;
	temp = carets;
	while (temp != NULL)
	{
		if (temp->color == num)
			cur += temp->live;
		temp = temp->next;
		i++;
	}
	if (cur > 1000000 || cur < 0)
		cur = 0;
	return (cur);
}

int		count_process(t_caret *caret)
{
	t_caret	*temp;
	int		ret;

	temp = caret;
	ret = 0;
	while (temp != NULL)
	{
		ret++;
		temp = temp->next;
	}
	return (ret);
}
