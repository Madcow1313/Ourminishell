#include "logic.h"

void	check_echo(char *str, t_list_commands *cmd)
{
	//char *argv[] = {"echo", "", NULL};
	if (!ft_strncmp(str, "echo", ft_strlen("echo")))
	{
		pid_t	pid = fork();
		if (pid == 0)
			execve("/usr/bin/echo", cmd->command, cmd->env_vars);
		else
			wait(&pid);
	}
	else
		return ;
}

void	start_cmd(t_list_commands *cmd)
{
	//int		i = 0;
	//char	*rez;
	ft_s_h();
/* 	while (cmd->command[i])
	{
		printf("%s\n", cmd->command[i]);
		i++;
	} */
	check_echo(cmd->command[0], cmd);
	return ;
}