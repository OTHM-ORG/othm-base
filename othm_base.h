#ifndef OTHM_BASE_H
#define OTHM_BASE_H

#include "othm_cpp.h"
#include <stdarg.h>


#define OTHM_TYPE(TYPED) ((struct othm_typed *) TYPED)

struct othm_typed {
	void *type;
};

/* The C standard allows function pointers to be
   cast to function pointers of different types,
   but not to a void pointer. By rapping a function
   pointer in a structure the pointer can be moved
   because it is data (data structures can have function
   pointers, nothing special)*/
struct othm_funct {
	/* some generic function, it doesn't matter
	   since it's type will be set at some other
	   time so I made it a useless function. */
	void (*function)(void);
	char *name;
};
/* These are "low level" parts of othm and thus should
   Not have a type since it would take up extra data */
struct othm_request {
	void *key_type;
	int (*check_key)(void *storage, void *data);
	int data_size;
	void *data;
};

struct othm_pair {
	void *first;
	void *second;
};

struct othm_triple {
	void *first;
	void *second;
	void *third;
};

struct othm_quadruple {
	void *first;
	void *second;
	void *third;
	void *fourth;
};

struct othm_quintuple {
	void *first;
	void *second;
	void *third;
	void *fourth;
	void *fifth;
};

struct othm_sextuple {
	void *first;
	void *second;
	void *third;
	void *fourth;
	void *fifth;
	void *sixth;
};

struct othm_septuple {
	void *first;
	void *second;
	void *third;
	void *fourth;
	void *fifth;
	void *sixth;
	void *seventh;
};

struct othm_octuple {
	void *first;
	void *second;
	void *third;
	void *fourth;
	void *fifth;
	void *sixth;
	void *seventh;
	void *eighth;
};


struct othm_list {
	void *here;
	struct othm_list *next;
};

struct othm_stack {
	struct othm_list *top;
};

#define OTHMREQUEST(REQUEST) ((struct othm_request *) (REQUEST))
#define OTHM_FUNCT(ANYFUNCTION, NAME) (othm_funct_new	\
				       ((void (*) (void))(ANYFUNCTION), \
					NAME))

extern const struct othm_typed OTHM_NULL_TYPED;
extern const struct othm_pair OTHM_NULL_PAIR;

struct othm_typed othm_typed_new(void *type);

struct othm_request *othm_request_new(int (*check_key)(void *storage, void *data),
				      void *key_type, int data_size, void *data);

struct othm_list *othm_list_direct(struct othm_list *(*list_gen)(void),
				   void *first, ...);

struct othm_pair othm_pair_new(void *first, void *second);

struct othm_stack *othm_stack_new(struct othm_stack *(*gen)(void));

void othm_stack_push(struct othm_stack *stack, void *thing);

void *othm_stack_pop(struct othm_stack *stack);

/*                       NOTE:IMPORTANT!
   If you are doing this it should be to pass a function around,
   be very careful though because it can be nearly impossible to
   debug if you mess something up!! */
struct othm_funct *othm_funct_new(void (*function)(void),
				  char *name);

char *othm_load_file(char *file_name);

#endif
