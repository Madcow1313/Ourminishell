#include "../logic/logic.h"

static int	is_digit(char *s)
{
	int	i;

	i = 0;
	while(ft_isdigit(s[i]) && s[i])
	{
		i++;
		if (s[i + 1] == '\0')
			return (1);
	}
	return (0);
}

void	process_exit(char **args)
{
	ft_putstr_fd("exit\n", 2);
	if (!*args || !args)
		exit(g_error_code);
	if (count_env_len(&args[1]) > 1)
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		g_error_code = 1;
		return ;
	}
	if (*args && !is_digit(*args))
	{
		ft_putstr_fd("exit: ", 2);
		ft_putstr_fd(*args, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		g_error_code = 1;
		exit(225);
	}
	if (*args && is_digit(*args))
		exit(ft_atoi(*args));
}