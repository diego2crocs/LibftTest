LIBFT_DIR   = ../Libft
NAME        = test_libft
SRC         = main_test.c

CC          = cc
CFLAGS      = -Wall -Wextra -Werror
INCLUDES    = -I$(LIBFT_DIR)
LIBS        = -L$(LIBFT_DIR) -lft

VG_FLAGS    = --leak-check=full --show-leak-kinds=all --track-origins=yes \
              --errors-for-leak-kinds=all --error-exitcode=42 -q

GREEN       = \033[0;32m
RED         = \033[0;31m
YELLOW      = \033[0;33m
BLUE        = \033[0;34m
CYAN        = \033[0;36m
BOLD        = \033[1m
RESET       = \033[0m

ALLOWED_FILES = Makefile libft.h \
    ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
    ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c \
    ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c \
    ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c \
    ft_atoi.c ft_calloc.c ft_strdup.c \
    ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c \
    ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c \
    ft_putendl_fd.c ft_putnbr_fd.c \
    ft_lstnew.c ft_lstadd_front.c ft_lstsize.c \
    ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c \
    ft_lstclear.c ft_lstiter.c ft_lstmap.c README.md

all: header check_files build run valgrind

header:
	@printf "$(BOLD)$(CYAN)"
	@printf "╔════════════════════════════════════════╗\n"
	@printf "║              LIBFT TESTER              ║\n"
	@printf "╚════════════════════════════════════════╝\n"
	@printf "$(RESET)\n"

check_files:
	@printf "$(BOLD)$(BLUE)[1/4] Vérification des fichiers...$(RESET)\n"
	@$(MAKE) -s -C $(LIBFT_DIR) fclean > /dev/null 2>&1 || true
	@extra=""; \
	for f in $$(ls -A $(LIBFT_DIR) 2>/dev/null); do \
		case "$$f" in \
			.git|.gitignore|.DS_Store|.vscode|.idea) continue ;; \
		esac; \
		if [ -d "$(LIBFT_DIR)/$$f" ]; then continue; fi; \
		found=0; \
		for ok in $(ALLOWED_FILES); do \
			if [ "$$f" = "$$ok" ]; then found=1; break; fi; \
		done; \
		if [ $$found -eq 0 ]; then \
			extra="$$extra $$f"; \
		fi; \
	done; \
	if [ -z "$$extra" ]; then \
		printf "      $(GREEN)✅ Aucun fichier en trop$(RESET)\n\n"; \
	else \
		printf "      $(RED)❌ Fichiers non autorisés :$(RESET)\n"; \
		for f in $$extra; do printf "         $(RED)→ $$f$(RESET)\n"; done; \
		printf "\n"; \
	fi

norm:
	@printf "$(BOLD)$(BLUE)[2/4] Norminette...$(RESET)\n"
	@if ! command -v norminette > /dev/null 2>&1; then \
		printf "      $(YELLOW)⚠  norminette non installée, étape ignorée$(RESET)\n\n"; \
	else \
		out=$$(norminette $(LIBFT_DIR) 2>&1); \
		errors=$$(printf "%s" "$$out" | grep -E "Error|KO" || true); \
		if [ -z "$$errors" ]; then \
			printf "      $(GREEN)✅ Norminette OK$(RESET)\n\n"; \
		else \
			printf "      $(RED)❌ Erreurs norminette :$(RESET)\n"; \
			printf "%s\n" "$$errors" | sed 's/^/         /'; \
			printf "\n"; \
		fi; \
	fi

build: norm
	@printf "$(BOLD)$(BLUE)[3/4] Compilation de la libft...$(RESET)\n"
	@$(MAKE) -s -C $(LIBFT_DIR) > /dev/null 2>&1 \
		&& printf "      $(GREEN)✅ libft.a compilée$(RESET)\n\n" \
		|| (printf "      $(RED)❌ Erreur de compilation de la libft$(RESET)\n\n" && exit 1)
	@printf "$(BOLD)$(BLUE)[4/4] Compilation du tester...$(RESET)\n"
	@$(CC) $(CFLAGS) $(INCLUDES) $(SRC) $(LIBS) -o $(NAME) 2> /tmp/test_libft_err \
		&& printf "      $(GREEN)✅ $(NAME) prêt$(RESET)\n\n" \
		|| (printf "      $(RED)❌ Erreur de compilation du tester :$(RESET)\n" \
			&& sed 's/^/         /' /tmp/test_libft_err && exit 1)

run:
	@printf "$(BOLD)$(CYAN)──────────── EXÉCUTION ────────────$(RESET)\n\n"
	@./$(NAME)

valgrind: header check_files build
	@printf "$(BOLD)$(CYAN)──────────── VALGRIND ────────────$(RESET)\n\n"
	@if ! command -v valgrind > /dev/null 2>&1; then \
		printf "      $(RED)❌ valgrind n'est pas installé$(RESET)\n"; \
		exit 1; \
	fi
	@valgrind $(VG_FLAGS) --log-file=/tmp/test_libft_vg.log ./$(NAME) > /dev/null 2>&1; \
	vg_ret=$$?; \
	if [ $$vg_ret -eq 42 ]; then \
		printf "$(BOLD)$(RED)❌ FUITES / ERREURS DÉTECTÉES PAR VALGRIND$(RESET)\n\n"; \
		cat /tmp/test_libft_vg.log; \
		exit 1; \
	elif [ $$vg_ret -ne 0 ]; then \
		printf "$(BOLD)$(RED)❌ Le binaire a crashé sous valgrind (code $$vg_ret)$(RESET)\n\n"; \
		cat /tmp/test_libft_vg.log; \
		exit 1; \
	else \
		printf "$(BOLD)$(GREEN)✅ AUCUNE FUITE DE MÉMOIRE$(RESET)\n"; \
		printf "   $(GREEN)Tous les malloc ont été correctement libérés.$(RESET)\n\n"; \
	fi

clean:
	@printf "$(YELLOW)Nettoyage...$(RESET)\n"
	@$(MAKE) -s -C $(LIBFT_DIR) fclean > /dev/null 2>&1 || true
	@rm -f $(NAME) /tmp/test_libft_err /tmp/test_libft_vg.log
	@printf "$(GREEN)✅ Tout est propre$(RESET)\n"

fclean: clean

re: fclean all

.PHONY: all header check_files norm build run valgrind clean fclean re