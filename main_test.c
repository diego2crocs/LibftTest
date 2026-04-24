#include "libft.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

static int	g_pass = 0;
static int	g_fail = 0;

static void	check(const char *name, int ok, const char *err)
{
	if (ok)
	{
		printf("  ✅ OK  %s\n", name);
		g_pass++;
	}
	else
	{
		printf("  ❌ KO  %s : %s\n", name, err);
		g_fail++;
	}
}

/* ===== CHARACTER CHECKS ===== */

static void	test_isalpha(void)
{
	printf("\n--- ft_isalpha ---\n");
	check("'a'", ft_isalpha('a') && isalpha('a'), "should accept 'a'");
	check("'Z'", ft_isalpha('Z') && isalpha('Z'), "should accept 'Z'");
	check("'0'", !ft_isalpha('0') && !isalpha('0'), "should reject '0'");
	check("' '", !ft_isalpha(' ') && !isalpha(' '), "should reject space");
	check("'\\0'", !ft_isalpha('\0'), "should reject null byte");
}

static void	test_isdigit(void)
{
	printf("\n--- ft_isdigit ---\n");
	check("'5'", ft_isdigit('5') && isdigit('5'), "should accept '5'");
	check("'0'", ft_isdigit('0') && isdigit('0'), "should accept '0'");
	check("'9'", ft_isdigit('9') && isdigit('9'), "should accept '9'");
	check("'a'", !ft_isdigit('a') && !isdigit('a'), "should reject 'a'");
	check("' '", !ft_isdigit(' '), "should reject space");
}

static void	test_isalnum(void)
{
	printf("\n--- ft_isalnum ---\n");
	check("'a'", ft_isalnum('a') && isalnum('a'), "should accept 'a'");
	check("'5'", ft_isalnum('5') && isalnum('5'), "should accept '5'");
	check("'!'", !ft_isalnum('!') && !isalnum('!'), "should reject '!'");
}

static void	test_isascii(void)
{
	printf("\n--- ft_isascii ---\n");
	check("0",   ft_isascii(0), "0 is ASCII");
	check("127", ft_isascii(127), "127 is ASCII");
	check("128", !ft_isascii(128), "128 is not ASCII");
	check("-1",  !ft_isascii(-1), "-1 is not ASCII");
}

static void	test_isprint(void)
{
	printf("\n--- ft_isprint ---\n");
	check("' '",  ft_isprint(' ') && isprint(' '), "space is printable");
	check("'~'",  ft_isprint('~') && isprint('~'), "'~' is printable");
	check("'\\t'", !ft_isprint('\t') && !isprint('\t'), "tab is not printable");
	check("127",  !ft_isprint(127), "127 is not printable");
}

static void	test_toupper(void)
{
	printf("\n--- ft_toupper ---\n");
	check("'a'->'A'", ft_toupper('a') == 'A', "'a' should become 'A'");
	check("'z'->'Z'", ft_toupper('z') == 'Z', "'z' should become 'Z'");
	check("'A' unchanged", ft_toupper('A') == 'A', "'A' should stay 'A'");
	check("'1' unchanged", ft_toupper('1') == '1', "'1' should stay '1'");
}

static void	test_tolower(void)
{
	printf("\n--- ft_tolower ---\n");
	check("'A'->'a'", ft_tolower('A') == 'a', "'A' should become 'a'");
	check("'Z'->'z'", ft_tolower('Z') == 'z', "'Z' should become 'z'");
	check("'a' unchanged", ft_tolower('a') == 'a', "'a' should stay 'a'");
	check("'1' unchanged", ft_tolower('1') == '1', "'1' should stay '1'");
}

/* ===== MEMORY ===== */

