#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

int expr(const char *s, int *i);

int factor(const char *s, int *i)
{
	int res;

	if (s[*i] == '(')
	{
		(*i)++;
		res = expr(s, i);
		if (s[*i] != ')')
		{
			printf("unexpected token '%c'\n", s[*i]);
			exit(1);
		}
		(*i)++;
		return res;
	}
	if (isdigit(s[*i]))
		return s[(*i)++] - '0';
	if (s[*i] == '\0')
	{
		printf("unexpected end of input\n");
		exit(1);
	}
	return 0;
}

int term(const char *s, int *i)
{
	int res = factor(s, i);
	while (s[*i] == '*')
	{
		(*i)++;
		res *= factor(s, i);
	}
	return res;
}

int expr(const char *s, int *i)
{
	int res = term(s, i);
	while (s[*i] == '+')
	{
		(*i)++;
		res += term(s, i);
	}
	return res;
}

int main(int ac, char **av)
{
	int i = 0;
	int res = expr(av[1], &i);

	if (ac != 2)
		return 1;
	if (av[1][i])
	{
		printf("unexpected token '%c'\n", av[1][i]);
		exit(1);
	}
	if (printf("%d\n", res) < 0)
		exit(1);
	return 0;
}