#include "othm_base.h"
#include <stdlib.h>

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

struct othm_funct *othm_funct_new(void (*function)(void))
{
	struct othm_funct *new_funct = malloc(sizeof(struct othm_funct));;

	new_funct->function = function;
	return new_funct;
}
