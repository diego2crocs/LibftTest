#include "libft.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

#define GREEN   "\033[0;32m"
#define RED     "\033[0;31m"
#define YELLOW  "\033[0;33m"
#define CYAN    "\033[0;36m"
#define BOLD    "\033[1m"
#define RESET   "\033[0m"

static int	g_pass = 0;
static int	g_fail = 0;
static int	g_idx  = 0;

/* Liste des erreurs de la fonction en cours, affichée à la fin de la ligne */
static char	g_errs[4096];
static int	g_err_len = 0;

static void	start_fn(const char *name)
{
	printf("%s%-15s%s:", BOLD, name, RESET);
	g_idx = 0;
	g_err_len = 0;
	g_errs[0] = '\0';
}

static void	end_fn(void)
{
	printf("\n");
	if (g_err_len > 0)
		printf("%s", g_errs);
}

static void	check(int ok, const char *err)
{
	g_idx++;
	if (ok)
	{
		printf(" %d." GREEN "✅" RESET, g_idx);
		g_pass++;
	}
	else
	{
		printf(" %d." RED "❌" RESET, g_idx);
		g_fail++;
		g_err_len += snprintf(g_errs + g_err_len,
				sizeof(g_errs) - g_err_len,
				"     " RED "→ test %d: %s" RESET "\n", g_idx, err);
	}
}

/* ===== CHARACTER CHECKS ===== */

static void	test_isalpha(void)
{
	start_fn("ft_isalpha");
	check(ft_isalpha('a') && isalpha('a'), "should accept 'a'");
	check(ft_isalpha('Z') && isalpha('Z'), "should accept 'Z'");
	check(!ft_isalpha('0') && !isalpha('0'), "should reject '0'");
	check(!ft_isalpha(' ') && !isalpha(' '), "should reject space");
	check(!ft_isalpha('\0'), "should reject null byte");
	end_fn();
}

static void	test_isdigit(void)
{
	start_fn("ft_isdigit");
	check(ft_isdigit('5') && isdigit('5'), "should accept '5'");
	check(ft_isdigit('0') && isdigit('0'), "should accept '0'");
	check(ft_isdigit('9') && isdigit('9'), "should accept '9'");
	check(!ft_isdigit('a') && !isdigit('a'), "should reject 'a'");
	check(!ft_isdigit(' '), "should reject space");
	end_fn();
}

static void	test_isalnum(void)
{
	start_fn("ft_isalnum");
	check(ft_isalnum('a') && isalnum('a'), "should accept 'a'");
	check(ft_isalnum('5') && isalnum('5'), "should accept '5'");
	check(!ft_isalnum('!') && !isalnum('!'), "should reject '!'");
	end_fn();
}

static void	test_isascii(void)
{
	start_fn("ft_isascii");
	check(ft_isascii(0), "0 is ASCII");
	check(ft_isascii(127), "127 is ASCII");
	check(!ft_isascii(128), "128 is not ASCII");
	check(!ft_isascii(-1), "-1 is not ASCII");
	end_fn();
}

static void	test_isprint(void)
{
	start_fn("ft_isprint");
	check(ft_isprint(' ') && isprint(' '), "space is printable");
	check(ft_isprint('~') && isprint('~'), "'~' is printable");
	check(!ft_isprint('\t') && !isprint('\t'), "tab is not printable");
	check(!ft_isprint(127), "127 is not printable");
	end_fn();
}

static void	test_toupper(void)
{
	start_fn("ft_toupper");
	check(ft_toupper('a') == 'A', "'a' should become 'A'");
	check(ft_toupper('z') == 'Z', "'z' should become 'Z'");
	check(ft_toupper('A') == 'A', "'A' should stay 'A'");
	check(ft_toupper('1') == '1', "'1' should stay '1'");
	end_fn();
}

static void	test_tolower(void)
{
	start_fn("ft_tolower");
	check(ft_tolower('A') == 'a', "'A' should become 'a'");
	check(ft_tolower('Z') == 'z', "'Z' should become 'z'");
	check(ft_tolower('a') == 'a', "'a' should stay 'a'");
	check(ft_tolower('1') == '1', "'1' should stay '1'");
	end_fn();
}

