#include "../logic/logic.h"

void	errors(void)
{
	char	*s;

	s = strerror(error_code);
	perror(s);
}