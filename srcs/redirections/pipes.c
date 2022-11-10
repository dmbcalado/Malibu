/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratinhosujo <ratinhosujo@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 15:26:23 by ratinhosujo       #+#    #+#             */
/*   Updated: 2022/11/09 16:05:08 by ratinhosujo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

void	pipes(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->cmd.cmd_nbr)
	{
		if (pipe(data->ids.pfd[i]) != 0)
			return ;
	}
}

void	piping(t_data *data, int index, int fn)
{
	if (!(index == 0 && fn == 0))
		//close(data->ids.pfd[index - 1][1]);
	if (!(index == data->cmd.cmd_nbr - 1 && fn == 1))
		close(data->ids.pfd[index][0]);
	dup2(data->ids.pfd[index - 1][0], fn);
}