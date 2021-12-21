#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	if (fd == -1)
		return ;
	else if (n == -2147483647 - 1)
	{
		write (fd, "-2147483648", 11);
		return ;
	}
	else if (n == 2147483647)
	{
		write(fd, "2147483647", 10);
		return ;
	}
	else if (n < 0)
	{
		ft_putchar_fd('-', fd);
		ft_putnbr_fd(-n, fd);
		return ;
	}
	else if (n > 9)
		ft_putnbr_fd(n / 10, fd);
	ft_putchar_fd(((n % 10) + '0'), fd);
}
