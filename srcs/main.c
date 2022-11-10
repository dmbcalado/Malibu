/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratinhosujo <ratinhosujo@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 06:49:28 by anfreire          #+#    #+#             */
/*   Updated: 2022/11/09 16:01:43 by ratinhosujo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	brain(t_data *data)
{
	int	i;

	i = -1;
	data->built.b_counter = 0;
	if (data->line == NULL || data->line[0] == '\0')
		return ;
	while (data->par_line[++i])
	{
		if (builtin_detector (data, data->par_line[i]) >= 0)
		{
			parse_builtin(data, i, data->built.b_counter);
			exec_builtin(data, i);
			data->built.b_counter++;
		}
		else if (cmd_detector(data, data->par_line[i]) == 1 && \
		data->paths.p_str != NULL)
			braining_cmds(data, i);
	}
}

void	braining_cmds(t_data *data, int i)
{
	int	c;
	int	cmds;

	c = 0;
	cmds = data->cmd.cmd_nbr;
	pipes (data);
	data->ids.id = (int *)malloc(data->cmd.cmd_nbr * sizeof(int));
	while (cmds > 0)
	{
		parse_cmd (data, c);
		cmds--;
		c++;
	}
	if (acessing_cmd(data, i) == 0)
	{
		printf ("%s: command not found.\n", data->paths.path_cmd[i]);
		return ;
	}
	run_command(data, i);
}

void	starting(t_data *data, char *envp[])
{
	signal (SIGQUIT, sig_ignore);
	signal (SIGINT, sig_handler);
	get_envp (data, envp);
	data->line = NULL;
	data->andre.exit = 0;
}

int	main(int argc, char *argv[], char *envp[])
{
	t_data	data;

	if (argc < 1 || *argv == NULL)
		return (0);
	starting(&data, envp);
	while (1)
	{
		get_line(&data);
		data.andre.args = 0;
		data.par_line = parse_line(&data);
		get_paths(&data);
		if (data.paths.p_str != NULL)
		{
			parse_alloc(&data);
			if (redirect(&data) < 0)
				continue ;
			brain (&data);
			free_line_info (&data);
		}
	}
	return (0);
}