/* ===== MEMORY ===== */

static void	test_memset(void)
{
	char	buf[10];

	start_fn("ft_memset");
	ft_memset(buf, 'X', 5);
	buf[5] = '\0';
	check(memcmp(buf, "XXXXX", 5) == 0, "buffer should contain 'XXXXX'");
	ft_memset(buf, 0, 10);
	check(buf[0] == 0 && buf[9] == 0, "buffer should be zeroed");
	check(ft_memset(buf, 'A', 0) == (void *)buf, "n=0 should return dst");
	end_fn();
}

static void	test_bzero(void)
{
	char	buf[8];

	start_fn("ft_bzero");
	memset(buf, 'A', 8);
	ft_bzero(buf, 5);
	check(buf[0] == 0 && buf[4] == 0, "first 5 bytes should be zero");
	check(buf[5] == 'A', "byte at index 5 should remain 'A'");
	end_fn();
}

static void	test_memcpy(void)
{
	char	dst[20];

	start_fn("ft_memcpy");
	ft_memcpy(dst, "hello", 6);
	check(memcmp(dst, "hello", 6) == 0, "dst should contain 'hello'");
	check(ft_memcpy(dst, "world", 5) == dst, "return value should be dst");
	end_fn();
}

static void	test_memmove(void)
{
	char	buf[20];

	start_fn("ft_memmove");
	strcpy(buf, "abcdef");
	ft_memmove(buf + 2, buf, 4);
	check(memcmp(buf + 2, "abcd", 4) == 0, "should handle forward overlap");
	strcpy(buf, "abcdef");
	ft_memmove(buf, buf + 2, 4);
	check(memcmp(buf, "cdef", 4) == 0, "should handle backward overlap");
	end_fn();
}

static void	test_memchr(void)
{
	const char	*s = "hello world";

	start_fn("ft_memchr");
	check(ft_memchr(s, 'o', 11) == memchr(s, 'o', 11), "should match libc");
	check(ft_memchr(s, 'z', 11) == NULL, "should return NULL when not found");
	check(ft_memchr(s, 'h', 11) == s, "should return pointer to first char");
	check(ft_memchr(s, 'd', 5) == NULL, "should not search past n bytes");
	end_fn();
}

static void	test_memcmp(void)
{
	start_fn("ft_memcmp");
	check(ft_memcmp("abc", "abc", 3) == 0, "equal buffers should return 0");
	check(ft_memcmp("abc", "abd", 3) < 0, "'abc' < 'abd' should be negative");
	check(ft_memcmp("abd", "abc", 3) > 0, "'abd' > 'abc' should be positive");
	check(ft_memcmp("abc", "xyz", 0) == 0, "n=0 should always return 0");
	end_fn();
}

/* ===== STRINGS ===== */

static void	test_strlen(void)
{
	start_fn("ft_strlen");
	check(ft_strlen("hello") == 5, "should return 5");
	check(ft_strlen("") == 0, "should return 0");
	check(ft_strlen("a") == 1, "should return 1");
	end_fn();
}

static void	test_strlcpy(void)
{
	char	dst[10];

	start_fn("ft_strlcpy");
	check(ft_strlcpy(dst, "hello", 10) == 5 && strcmp(dst, "hello") == 0,
		"basic copy should return 5 and copy 'hello'");
	check(ft_strlcpy(dst, "hello", 3) == 5 && strcmp(dst, "he") == 0,
		"should truncate to 'he' and return 5");
	check(ft_strlcpy(dst, "hello", 0) == 5,
		"should return src length even with size=0");
	end_fn();
}

static void	test_strlcat(void)
{
	char	dst[20];

	start_fn("ft_strlcat");
	strcpy(dst, "foo");
	check(ft_strlcat(dst, "bar", 20) == 6 && strcmp(dst, "foobar") == 0,
		"should concat to 'foobar' and return 6");
	strcpy(dst, "foo");
	check(ft_strlcat(dst, "bar", 5) == 6 && strcmp(dst, "foob") == 0,
		"should truncate to 'foob' and return 6");
	end_fn();
}

