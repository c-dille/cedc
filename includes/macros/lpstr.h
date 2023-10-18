#ifndef LPSTR_H
# define LPSTR_H

typedef struct s_lpstr
{
	size_t	len;
	char	*str;
} lpstr;

lpstr	lp(char *str)
{
	return ((lpstr){strlen(str), str});
}

void	lpstr_free(lpstr str)
{
	str.len = 0;
	free(str.str);
}

lpstr	lpstr_clone(lpstr str)
{
	return (lpstr){.len = str.len, .str = strdup(str.str)};
}

DEF_LIST_PROTO(lpstr, lpstr_list);
DEF_LIST(lpstr, lpstr_list, lpstr_free, lpstr_clone);

bool	lpstr_begins_with(lpstr haystack, const char *needle)
{
	return (!strncmp(haystack.str, needle, haystack.len));
}
#endif
