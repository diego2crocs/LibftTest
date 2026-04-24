LIBFT_DIR	= ../Libft
CC		= cc
CFLAGS		= -Wall -Wextra -Werror

all:
	$(MAKE) -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) main_test.c -I$(LIBFT_DIR) -L$(LIBFT_DIR) -lft -o test_libft
	./test_libft

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -f test_libft

re:
	$(MAKE) -C $(LIBFT_DIR) re
	$(CC) $(CFLAGS) main_test.c -I$(LIBFT_DIR) -L$(LIBFT_DIR) -lft -o test_libft
	./test_libft

.PHONY: all clean re
