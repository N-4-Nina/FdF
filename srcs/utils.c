#include "../include/FdF.h"

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}

int	hextoint(char *s)
{
	int	dec;
	int	x;
	int	p;
	int	i;

	if (s[0] == '0')
		s++;
	if (s[0] == 'x')
		s++;
	i = ft_strlen(s) - 1;
	p = 0;
	dec = 0;
	while (i >= 0)
	{
		if (s[i] >= '0' && s[i] <= '9')
			x = s[i] - '0';
		else
			x = s[i] - 'A' + 10;
		dec = dec + x * pow(16, p++);
		i--;
	}
	return (dec);
}

float	max(float val1, float val2)
{
	if (val1 > val2)
		return (val1);
	else
		return (val2);
}

float	min(float val1, float val2)
{
	if (val1 < val2)
		return (val1);
	else
		return (val2);
}
