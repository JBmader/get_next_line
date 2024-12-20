# **************************************************************************** #
#                                VARIABLES                                    #
# **************************************************************************** #

NAME            = libgnl.a
CC              = cc
CFLAGS          = -Wall -Wextra -Werror
AR              = ar rcs
RM              = rm -f

SRCS            = get_next_line.c \
                  get_next_line_utils.c

BONUS_SRCS      = get_next_line_bonus.c \
                  get_next_line_utils_bonus.c

OBJS            = $(SRCS:.c=.o)
BONUS_OBJS      = $(BONUS_SRCS:.c=.o)

# **************************************************************************** #
#                                RULES                                        #
# **************************************************************************** #

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

bonus: $(BONUS_OBJS)
	$(AR) $(NAME) $(BONUS_OBJS)

clean:
	$(RM) $(OBJS) $(BONUS_OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus