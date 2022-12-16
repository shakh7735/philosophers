#SETUP
NAME		=	philo
NAME_B		=	philo_bonus
CC			=	cc
FLAGS		=	-Wall -Wextra -Werror
RM			=	rm -rf

#FILES AND PATH
HEADER_SRCS	=	philo.h philo_bonus.h
#HEADER_DIR	=	includes/
#HEADER		=	$(addprefix $(HEADER_DIR), $(HEADER_SRCS))
HEADER		=	$(HEADER_SRCS)

MPATH_SRCS	=	philo.c utils.c philo_thread.c
MPATH_DIR	=	mandatory/
MPATH		=	$(addprefix $(MPATH_DIR), $(MPATH_SRCS))
OBJ_M		=	$(MPATH:.c=.o)

BPATH_SRCS	=	philo_bonus.c utils.c phil_proc.c
BPATH_DIR	=	bonus/
BPATH		=	$(addprefix $(BPATH_DIR), $(BPATH_SRCS))
OBJ_B		=	$(BPATH:.c=.o)

#COMMANDS
%.o: %.c $(HEADER) Makefile
				@${CC} ${FLAGS} -c $< -o $@

all:			$(NAME)

bonus:			$(NAME_B)

$(NAME):		$(OBJ_M)
				@$(RM) $(OBJ_B) 
				@$(CC) $(OBJ_M) -o $(NAME)
				@echo "$(GREEN)$(NAME) created!$(DEFAULT)"

$(NAME_B):		$(OBJ_B)
				@$(RM) $(OBJ_M)
				@$(CC) $(OBJ_B) -o $(NAME_B)
				@echo "$(GREEN)$(NAME_B) created!$(DEFAULT)"
clean:			
				@$(RM) $(OBJ_M)
				@$(RM) $(OBJ_B)
				@echo "$(YELLOW)object files deleted!$(DEFAULT)"

fclean:			clean
				@$(RM) $(NAME)
				@$(RM) $(NAME_B)
				@echo "$(RED)all deleted!$(DEFAULT)"

re:				fclean all

.PHONY:		all clean fclean bonus re

#COLORS
RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
DEFAULT = \033[0m

