#include <stdio.h>
#include <Infix.h>

void main()
{
  char buff[300];
  Infix *queue;
 
  printf("Enter :");
  scanf("%[^\n]", buff);
  	
  queue = infix_postfix_conversion(buff);
  	
  printf("infix-postfix : ");
  	
  print_postfix(queue);
  	
  printf("\nresult : %d\n",infix_postfix_eval(&queue));
}
