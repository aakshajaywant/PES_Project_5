/******************************************************************************
 *  					PES PROJECT 5
 *   AAKSHA JAYWANT (AAJA1276) & RUCHA BORWANKAR (RUBO1268)
 *
 * 				Cross Platform IDE: MCUXpresso IDE v11
 * 					Cross-Compiler: ARM GCC
 * 						application.c
 ********************************************************************************/
/**********************************REFERENCE*********************************
https://www.programmingsimplified.com/c-program-find-characters-frequency
*****************************************************************************/

#include "application.h"


#if MODE == APPLICATION_MODE

/***************************APPLICATION MODE FUNCTION**********************
 In this function we take a string from the user and when ENTER key is pressed
 we get desired report of number of entries of characters from  A to Z,a to z
 or 0-9 made to the system.
*****************************************************************************/

void app_mode(char string[])
{

   int a = 0, count[26] = {0},count2[26] = {0},count3[26] = {0}, x;

   while (string[a] != '\0')		//terminating condition
   {

      if (string[a] >= 'a' && string[a] <= 'z')
      {
         x = string[a] - 'a';
         count[x]++;
      }
      else if (string[a] >= 'A' && string[a] <= 'Z')
      {
         int y = string[a] - 'A';
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
	   if(count[a] != 0)
	   {
         printf("\n \r %c -> %d ", a + 'a', count[a]);
	   }
   }
   for (int d = 0; d < 26; d++)
   {
	   if(count2[d] != 0)
	   {
         printf("\n \r %c -> %d ", d + 'A', count2[d]);
	   }
   }
   for (int c = 0; c < 10; c++)
   {
	   if(count3[c] != 0)
	   {
         printf("\n \r %c -> %d ", c + '0', count3[c]);
	   }
   }

}

#endif
