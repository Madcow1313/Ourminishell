#include "../logic/logic.h"

int	cmpr_oldpwd(t_list_commands *cmd, int i)
{
	char	*cmp;
	int		j;

	j = 0;
	while(cmd->env_vars[i][j] && cmd->env_vars[i][j] != '=')
		j++;
	cmp = ft_substr(cmd->env_vars[i], 0, j);
	if (!ft_strcmp(cmp, "OLDPWD"))
	{
		free(cmp);
		return (0);
	}
	free(cmp);
	return (1);
}

int	cmpr_pwd(t_list_commands *cmd, int i)
{
	char	*cmp;
	int		j;

	j = 0;
	while(cmd->env_vars[i][j] && cmd->env_vars[i][j] != '=')
		j++;
	cmp = ft_substr(cmd->env_vars[i], 0, j);
	if (!ft_strcmp(cmp, "PWD"))
	{
		free(cmp);
		return (0);
	}
	free(cmp);
	return (1);
}
