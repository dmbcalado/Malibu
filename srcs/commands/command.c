
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmendonc <dmendonc@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 16:53:40 by dmendonc          #+#    #+#             */
/*   Updated: 2022/11/09 14:07:02 by dmendonc      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

void	run_command(t_data *data, int index)
{
	data->ids.id[index] = fork();
	if (data->ids.id[index] == 0)
	{
		printf("index %d", index);
		run_child(data, index);
		execve (data->paths.path_cmd[index], data->cmd.cmdx[index], data->envp);
	}
	else
	{
		close (data->ids.pfd[index][1]);
		waitpid(data->ids.id[index], &data->andre.exit, 0);
		while (data->andre.exit > 256)
			data->andre.exit /= 256;
		WEXITSTATUS(data->andre.exit);
	}
}

void	run_child(t_data *data, int index)
{
	if (data->ids.inp_list[index] != STDIN_FILENO)
	{
		dup2(data->ids.inp_list[index], STDIN_FILENO);
		data->redir.input_c++;
	}
	else
		piping(data, index, 0);
	if (data->ids.outp_list[index] != STDOUT_FILENO)
	{
		dup2(data->ids.outp_list[index], STDOUT_FILENO);
		data->redir.output_c++;
	}
	else
		piping(data, index, 1);
}