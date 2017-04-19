/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_live.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkovalen <dkovalen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 11:36:16 by okerniak          #+#    #+#             */
/*   Updated: 2017/04/18 18:33:57 by dkovalen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** function checks wether all carets have right to live.
*/

int		ft_live(t_caret **caret)
{
	t_caret	*carrent;
	t_caret	*temp;
	int		winer;

	winer = (*caret)->color;
	while (*caret != NULL && (*caret)->live == 0)
	{
		temp = (*caret)->next;
		free(*caret);
		*caret = temp;
	}
	carrent = *caret;
	while (carrent != NULL)
	{
		temp = carrent->next;
		if (temp != NULL && temp->live == 0)
		{
			carrent->next = temp->next;
			free(temp);
			continue ;
		}
		carrent->live = 0;
		carrent = temp;
	}
	return ((*caret == NULL) ? winer : 0);
}

/*
** correct CYCLE_TO_DIE
*/

void	ft_edit_cycle_to_die(t_caret *caret, int *cycle_die)
{
	int			nbr;
	int			cycle;
	static int	checks = 0;

	nbr = 0;
	cycle = *cycle_die;
	while (caret != NULL)
	{
		nbr += caret->live;
		caret = caret->next;
	}
	if (nbr >= NBR_LIVE || checks >= MAX_CHECKS)
	{
		cycle -= CYCLE_DELTA;
		checks = 0;
	}
	else
		checks++;
	*cycle_die = cycle;
}
