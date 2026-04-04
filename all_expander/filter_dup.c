#include "../minishell.h"

int filter_dup(char *content)
{
	int		i;
	int		count;
	char	quote;

	count = 0;
	i = 0;
	while (content[i])
	{
		if (content[i] == '\'' || content[i] == '\"')
		{
			quote = content[i++];
			while (quote != content[i] && content[i])
			{
				count++;
				i++;
			}
			if (content[i] == quote)
			i++;
			}
		else
		{
			count++;
			i++;
		}
	}
	printf("%d\n", count);
	// res = malloc(sizeof(char) * count + 1);
	// i = 0;
	// count = 0;
	// while (content[i])
	// {
	// 	if (content[i] != '\'' && content[i] != '\"')
	// 	{
	// 		res[count] = content[i];
	// 		count++;
	// 	}
	// 	i++;
	// }
	// res[count] = '\0';
	// return (res);
}
