#include "shell.h"

/**
 * **strok - splits a string into words and repeated delimiters are ignored.
 * @str: the input string of the function.
 * @dl: the delimeter string of the function.
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **strok(char *str, char *dl)
{
	int i, j, k, m, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!dl)
		dl = " ";
	for (i = 0; str[i] != '\0'; i++)
		if (!_delim(str[i], dl) && (_delim(str[i + 1], dl) || !str[i + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (_delim(str[i], dl))
			i++;
		k = 0;
		while (!_delim(str[i + k], dl) && str[i + k])
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = str[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}

/**
 * **strok2 - splits a string into words
 * @str: the input string
 * @dl: the delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **strok2(char *str, char dl)
{
	int i, j, k, m, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
		if ((str[i] != dl && str[i + 1] == dl) ||
				    (str[i] != dl && !str[i + 1]) || str[i + 1] == dl)
			numwords++;
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (str[i] == dl && str[i] != dl)
			i++;
		k = 0;
		while (str[i + k] != dl && str[i + k] && str[i + k] != dl)
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = str[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}
