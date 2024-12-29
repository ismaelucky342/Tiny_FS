#include "libft.h"

#define RED "\033[31m"
#define RESET "\033[0m"

void ft_perror(const char *message)
{
    const char *error_prefix = "Error: ";
    size_t prefix_len = ft_strlen(error_prefix);
    size_t message_len = ft_strlen(message);

    write(STDERR_FILENO, RED, ft_strlen(RED));
    write(STDERR_FILENO, error_prefix, prefix_len);
    write(STDERR_FILENO, message, message_len);
    write(STDERR_FILENO, RESET, ft_strlen(RESET));
    write(STDERR_FILENO, "\n", 1);
}