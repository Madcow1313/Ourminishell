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
