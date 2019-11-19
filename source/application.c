#include "application.h"


#if MODE == APPLICATION_MODE

void application_mode(char string[])
{
   //char string[100];
   int a = 0,c=0, count[26] = {0},count2[26] = {0},count3[26] = {0}, x;

   while (string[a] != '\0')
   {
   /** Considering characters from 'a' to 'z' only and ignoring others. */

      if (string[a] >= 'a' && string[a] <= 'z')
      {
         x = string[a] - 'a';
         count[x]++;
      }
      else if (string[a] >= 'A' && string[a] <= 'Z')
      {
         int y = string[a] - 'a';
         count2[y]++;
      }
      else if (string[a] >= '0' && string[a] <= '9')
      {
         int z = string[a] - '0';
         count3[z]++;
      }

      a++;
   }

   for (a = 0; a < 26; a++)
   {
         printf("\n \r %c occurs %d times in the string", a + 'a', count[a]);
   }
   for (int d = 0; d < 26; d++)
   {
         printf("\n \r %c occurs %d times in the string", d + 'A', count2[d]);
   }
   for (int c = 0; c < 10; c++)
   {
         printf("\n \r %c occurs %d times in the string", c + '0', count3[c]);
   }
   return 0;
}

#endif
