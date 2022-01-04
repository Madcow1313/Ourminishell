#include "../logic/logic.h"

void	errors(void)
{
	ft_putstr_fd(strerror(g_error_code), 2);
	ft_putstr_fd("\n", 2);
}

void	cd_errors(char *path)
{
	ft_putstr_fd("bash: cd: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(": ", 2);
	errors();
	return ;
}

void	export_errors(char *str)
{
	g_error_code = 1;
	ft_putstr_fd("bash: export: '", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd("': not a valid identifier", 2);
	return ;
}

void	malloc_error(char **s)
{
	if (s)
		free_array(s);
	g_error_code = 12;
	errors();
	return ;
}
