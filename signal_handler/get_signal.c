#include "../logic/logic.h"

// int	rl_replace_line(char *str);

// int	rl_replace_line()
// {
// 	return (0);
// }

void	ft_signal_ctrl_c()
{
	write(1, "\n", 1);
	//rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

int	ft_s_h(void)
{
	//signal(SIGTERM, SIG_IGN);
	signal(SIGINT, ft_signal_ctrl_c);
	signal(SIGQUIT, SIG_IGN);
	return (1);
}
