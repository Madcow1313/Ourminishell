#include "../logic/logic.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>

// int	rl_replace_line(char *str);

// int	rl_replace_line()
// {
// 	return (0);
// }

void	rl_replace_line (const char *text, int clear_undo)
{
	if (text && !clear_undo)
		return ;
}

void	ft_signal_ctrl_c(int num)
{
	write(1, "\n", 1);
	rl_on_new_line();
	write(1, "", 0);
	rl_replace_line("", 0);
	rl_redisplay();
	num = 0;
}

int	ft_s_h(void)
{
	//signal(SIGTERM, SIG_IGN);
	signal(SIGINT, ft_signal_ctrl_c);
	signal(SIGQUIT, SIG_IGN);
	return (1);
}

void	ft_s_h_heredoc(void)
{
	signal(SIGINT, ft_signal_ctrl_c);
	signal(SIGQUIT, SIG_IGN);
}