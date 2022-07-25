SRCS = philo_m/ft_atoi.c philo_m/ph.c philo_m/func.c philo_m/true_sleep.c philo_m/if_circle.c \
		philo_m/validation.c philo_m/print_die.c philo_m/zachistka.c
OBJS = $(SRCS:%.c=%.o)
HEADER = philo_m/philo.h
CC = gcc -Wall -Wextra -Werror -g -fsanitize=thread
RM = rm -f
NAME = philo
SRCS_B = philo_b/philo_b.c philo_b/validation.c philo_b/ft_atoi.c philo_b/if_circle.c \
		philo_b/check_die.c philo_b/kill_process.c philo_b/true_sleep.c philo_b/go.c philo_b/tri_v_odnom.c
OBJS_B = $(SRCS_B:%.c=%.o)
NAME_B = philo_bonus
HEADER_B = philo_bonus/philo_bonus.h

$(NAME):	$(OBJS)
	$(CC) $(OBJS) -I $(HEADER) -o $(NAME)

all		:		$(NAME)

clean	:
	$(RM) $(OBJS) $(OBJS_B)

fclean	:		clean
	$(RM) $(NAME) $(NAME_B)

re		:		fclean	all

bonus	:
	make	OBJS="${OBJS_B}" HEADER="${HEADER_B}" NAME="${NAME_B}" all