static void	test_strchr(void)
{
	const char	*s = "hello";

	start_fn("ft_strchr");
	check(ft_strchr(s, 'l') == strchr(s, 'l'), "should match libc strchr");
	check(ft_strchr(s, 'z') == NULL, "should return NULL when not found");
	check(ft_strchr(s, '\0') == s + 5, "should find '\\0' at end of string");
	end_fn();
}

static void	test_strrchr(void)
{
	const char	*s = "hello";

	start_fn("ft_strrchr");
	check(ft_strrchr(s, 'l') == strrchr(s, 'l'), "should match libc strrchr");
	check(ft_strrchr(s, 'z') == NULL, "should return NULL when not found");
	end_fn();
}

static void	test_strncmp(void)
{
	start_fn("ft_strncmp");
	check(ft_strncmp("abc", "abc", 3) == 0, "equal strings should return 0");
	check(ft_strncmp("abc", "abd", 3) < 0, "'abc' < 'abd' should be negative");
	check(ft_strncmp("abd", "abc", 3) > 0, "'abd' > 'abc' should be positive");
	check(ft_strncmp("abc", "xyz", 0) == 0, "n=0 should always return 0");
	check(ft_strncmp("abcd", "abce", 3) == 0,
		"common prefix of length n should return 0");
	end_fn();
}

static void	test_strnstr(void)
{
	start_fn("ft_strnstr");
	check(ft_strnstr("hello world", "world", 11)
		== strstr("hello world", "world"),
		"should find 'world' in 'hello world'");
	check(ft_strnstr("hello world", "world", 5) == NULL,
		"should return NULL when needle is outside range");
	check(ft_strnstr("hello", "", 5) != NULL,
		"empty needle should return haystack");
	check(ft_strnstr("", "", 0) != NULL,
		"empty needle with n=0 should return haystack");
	end_fn();
}

static void	test_strdup(void)
{
	char	*orig = "hello";
	char	*dup;

	start_fn("ft_strdup");
	dup = ft_strdup(orig);
	check(dup && strcmp(dup, orig) == 0, "dup should contain 'hello'");
	check(dup && dup != orig, "dup should be a new allocation");
	free(dup);
	dup = ft_strdup("");
	check(dup && strcmp(dup, "") == 0, "dup of empty string should be empty");
	free(dup);
	end_fn();
}

/* ===== CONVERSION ===== */

static void	test_atoi(void)
{
	start_fn("ft_atoi");
	check(ft_atoi("42") == 42, "expected 42");
	check(ft_atoi("-42") == -42, "expected -42");
	check(ft_atoi("  +10") == 10, "expected 10");
	check(ft_atoi("0") == 0, "expected 0");
	check(ft_atoi("   123abc") == 123, "expected 123, should stop at 'a'");
	check(ft_atoi("2147483647") == INT_MAX, "expected INT_MAX");
	check(ft_atoi("-2147483648") == INT_MIN, "expected INT_MIN");
	end_fn();
}

static void	test_itoa(void)
{
	char	*s;

	start_fn("ft_itoa");
	s = ft_itoa(42);
	check(s && strcmp(s, "42") == 0, "expected \"42\"");
	free(s);
	s = ft_itoa(-42);
	check(s && strcmp(s, "-42") == 0, "expected \"-42\"");
	free(s);
	s = ft_itoa(0);
	check(s && strcmp(s, "0") == 0, "expected \"0\"");
	free(s);
	s = ft_itoa(INT_MIN);
	check(s && strcmp(s, "-2147483648") == 0, "expected \"-2147483648\"");
	free(s);
	s = ft_itoa(INT_MAX);
	check(s && strcmp(s, "2147483647") == 0, "expected \"2147483647\"");
	free(s);
	end_fn();
}

/* ===== ALLOCATION ===== */

static void	test_calloc(void)
{
	char	*p;

	start_fn("ft_calloc");
	p = ft_calloc(5, sizeof(char));
	check(p && p[0] == 0 && p[4] == 0, "allocated memory should be zeroed");
	free(p);
	p = ft_calloc(0, sizeof(int));
	check(p != NULL, "should return a valid pointer even with size=0");
	free(p);
	end_fn();
}

