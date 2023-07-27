#include "shell.h"

/**
 * _chain - test if current char in buffer is a chain delimeter.
 * @info: the parameter structure.
 * @buf: the char buffer.
 * @p: address of current position in buffer.
 *
 * Return: 1 if chain delimeter, 0 otherwise.
 */
int _chain(info_t *info, char *buf, size_t *p)
{
	size_t i = *p;

	if (buf[i] == '|' && buf[i + 1] == '|')
	{
		buf[i] = 0;
		i++;
		/*info->cmd_buf_type = CMD_OR;*/
	}
	else if (buf[i] == '&' && buf[i + 1] == '&')
	{
		buf[i] = 0;
		i++;
		/*info->cmd_buf_type = CMD_AND;*/
	}
	else if (buf[i] == ';') /* the end of command*/
	{
		buf[i] = 0;
		/*info->cmd_buf_type = CMD_CHAIN;*/
	}
	else
		return (0);
	*p = i;
	return (1);
}

/**
 * check_chain - checks we should continue chaining based on last status.
 * @info: the parameter structure.
 * @buf: the char buffer.
 * @p: address of current position in buf.
 * @st: starting position in buf.
 * @len: length of buf.
 *
 * Return: Void
 */
void check_chain(info_t *info, char *buf, size_t *p, size_t st, size_t len)
{
	size_t i = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[st] = 0;
			i = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[st] = 0;
			i = len;
		}
	}

	*p = i;
}

/**
 * replace_alias - replaces an aliases in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_alias(info_t *info)
{
	int n;
	list_t *node;
	char *p;

	for (n = 0; n < 10; n++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * replace_vars - replaces vars in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_vars(info_t *info)
{
	int n = 0;
	list_t *node;

	for (n = 0; info->argv[n]; n++)
	{
		if (info->argv[n][0] != '$' || !info->argv[n][1])
			continue;

		if (!_strcmp(info->argv[n], "$?"))
		{
			replace_string(&(info->argv[n]),
					_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[n], "$$"))
		{
			replace_string(&(info->argv[n]),
					_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[n][1], '=');
		if (node)
		{
			replace_string(&(info->argv[n]),
					_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[n], _strdup(""));

	}
	return (0);
}

/**
 * replace_string - replaces string.
 * @prev: address of older/previuos string.
 * @cur: new/current string.
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_string(char **prev, char *cur)
{
	free(*prev);
	*prev = cur;
	return (1);
}