static void	test_memset(void)
{
	char	buf[10];

	printf("\n--- ft_memset ---\n");
	ft_memset(buf, 'X', 5);
	buf[5] = '\0';
	check("fills 5 bytes", memcmp(buf, "XXXXX", 5) == 0,
		"buffer should contain 'XXXXX'");
	ft_memset(buf, 0, 10);
	check("zero fill", buf[0] == 0 && buf[9] == 0,
		"buffer should be zeroed");
	check("n=0 no-op", ft_memset(buf, 'A', 0) == (void *)buf,
		"should return dst untouched");
}

static void	test_bzero(void)
{
	char	buf[8];

	printf("\n--- ft_bzero ---\n");
	memset(buf, 'A', 8);
	ft_bzero(buf, 5);
	check("zeros 5 bytes", buf[0] == 0 && buf[4] == 0,
		"first 5 bytes should be zero");
	check("leaves rest", buf[5] == 'A',
		"byte at index 5 should remain 'A'");
}

static void	test_memcpy(void)
{
	char	dst[20];

	printf("\n--- ft_memcpy ---\n");
	ft_memcpy(dst, "hello", 6);
	check("basic copy", memcmp(dst, "hello", 6) == 0,
		"dst should contain 'hello'");
	check("returns dst", ft_memcpy(dst, "world", 5) == dst,
		"return value should be dst pointer");
}

static void	test_memmove(void)
{
	char	buf[20];

	printf("\n--- ft_memmove ---\n");
	strcpy(buf, "abcdef");
	ft_memmove(buf + 2, buf, 4);
	check("overlap forward", memcmp(buf + 2, "abcd", 4) == 0,
		"should handle forward overlap");
	strcpy(buf, "abcdef");
	ft_memmove(buf, buf + 2, 4);
	check("overlap backward", memcmp(buf, "cdef", 4) == 0,
		"should handle backward overlap");
}

static void	test_memchr(void)
{
	const char	*s = "hello world";

	printf("\n--- ft_memchr ---\n");
	check("found", ft_memchr(s, 'o', 11) == memchr(s, 'o', 11),
		"should match libc memchr");
	check("not found", ft_memchr(s, 'z', 11) == NULL,
		"should return NULL when char not found");
	check("found at start", ft_memchr(s, 'h', 11) == s,
		"should return pointer to first char");
	check("beyond n", ft_memchr(s, 'd', 5) == NULL,
		"should not search past n bytes");
}

static void	test_memcmp(void)
{
	printf("\n--- ft_memcmp ---\n");
	check("equal", ft_memcmp("abc", "abc", 3) == 0,
		"equal buffers should return 0");
	check("less", ft_memcmp("abc", "abd", 3) < 0,
		"'abc' < 'abd' should return negative");
	check("greater", ft_memcmp("abd", "abc", 3) > 0,
		"'abd' > 'abc' should return positive");
	check("n=0", ft_memcmp("abc", "xyz", 0) == 0,
		"n=0 should always return 0");
}

/* ===== STRINGS ===== */

static void	test_strlen(void)
{
	printf("\n--- ft_strlen ---\n");
	check("\"hello\"", ft_strlen("hello") == 5, "should return 5");
	check("empty", ft_strlen("") == 0, "should return 0");
	check("one char", ft_strlen("a") == 1, "should return 1");
}

static void	test_strlcpy(void)
{
	char	dst[10];

	printf("\n--- ft_strlcpy ---\n");
	check("basic",
		ft_strlcpy(dst, "hello", 10) == 5 && strcmp(dst, "hello") == 0,
		"should copy 'hello' and return 5");
	check("truncated",
		ft_strlcpy(dst, "hello", 3) == 5 && strcmp(dst, "he") == 0,
		"should truncate to 'he' and return 5");
	check("size=0", ft_strlcpy(dst, "hello", 0) == 5,
		"should return src length even with size=0");
}

static void	test_strlcat(void)
{
	char	dst[20];

	printf("\n--- ft_strlcat ---\n");
	strcpy(dst, "foo");
	check("basic",
		ft_strlcat(dst, "bar", 20) == 6 && strcmp(dst, "foobar") == 0,
		"should concat to 'foobar' and return 6");
	strcpy(dst, "foo");
	check("truncated",
		ft_strlcat(dst, "bar", 5) == 6 && strcmp(dst, "foob") == 0,
		"should truncate to 'foob' and return 6");
}