/* ===== STRING MANIPULATION ===== */

static void	test_substr(void)
{
	char	*s;

	start_fn("ft_substr");
	s = ft_substr("hello world", 6, 5);
	check(s && strcmp(s, "world") == 0, "expected \"world\"");
	free(s);
	s = ft_substr("hello", 10, 3);
	check(s && strcmp(s, "") == 0,
		"start beyond length should give empty string");
	free(s);
	s = ft_substr("hello", 1, 2);
	check(s && strcmp(s, "el") == 0, "expected \"el\"");
	free(s);
	end_fn();
}

static void	test_strjoin(void)
{
	char	*s;

	start_fn("ft_strjoin");
	s = ft_strjoin("hello ", "world");
	check(s && strcmp(s, "hello world") == 0, "expected \"hello world\"");
	free(s);
	s = ft_strjoin("", "world");
	check(s && strcmp(s, "world") == 0, "expected \"world\"");
	free(s);
	s = ft_strjoin("hello", "");
	check(s && strcmp(s, "hello") == 0, "expected \"hello\"");
	free(s);
	end_fn();
}

static void	test_strtrim(void)
{
	char	*s;

	start_fn("ft_strtrim");
	s = ft_strtrim("  hello  ", " ");
	check(s && strcmp(s, "hello") == 0, "expected \"hello\"");
	free(s);
	s = ft_strtrim("xxhelloxx", "x");
	check(s && strcmp(s, "hello") == 0, "expected \"hello\"");
	free(s);
	s = ft_strtrim("hello", "xyz");
	check(s && strcmp(s, "hello") == 0, "expected \"hello\" unchanged");
	free(s);
	s = ft_strtrim("   ", " ");
	check(s && strcmp(s, "") == 0, "expected empty string");
	free(s);
	end_fn();
}

static void	test_split(void)
{
	char	**res;
	int		i;

	start_fn("ft_split");
	res = ft_split("hello world foo", ' ');
	check(res && strcmp(res[0], "hello") == 0
		&& strcmp(res[1], "world") == 0 && strcmp(res[2], "foo") == 0
		&& res[3] == NULL,
		"expected [\"hello\", \"world\", \"foo\", NULL]");
	i = 0;
	while (res[i])
		free(res[i++]);
	free(res);

	res = ft_split("  hello  ", ' ');
	check(res && strcmp(res[0], "hello") == 0 && res[1] == NULL,
		"expected [\"hello\", NULL]");
	i = 0;
	while (res[i])
		free(res[i++]);
	free(res);

	res = ft_split("", ' ');
	check(res && res[0] == NULL, "expected [NULL]");
	free(res);
	end_fn();
}

static char	upcase(unsigned int i, char c)
{
	(void)i;
	return (toupper(c));
}

static void	test_strmapi(void)
{
	char	*s;

	start_fn("ft_strmapi");
	s = ft_strmapi("hello", upcase);
	check(s && strcmp(s, "HELLO") == 0, "expected \"HELLO\"");
	free(s);
	s = ft_strmapi("", upcase);
	check(s && strcmp(s, "") == 0, "expected empty string");
	free(s);
	end_fn();
}

static void	striteri_upcase(unsigned int i, char *c)
{
	(void)i;
	*c = toupper(*c);
}

static void	test_striteri(void)
{
	char	buf[10];

	start_fn("ft_striteri");
	strcpy(buf, "hello");
	ft_striteri(buf, striteri_upcase);
	check(strcmp(buf, "HELLO") == 0,
		"buffer should be \"HELLO\" after iteration");
	end_fn();
}

/* ===== OUTPUT (written to fd 1) ===== */

static void	test_put_fds(void)
{
	printf("\n%s--- ft_put*_fd (visual check on stdout) ---%s\n", CYAN, RESET);
	printf("  putchar_fd: ");
	ft_putchar_fd('X', 1);
	printf("\n  putstr_fd:  ");
	ft_putstr_fd("hello", 1);
	printf("\n  putendl_fd: ");
	ft_putendl_fd("hello", 1);
	printf("  putnbr_fd:  ");
	ft_putnbr_fd(-42, 1);
	printf("\n  putnbr_fd INT_MIN: ");
	ft_putnbr_fd(INT_MIN, 1);
	printf("\n");
}

