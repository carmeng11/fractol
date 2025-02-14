int	ft_str_isdigit(char *str)
{
	while (*str)
	{
		printf("%c\n", *str);
		if (!(ft_isdigit(*str)))
			return (0);
		str++;
	}
	return (1);
}