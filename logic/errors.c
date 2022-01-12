#include "../logic/logic.h"

void	errors(void)
{
	ft_putstr_fd(strerror(g_error_code), STD_ERROR);
	ft_putstr_fd("\n", STD_ERROR);
}

void	cd_errors(char *path)
{
	ft_putstr_fd("bash: cd: ", STD_ERROR);
	ft_putstr_fd(path, STD_ERROR);
	ft_putstr_fd(": ", STD_ERROR);
	errors();
	return ;
}

void	export_errors(char *str)
{
	g_error_code = 1;
	ft_putstr_fd("bash: export: '", STD_ERROR);
	ft_putstr_fd(str, STD_ERROR);
	ft_putendl_fd("': not a valid identifier", STD_ERROR);
	return ;
}

void	malloc_error(char **s)
{
	if (s)
		free_array(s);
	g_error_code = 12;
	//errors();
	return ;
}

void	command_error()
{
	g_error_code = 127;
	ft_putstr_fd("Error: bash: 127: command not found\n", STD_ERROR);
	return ;
}
