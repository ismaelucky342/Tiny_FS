#*************************************************************************************#
#                                                                                     #
#                                         ██╗   ██╗   ████████╗ █████╗ ██████╗        #
#      TINY_FS                            ██║   ██║   ╚══██╔══╝██╔══██╗██╔══██╗       #
#                                         ██║   ██║█████╗██║   ███████║██║  ██║       #
#      created:        12/12/2024         ██║   ██║╚════╝██║   ██╔══██║██║  ██║       #
#      last change:    12/12/2024         ╚██████╔╝      ██║   ██║  ██║██████╔╝       #
#                                          ╚═════╝       ╚═╝   ╚═╝  ╚═╝╚═════╝        #
#                                                                                     #
#       Ismael Hernandez Clemente              ismael.hernandez@live.u-tad.com        #
#                                                                                     #
#       Izhan Sastre Hernando                  izhan.sastre@live.u-tad.com            #
#                                                                                     #
#*************************************************************************************#

# Colores para mensajes
COLOR_RESET   = \033[0m
COLOR_GREEN   = \033[32m
COLOR_RED     = \033[31m
COLOR_YELLOW  = \033[33m

NAME =                        tiny_fs

CC =                        gcc

CFLAGS =                -Wall -Werror -Wextra #-fsanitize=thread -pthrea 

SRC_FILES =                src/main.c \
                                src/bytemaps.c \
                                src/data_block.c \
                                src/directory.c \
                                src/file_operations.c \
                                src/inode.c \
                                src/superblock.c \
                                src/utils/utils.c

OBJS = $(SRC_FILES:.c=.o)

all: $(NAME)
        @echo "$(COLOR_GREEN)Compilacion finalizada.$(COLOR_RESET)"
        @echo "                                                                                               "
        @echo "$(COLOR_GREEN)            █████████╗██╗███╗   ██╗██╗   ██╗     ███████╗███████╗$(COLOR_RESET)"
        @echo "$(COLOR_GREEN)            ╚══██╔══╝ ██║████╗  ██║╚██╗ ██╔╝     ██╔════╝██╔════╝$(COLOR_RESET)"
        @echo "$(COLOR_GREEN)               ██║    ██║██╔██╗ ██║ ╚████╔╝      █████╗  ███████╗$(COLOR_RESET)"
        @echo "$(COLOR_GREEN)               ██║    ██║██║╚██╗██║  ╚██╔╝       ██╔══╝  ╚════██║$(COLOR_RESET)"
        @echo "$(COLOR_GREEN)               ██║    ██║██║ ╚████║   ██║███████╗██║     ███████║$(COLOR_RESET)"
        @echo "$(COLOR_GREEN)               ╚═╝    ╚═╝╚═╝  ╚═══╝   ╚═╝╚══════╝╚═╝     ╚══════╝$(COLOR_RESET)"
        @echo "                                                                                               "
        @echo "$(COLOR_YELLOW)    Ismael Hernandez Clemente - ismael.hernandez@live.u-tad.com$(COLOR_RESET)"
        @echo "$(COLOR_YELLOW)    Izhan Sastre Hernando     - izhan.sastre@live.u-tad.com$(COLOR_RESET)"


$(NAME): $(OBJS)
        @$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
        @printf "%-200s\r" ">Philo_bonus compiling: $(CC) $(CFLAGS) -c -o $@ $<"
        @$(CC) $(CFLAGS) -c -o $@ $<

clean:
        @rm -f $(OBJS)

fclean: clean
        @rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re