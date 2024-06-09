#include <criterion/criterion.h>
#include <stdio.h>
#include <fcntl.h>
#include "../get_next_line.h"

Test(gnl_mandatory, basic_text)
{
	int fd = open("txt/manifesto.txt", O_RDONLY);
	char *line;

	line = get_next_line(fd);
	cr_expect_str_eq(line, "MANIFESTO OF THE COMMUNIST PARTY\n");
	free(line);

	line = get_next_line(fd);
	cr_expect_str_eq(line, "\n");
	free(line);

	line = get_next_line(fd);
	cr_expect_str_eq(line, "[From the English edition of 1888, edited by Friedrich Engels]\n");
	free(line);

	line = get_next_line(fd);
	cr_expect_str_eq(line, "\n");
	free(line);

	line = get_next_line(fd);
	cr_expect_str_eq(line, "\n");
	free(line);

	line = get_next_line(fd);
	cr_expect_str_eq(line, "A spectre is haunting Europe--the spectre of Communism.\n");
	free(line);

	for (int i = 6; i < 1485; i++)
		free(get_next_line(fd));

	line = get_next_line(fd);
	cr_expect_str_eq(line, "\n");
	free(line);

	line = get_next_line(fd);
	cr_expect_str_eq(line, "           WORKING MEN OF ALL COUNTRIES, UNITE!\n");
	free(line);

	line = get_next_line(fd);
	printf("\n%s\n",line);
	free(line);
	line = get_next_line(fd);
	printf("\n%s\n",line);
	free(line);
	line = get_next_line(fd);
	printf("\n%s\n",line);
	free(line);
	line = get_next_line(fd);
	printf("\n%s\n",line);
	free(line);
//	cr_expect_null(line);

	close(fd);
}