static void	test_strchr(void)
{
	const char	*s = "hello";

	printf("\n--- ft_strchr ---\n");
	check("found", ft_strchr(s, 'l') == strchr(s, 'l'),
		"should match libc strchr");
	check("not found", ft_strchr(s, 'z') == NULL,
		"should return NULL when not found");
	check("nul char", ft_strchr(s, '\0') == s + 5,
		"should find '\\0' at end of string");
}

static void	test_strrchr(void)
{
	const char	*s = "hello";

	printf("\n--- ft_strrchr ---\n");
	check("last 'l'", ft_strrchr(s, 'l') == strrchr(s, 'l'),
		"should match libc strrchr");
	check("not found", ft_strrchr(s, 'z') == NULL,
		"should return NULL when not found");
}

static void	test_strncmp(void)
{
	printf("\n--- ft_strncmp ---\n");
	check("equal", ft_strncmp("abc", "abc", 3) == 0,
		"equal strings should return 0");
	check("less", ft_strncmp("abc", "abd", 3) < 0,
		"'abc' < 'abd' should return negative");
	check("greater", ft_strncmp("abd", "abc", 3) > 0,
		"'abd' > 'abc' should return positive");
	check("n=0", ft_strncmp("abc", "xyz", 0) == 0,
		"n=0 should always return 0");
	check("prefix", ft_strncmp("abcd", "abce", 3) == 0,
		"common prefix of length n should return 0");
}

static void	test_strnstr(void)
{
	printf("\n--- ft_strnstr ---\n");
	check("found", ft_strnstr("hello world", "world", 11)
		== strstr("hello world", "world"),
		"should find 'world' in 'hello world'");
	check("not in range", ft_strnstr("hello world", "world", 5) == NULL,
		"should return NULL when needle is outside range");
	check("empty needle", ft_strnstr("hello", "", 5) != NULL,
		"empty needle should return haystack");
	check("empty haystack+needle", ft_strnstr("", "", 0) != NULL,
		"empty needle with n=0 should return haystack");
}

static void	test_strdup(void)
{
	const char	*orig = "hello";
	char		*dup;

	printf("\n--- ft_strdup ---\n");
	dup = ft_strdup(orig);
	check("content", dup && strcmp(dup, orig) == 0,
		"dup should contain 'hello'");
	check("different ptr", dup && dup != orig,
		"dup should be a new allocation");
	free(dup);
	dup = ft_strdup("");
	check("empty string", dup && strcmp(dup, "") == 0,
		"dup of empty string should be empty");
	free(dup);
}

/* ===== CONVERSION ===== */

static void	test_atoi(void)
{
	printf("\n--- ft_atoi ---\n");
	check("\"42\"", ft_atoi("42") == 42, "expected 42");
	check("\"-42\"", ft_atoi("-42") == -42, "expected -42");
	check("\"  +10\"", ft_atoi("  +10") == 10, "expected 10");
	check("\"0\"", ft_atoi("0") == 0, "expected 0");
	check("leading spaces", ft_atoi("   123abc") == 123,
		"expected 123, should stop at 'a'");
	check("INT_MAX", ft_atoi("2147483647") == INT_MAX,
		"expected INT_MAX");
	check("INT_MIN", ft_atoi("-2147483648") == INT_MIN,
		"expected INT_MIN");
}

