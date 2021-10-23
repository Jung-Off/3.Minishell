#include "minishell.h"

int	error_handler(char *err_msg)
{
	printf("[Error] %s\n", err_msg);
	return (EXIT_FAILURE);
}