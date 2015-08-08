#include <othm_base.h>
#include <stdio.h>

void print_input(char *input)
{
	printf("%s", input);
}

int main(void)
{
	struct othm_funct *printer = OTHM_FUNCT(print_input);
	((void (*) (char *)) printer->function)
		("You built othm-base!\n");
	return 0;
}
