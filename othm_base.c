#include "othm_base.h"
#include <stdio.h>
#include <stdlib.h>


const struct othm_typed OTHM_NULL_TYPED = {
	.type = NULL
};

const struct othm_pair OTHM_NULL_PAIR = {
	.first  = NULL,
	.second = NULL
};


struct othm_typed othm_typed_new(void *type)
{
	struct othm_typed new_type;
	new_type.type = type;

	return new_type;
}

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

struct othm_triple othm_triple_new(void *first, void *second,
				   void *third)
{
	struct othm_triple triple;

	triple.first = first;
	triple.second = second;
	triple.third = third;
	return triple;
}

struct othm_quadruple othm_quadruple_new(void *first, void *second,
					 void *third, void *fourth)
{
	struct othm_quadruple quadruple;

	quadruple.first = first;
	quadruple.second = second;
	quadruple.third = third;
	quadruple.fourth = fourth;
	return quadruple;
}

struct othm_quintuple othm_quintuple_new(void *first, void *second,
					 void *third, void *fourth,
					 void *fifth)
{
	struct othm_quintuple quintuple;

	quintuple.first = first;
	quintuple.second = second;
	quintuple.third = third;
	quintuple.fourth = fourth;
	quintuple.fifth = fifth;
	return quintuple;
}

struct othm_sextuple othm_sextuple_new(void *first, void *second,
				       void *third, void *fourth,
				       void *fifth, void *sixth)
{
	struct othm_sextuple sextuple;

	sextuple.first = first;
	sextuple.second = second;
	sextuple.third = third;
	sextuple.fourth = fourth;
	sextuple.fifth = fifth;
	sextuple.sixth = sixth;
	return sextuple;
}

struct othm_septuple othm_septuple_new(void *first, void *second,
				       void *third, void *fourth,
				       void *fifth, void *sixth,
				       void *seventh)
{
	struct othm_septuple septuple;

	septuple.first = first;
	septuple.second = second;
	septuple.third = third;
	septuple.fourth = fourth;
	septuple.fifth = fifth;
	septuple.sixth = sixth;
	septuple.seventh = seventh;
	return septuple;
}

struct othm_octuple othm_octuple_new(void *first, void *second,
				     void *third, void *fourth,
				     void *fifth, void *sixth,
				     void *seventh, void *eighth)
{
	struct othm_octuple octuple;

	octuple.first = first;
	octuple.second = second;
	octuple.third = third;
	octuple.fourth = fourth;
	octuple.fifth = fifth;
	octuple.sixth = sixth;
	octuple.seventh = seventh;
	octuple.eighth = eighth;
	return octuple;
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

struct othm_list *othm_list_new(void *here)
{
	struct othm_list *new_list;

	new_list = malloc(sizeof(struct othm_list));
	new_list->here = here;
	new_list->next = NULL;

	return new_list;
}

struct othm_list *othm_list_direct(struct othm_list *(*list_gen)(void),
				   void *first, ...)
{
	va_list argp;
	void *arg;
	struct othm_list *head;
	struct othm_list *tail;

	if (first == NULL)
		return NULL;

	arg = first;
	head = list_gen();
	tail = head;
	va_start(argp, first);
	do {
		tail->here = arg;
	} while ((arg = va_arg(argp, void *))
		 ? (tail->next = list_gen(),
		    tail = tail->next, 1)
		 : 0);

	/* This while is used to only allocate another part of the list
	   if the list is not null! it does this using the comma operator
	   and the conditional operator */

	tail->next = NULL;
	va_end(argp);

	return head;
}

struct othm_dlist *othm_dlist_direct(struct othm_dlist *(*dlist_gen)(void),
				     void *first, ...)
{
	va_list argp;
	void *arg;
	struct othm_dlist *head;
	struct othm_dlist *tail;

	if (first == NULL)
		return NULL;

	arg = first;
	head = dlist_gen();
	head->prev = NULL;
	tail = head;
	va_start(argp, first);
	do {
		tail->here = arg;
	} while ((arg = va_arg(argp, void *))
		 ? (tail->next = dlist_gen(),
		    tail->next->prev = tail,
		    tail = tail->next, 1)
		 : 0);

	/* This while is used to only allocate another part of the list
	   if the list is not null! it does this using the comma operator
	   and the conditional operator */

	tail->next = NULL;
	va_end(argp);

	return head;
}

void othm_list_append(struct othm_list *list,
		      void *end)
{
	struct othm_list *list_ptr;

	for(list_ptr = list; list_ptr->next != NULL;
	    list_ptr = list_ptr->next);
	list_ptr->next = othm_list_new(end);
}

void *othm_list_car(struct othm_list *list)
{
	return list->here;
}

struct othm_list *othm_list_cdr(struct othm_list *list)
{
	return list->next;
}

struct othm_stack *othm_stack_new(struct othm_stack *(*gen)(void))
{
	struct othm_stack *stack;

	stack = gen();
	stack->top = NULL;

	return stack;
}

void othm_stack_push(struct othm_stack *stack,
		     void *thing)
{
	struct othm_list *list;

	list = malloc(sizeof(struct othm_list));;
	list->here = thing;
	list->next = stack->top;
	stack->top = list;
}

void *othm_stack_pop(struct othm_stack *stack)
{
	struct othm_list *list;
	void *thing;

	list = stack->top;
	thing = list->here;
	stack->top = list->next;

	free(list);

	return thing;
}