static void	test_itoa(void)
{
	char	*s;

	printf("\n--- ft_itoa ---\n");
	s = ft_itoa(42);
	check("42", s && strcmp(s, "42") == 0, "expected \"42\"");
	free(s);
	s = ft_itoa(-42);
	check("-42", s && strcmp(s, "-42") == 0, "expected \"-42\"");
	free(s);
	s = ft_itoa(0);
	check("0", s && strcmp(s, "0") == 0, "expected \"0\"");
	free(s);
	s = ft_itoa(INT_MIN);
	check("INT_MIN", s && strcmp(s, "-2147483648") == 0,
		"expected \"-2147483648\"");
	free(s);
	s = ft_itoa(INT_MAX);
	check("INT_MAX", s && strcmp(s, "2147483647") == 0,
		"expected \"2147483647\"");
	free(s);
}

/* ===== ALLOCATION ===== */

static void	test_calloc(void)
{
	char	*p;

	printf("\n--- ft_calloc ---\n");
	p = ft_calloc(5, sizeof(char));
	check("zeroed", p && p[0] == 0 && p[4] == 0,
		"allocated memory should be zeroed");
	free(p);
	p = ft_calloc(0, sizeof(int));
	check("size=0 not NULL", p != NULL,
		"should return a valid pointer even with size=0");
	free(p);
}

/* ===== STRING MANIPULATION ===== */

static void	test_substr(void)
{
	char	*s;

	printf("\n--- ft_substr ---\n");
	s = ft_substr("hello world", 6, 5);
	check("basic", s && strcmp(s, "world") == 0,
		"expected \"world\"");
	free(s);
	s = ft_substr("hello", 10, 3);
	check("start > len", s && strcmp(s, "") == 0,
		"start beyond length should give empty string");
	free(s);
	s = ft_substr("hello", 1, 2);
	check("truncated len", s && strcmp(s, "el") == 0,
		"expected \"el\"");
	free(s);
}

static void	test_strjoin(void)
{
	char	*s;

	printf("\n--- ft_strjoin ---\n");
	s = ft_strjoin("hello ", "world");
	check("basic", s && strcmp(s, "hello world") == 0,
		"expected \"hello world\"");
	free(s);
	s = ft_strjoin("", "world");
	check("empty s1", s && strcmp(s, "world") == 0,
		"expected \"world\"");
	free(s);
	s = ft_strjoin("hello", "");
	check("empty s2", s && strcmp(s, "hello") == 0,
		"expected \"hello\"");
	free(s);
}

static void	test_strtrim(void)
{
	char	*s;

	printf("\n--- ft_strtrim ---\n");
	s = ft_strtrim("  hello  ", " ");
	check("spaces", s && strcmp(s, "hello") == 0,
		"expected \"hello\"");
	free(s);
	s = ft_strtrim("xxhelloxx", "x");
	check("custom set", s && strcmp(s, "hello") == 0,
		"expected \"hello\"");
	free(s);
	s = ft_strtrim("hello", "xyz");
	check("no trim", s && strcmp(s, "hello") == 0,
		"expected \"hello\" unchanged");
	free(s);
	s = ft_strtrim("   ", " ");
	check("all trimmed", s && strcmp(s, "") == 0,
		"expected empty string");
	free(s);
}

static void	test_split(void)
{
	char	**res;
	int		i;

	printf("\n--- ft_split ---\n");
	res = ft_split("hello world foo", ' ');
	check("3 words", res && strcmp(res[0], "hello") == 0
		&& strcmp(res[1], "world") == 0 && strcmp(res[2], "foo") == 0
		&& res[3] == NULL,
		"expected [\"hello\", \"world\", \"foo\", NULL]");
	i = 0;
	while (res[i])
		free(res[i++]);
	free(res);

	res = ft_split("  hello  ", ' ');
	check("leading/trailing sep", res && strcmp(res[0], "hello") == 0
		&& res[1] == NULL,
		"expected [\"hello\", NULL]");
	i = 0;
	while (res[i])
		free(res[i++]);
	free(res);

	res = ft_split("", ' ');
	check("empty string", res && res[0] == NULL,
		"expected [NULL]");
	free(res);
}

static char	upcase(unsigned int i, char c)
{
	(void)i;
	return (toupper(c));
}

