#include "../logic/logic.h"

void	errors(void)
{
	char	*s;

	s = strerror(g_error_code);
	perror(s);
}