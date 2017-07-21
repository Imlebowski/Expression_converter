#include <stdio.h>
#include <Infix.h>

void main()
{
  char buff[300];
  Infix *queue;
 
  /* read expresion*/
  printf("Enter :");
  scanf("%[^\n]", buff);
  	
  /* get prefix */
  queue = infix_prefix_conversion(str_2_infix(buff));
  	
  printf("prefix : ");
  print_prefix(queue);

  /* evaluate */
  printf("\nresult : %d\n",infix_prefix_eval(&queue));
}