static void	test_strmapi(void)
{
	char	*s;

	printf("\n--- ft_strmapi ---\n");
	s = ft_strmapi("hello", upcase);
	check("toupper", s && strcmp(s, "HELLO") == 0,
		"expected \"HELLO\"");
	free(s);
	s = ft_strmapi("", upcase);
	check("empty", s && strcmp(s, "") == 0,
		"expected empty string");
	free(s);
}

static void	striteri_upcase(unsigned int i, char *c)
{
	(void)i;
	*c = toupper(*c);
}

static void	test_striteri(void)
{
	char	buf[10];

	printf("\n--- ft_striteri ---\n");
	strcpy(buf, "hello");
	ft_striteri(buf, striteri_upcase);
	check("in-place toupper", strcmp(buf, "HELLO") == 0,
		"buffer should be \"HELLO\" after iteration");
}

/* ===== OUTPUT (written to fd 1) ===== */

static void	test_put_fds(void)
{
	printf("\n--- ft_put*_fd (visual check on stdout) ---\n");
	printf("  putchar_fd: ");
	ft_putchar_fd('X', 1);
	printf("\n");
	printf("  putstr_fd: ");
	ft_putstr_fd("hello", 1);
	printf("\n");
	printf("  putendl_fd: ");
	ft_putendl_fd("hello", 1);
	printf("  putnbr_fd: ");
	ft_putnbr_fd(-42, 1);
	printf("\n");
	printf("  putnbr_fd INT_MIN: ");
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

	printf("\n--- ft_lst* ---\n");

	v1 = malloc(sizeof(int)); *v1 = 1;
	v2 = malloc(sizeof(int)); *v2 = 2;
	v3 = malloc(sizeof(int)); *v3 = 3;

	lst = ft_lstnew(v1);
	check("lstnew content", lst && *(int *)lst->content == 1,
		"new node should contain value 1");
	check("lstnew next=NULL", lst && lst->next == NULL,
		"new node's next should be NULL");

	ft_lstadd_front(&lst, ft_lstnew(v2));
	check("lstadd_front", *(int *)lst->content == 2,
		"front of list should now contain 2");

	ft_lstadd_back(&lst, ft_lstnew(v3));
	check("lstadd_back", *(int *)ft_lstlast(lst)->content == 3,
		"last node should contain 3");

	check("lstsize=3", ft_lstsize(lst) == 3,
		"list size should be 3");
	check("lstlast=3", *(int *)ft_lstlast(lst)->content == 3,
		"last node should contain 3");

	ft_lstiter(lst, iter_inc);
	check("lstiter inc", *(int *)lst->content == 3,
		"first node should now be 3 (was 2 before increment)");

	lst2 = ft_lstmap(lst, dup_int, del_int);
	check("lstmap not NULL", lst2 != NULL,
		"lstmap should return a new list");
	check("lstmap size", ft_lstsize(lst2) == 3,
		"mapped list should have size 3");
	ft_lstclear(&lst2, del_int);
	check("lstclear lst2=NULL", lst2 == NULL,
		"lst2 should be NULL after clear");

	/* lstdelone : test sur un nœud isolé pour ne pas casser lst */
	vtmp = malloc(sizeof(int));
	*vtmp = 42;
	tmp = ft_lstnew(vtmp);
	ft_lstdelone(tmp, del_int);
	check("lstdelone", 1, "should not crash when freeing isolated node");

	ft_lstclear(&lst, del_int);
	check("lstclear lst=NULL", lst == NULL,
		"lst should be NULL after clear");
}

/* ===== MAIN ===== */

int	main(void)
{
	printf("========================================\n");
	printf("               LIBFT TEST               \n");
	printf("========================================\n");

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

	test_list();

	printf("\n========================================\n");
	printf("  PASSED: %d | FAILED: %d | TOTAL: %d\n",
		g_pass, g_fail, g_pass + g_fail);
	printf("========================================\n");
	return (g_fail > 0 ? 1 : 0);
}