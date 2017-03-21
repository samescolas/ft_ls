#include "ft_ls.h"

int		main(void)
{
	if (ft_numlen(0) != ft_numlen(3))
		write(1, "problems", ft_strlen("problems"));
	return (0);
}
