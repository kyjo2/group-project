


#include "../minishell.h"

void    change_tmp_right(char **s, char *tmp, int *i, int *j)
{
    if ((*s)[(*i) + 1] == '>')
    {
		tmp[(*j)++] = ' ';
		tmp[(*j)++] = '>';
		tmp[(*j)++] = '>';
		tmp[(*j)++] = ' ';
		(*i)++;
	}
	else if ((*s)[(*i) + 1] == '<')
	{
		tmp[(*j)++] = ' ';
		tmp[(*j)++] = '>';
	}
	else
	{
		tmp[(*j)++] = ' ';
		tmp[(*j)++] = '>';
		tmp[(*j)++] = ' ';
	} 
}

void    change_tmp_left(char **s, char *tmp, int *i, int *j)
{
    if ((*s)[(*i) + 1] == '<')
	{
		tmp[(*j)++] = ' ';
		tmp[(*j)++] = '<';
		tmp[(*j)++] = '<';
		tmp[(*j)++] = ' ';
		(*i)++;
	}
	else if ((*s)[(*i) + 1] == '>')
	{
		tmp[(*j)++] = ' ';
		tmp[(*j)++] = '<';
	}
	else
	{
		tmp[(*j)++] = ' ';
		tmp[(*j)++] = '<';
		tmp[(*j)++] = ' ';
	}
}