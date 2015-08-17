#include "othm_base.h"
#include <stdio.h>
#include <stdlib.h>

const struct othm_pair OTHM_NULL_PAIR = {
	.first  = NULL,
	.second = NULL
};

/* Creates a new request */
struct othm_request *othm_request_new(int (*check_key)(void *storage, void *data),
				      void *key_type, int data_size, void *data)
{
	struct othm_request *request;
	request = malloc(sizeof(struct othm_request));
	request->check_key = check_key;
	request->key_type = key_type;
	request->data_size = data_size;
	request->data = data;
	return request;
}

/* Creates a new pair */
struct othm_pair othm_pair_new(void *first, void *second)
{
	struct othm_pair pair;

	pair.first = first;
	pair.second = second;
	return pair;
}

struct othm_funct *othm_funct_new(void (*function)(void), char *name)
{
	struct othm_funct *new_funct = malloc(sizeof(struct othm_funct));;

	new_funct->function = function;
	new_funct->name = name;
	return new_funct;
}

char *othm_load_file(char *file_name)
{
	FILE *f;
	char *contents;
	long fsize;

	f = fopen(file_name, "rb");
	fseek(f, 0, SEEK_END);
	fsize = ftell(f);
	fseek(f, 0, SEEK_SET);

	contents = malloc(fsize + 1);
	fread(contents, fsize, 1, f);
	fclose(f);
	contents[fsize] = '\0';

        return contents;
}