/* ===== LIST ===== */

static void	del_int(void *p)
{
	free(p);
}

static void	*dup_int(void *p)
{
	int	*n;

	n = malloc(sizeof(int));
	if (!n)
		return (NULL);
	*n = *(int *)p;
	return (n);
}

static void	iter_inc(void *p)
{
	(*(int *)p)++;
}

static void	test_list(void)
{
	t_list	*lst;
	t_list	*lst2;
	t_list	*tmp;
	int		*v1;
	int		*v2;
	int		*v3;
	int		*vtmp;

	v1 = malloc(sizeof(int)); *v1 = 1;
	v2 = malloc(sizeof(int)); *v2 = 2;
	v3 = malloc(sizeof(int)); *v3 = 3;

	start_fn("ft_lstnew");
	lst = ft_lstnew(v1);
	check(lst && *(int *)lst->content == 1, "new node should contain value 1");
	check(lst && lst->next == NULL, "new node's next should be NULL");
	end_fn();

	start_fn("ft_lstadd_front");
	ft_lstadd_front(&lst, ft_lstnew(v2));
	check(*(int *)lst->content == 2, "front of list should now contain 2");
	end_fn();

	start_fn("ft_lstadd_back");
	ft_lstadd_back(&lst, ft_lstnew(v3));
	check(*(int *)ft_lstlast(lst)->content == 3, "last node should contain 3");
	end_fn();

	start_fn("ft_lstsize");
	check(ft_lstsize(lst) == 3, "list size should be 3");
	end_fn();

	start_fn("ft_lstlast");
	check(*(int *)ft_lstlast(lst)->content == 3, "last node should contain 3");
	end_fn();

	start_fn("ft_lstiter");
	ft_lstiter(lst, iter_inc);
	check(*(int *)lst->content == 3,
		"first node should now be 3 (was 2 before increment)");
	end_fn();

	start_fn("ft_lstmap");
	lst2 = ft_lstmap(lst, dup_int, del_int);
	check(lst2 != NULL, "lstmap should return a new list");
	check(ft_lstsize(lst2) == 3, "mapped list should have size 3");
	end_fn();
	ft_lstclear(&lst2, del_int);

	start_fn("ft_lstdelone");
	vtmp = malloc(sizeof(int));
	*vtmp = 42;
	tmp = ft_lstnew(vtmp);
	ft_lstdelone(tmp, del_int);
	check(1, "should not crash when freeing isolated node");
	end_fn();

	start_fn("ft_lstclear");
	ft_lstclear(&lst, del_int);
	check(lst == NULL, "lst should be NULL after clear");
	end_fn();
}

/* ===== MAIN ===== */

int	main(void)
{
	test_isalpha();
	test_isdigit();
	test_isalnum();
	test_isascii();
	test_isprint();
	test_toupper();
	test_tolower();

	test_memset();
	test_bzero();
	test_memcpy();
	test_memmove();
	test_memchr();
	test_memcmp();

	test_strlen();
	test_strlcpy();
	test_strlcat();
	test_strchr();
	test_strrchr();
	test_strncmp();
	test_strnstr();
	test_strdup();

	test_atoi();
	test_itoa();
	test_calloc();

	test_substr();
	test_strjoin();
	test_strtrim();
	test_split();
	test_strmapi();
	test_striteri();

	test_put_fds();

	printf("\n");
	test_list();

	printf("\n%s%s", BOLD, CYAN);
	printf("========================================\n");
	printf("  %sPASSED: %s%d%s | %sFAILED: %s%d%s | TOTAL: %d%s%s\n",
		RESET, GREEN, g_pass, RESET,
		RESET, RED, g_fail, RESET, g_pass + g_fail, BOLD, CYAN);
	printf("========================================%s\n", RESET);
	return (g_fail > 0 ? 1 : 0);
}