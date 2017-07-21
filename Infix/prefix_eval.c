#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Infix.h>


/* get stack operation type */
int stack_op_type_pre(Infix *stack, char op)
{
  /* bracket close */
  if (op == '(') 
	return 3;
  /* empty stack */
  if (stack == NULL || op == ')')
	return 1;

  /* other operators */
  switch (stack->op)
  {
	case '+':
	case '-':
	  if (op == '+' || op == '-')
		return 2;
	case ')':
	  return 1;
	case '*':
	case '/':
	  if (op == '+' || op == '-')
		return 2;
	  return 1;
	default:
	  return 0;
  }
}

/* process operaotrs  */
int process_op_pre(Infix **queue, Infix **stack, char op)
{
  while (1)
  {
	/* get operation type  and process */
	switch (stack_op_type_pre(*stack, op))
	{
	  case 0:
		/* error */
		return 0;
	  case 1:
		/* push to stack */
		if (!infix_push(stack, create_infix(op, 1)))
		  return 0;
		return 1;
	  case 2:
		/* pop from stack and move to queue */
		if (!infix_push(queue, infix_pop(stack)))
		  return 0;
		continue;
		break;
	  case 3:
		/* pop from stack and move to queue till '(' */
		while (*stack != NULL && (*stack)->op != ')')
		  if (!infix_push(queue, infix_pop(stack)))
			return 0;
		if (*stack == NULL)
		  return 0;
		free(infix_pop(stack));
		return 1;
	}
  }
}

/* Infix to prefix conversion */
Infix *infix_prefix_conversion(Infix *infix)
{
  Infix *queue = NULL, *stack = NULL;

  /* while end of list */
  while (infix != NULL)
  {
	if (infix->cflag)
	{
	  /* operator */
	  if (!process_op_pre(&queue, &stack, infix->op))
  		return NULL;
	}  
	else
	{
	  /* variable */
	  if (!infix_push(&queue, create_infix(infix->data, 0)))
		return NULL;
	}
	infix = infix->link;
  }

  /* remaining var */
  while (stack != NULL)
	if (!infix_push(&queue, infix_pop(&stack)))
	  return NULL;

  return queue;
}

/* str to infix */
Infix *str_2_infix(char *str)
{
  Infix *infix = NULL;
  int buff = 0, oflag = 0, nflag = 1, bflag = 0, sflag = 0; // flags 
  /* process expression one char at a time */
  while (*str != '\0')
  {
	switch (*str)
	{
	  case ' ':
	  	/* remove spaces */
		sflag = 1;
		str++;
		continue;
	  case '0' ... '9':
		/* numbers */
		if (sflag && oflag)
		  return NULL;
		buff = buff * 10 + (*str - '0');
		oflag = 1;
		sflag = 0;
		str++;
		continue;
		/* operators */
	  case '-':
		if (!oflag)	
		{
		  /* negitive number */
		  buff = -buff;
		  if (nflag == -1)
			return NULL;
		  nflag = -1;
		  str++;
		  continue;
		}
	  case '+':
	  case '*':
	  case '/':
	  case ')':
		/* process operators */
		sflag = 0;
		if (oflag)
		{
		  if (!bflag)
		  {
		  	buff *=  nflag;
		  	nflag = 1;
		  	if (!infix_push(&infix, create_infix(buff, 0)))
			  return NULL;
		  }
		  else
			bflag = 0;	
		  if (!infix_push(&infix, create_infix(*str, 1)))
			  return NULL;
		  buff = 0;
		  if (*str != ')')
		  	oflag = 0;
		  else
			bflag = 1;
		}
		else
		  return NULL;
		str++;
		continue;
		break;
	  case '(':
		sflag = 0;
		  if (!infix_push(&infix, create_infix(*str, 1)))
			  return NULL;
		oflag = 1;
		str++;
		continue;
		break;
	  default:
		return NULL;
	}
  }
  if (oflag && !bflag)
  {
	buff *=  nflag;
	if (!infix_push(&infix, create_infix(buff, 0)))
	  return NULL;		  
  }
  else if (!oflag)
	return NULL;

  /* empty stack */
  return infix;
}


/* print prefix */
void print_prefix(Infix *queue)
{
  /* print queue */
  while (queue != NULL)
  {
	if (queue->cflag)
	  printf("%c ", queue->op);
	else
	  printf("%d ", queue->data);
	queue = queue->link;
  }
  printf("\n");
}

/* prefix eval */
int infix_prefix_eval(Infix **queue)
{
  Infix *stack = NULL, *tmp, *node;
  int buf;
  if (*queue == NULL)
  {
	printf("Err\n");
	return 0;
  }
  /* till queue is not empty */
  while (*queue != NULL)
  {
	/* de queue node */
	node = infix_dequeue(queue);
	if (node->cflag)
	{
	  /* operator */
	  tmp = infix_pop(&stack);
	  /* do required operation */
	  switch (node->op)
	  {
		case '+':
		  tmp->data = tmp->data	+ infix_pop(&stack)->data;
		  if (!infix_push(&stack, tmp))
	  		return 0;
		  continue;
		case '-':
		  tmp->data = tmp->data - infix_pop(&stack)->data;
		  if (!infix_push(&stack, tmp))
	  		return 0;
		  continue;
		case '*':
		  tmp->data = tmp->data * infix_pop(&stack)->data;
		  if (!infix_push(&stack, tmp))
	  		return 0;
		  continue;
		case '/':
		  if ((buf = infix_pop(&stack)->data) == 0)
		  {
			printf("div by 0 err\n");
			return 0;
		  }
		  tmp->data = tmp->data / buf;
		  if (!infix_push(&stack, tmp))
	  		return 0;
		  continue;
	  }
	}
	else
	  /* data */
	if (!infix_push(&stack, node))
	  return 0;
  }
  return stack->data;
}
