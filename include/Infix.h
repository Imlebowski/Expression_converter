
#ifndef INFIX
#define INFIX

#pragma pack(1)

typedef struct In_Eval Infix;

/* singly linked list */
struct In_Eval
{
  struct In_Eval *link;
  union
  {
  	int data;
  	char op;
  };
  unsigned int cflag;
};

/* create node */
Infix *create_infix(int data, int cflag);

/* push and en-queue */
int infix_push(Infix **head, Infix *node);

/* pop */
Infix *infix_pop(Infix **head);

/* de-queue */
Infix *infix_dequeue(Infix **head);

/* postfix eval */
int infix_postfix_eval(Infix **queue);

/* Infix to postfix conversion */
Infix *infix_postfix_conversion(char *str);

/* print postfix */
void print_postfix(Infix *queue);

/* Infix to postfix conversion */
Infix *infix_prefix_conversion(Infix *infix);

/* str to infix */
Infix *str_2_infix(char *str);

/* print postfix */
void print_prefix(Infix *queue);

/* prefix eval */
int infix_prefix_eval(Infix **queue);

#endif
