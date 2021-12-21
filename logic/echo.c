#include "../logic/logic.h"

char	*process_echo(t_list_commands *cmd, char *rez)
{
	int	i;

	i = 0; //i need to compare using strcmpr
	while (cmd->command[i])
	{
		if (!ft_strncmp(cmd->command[i], "\'", "\'"))
			rez = ft_quotes(data, str, i, rez);
		else if (cmd->command[i] == '$')
			rez = ft_dollar(data, str, i, rez);
		else if (cmd->command[i] == '\"')
			rez = ft_double_quotes(data, str, i, rez);
		else if (cmd->command[i] == '\\')
		{
			rez = ft_strjoin_m(rez, ft_strndup(&str[*i + 1], 1), 3);
			*i = *i + 2;
		}
		else if (cmd->command[i] && ft_ch_for_coinc(cmd->command[i], "><"))
			*i = ft_skip_redir(str, *i);
		else
			rez = ft_normal(str, i, rez, "> <\\'\"$");
	}
	return (rez);
}