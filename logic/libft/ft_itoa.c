#include "libft.h"

static	int	count(int n)
{
	int	len;

	len = 1;
	if (n < 0)
	{
		while (n != 0)
		{
			n = n / 10;
			len++;
		}
	}
	else
	{
		while (n > 9)
		{
			n = n / 10;
			len++;
		}
	}
	return (len);
}

static	char	*fill_array(char *str, int n, int len)
{
	if (n == 0)
		str[0] = '0';
	else if (n - 1 == 2147483647)
	{
		str[1] = '2';
		n = 147483648;
	}
	while (n != 0)
	{
		str[len] = n % 10 + '0';
		n /= 10;
		len--;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		sign;
	int		len;

	sign = 1;
	if (n < 0)
		sign = -1;
	len = count(n);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	if (n == -2147483647 - 1)
	{
		ft_strlcpy(str, "-2147483648", sizeof("-2147483648"));
		return (str);
	}
	str[len] = '\0';
	if (sign == -1)
		str[0] = '-';
	n *= sign;
	len--;
	str = fill_array(str, n, len);
	return (str);
}
