/* htmltophp.c
   input: file.htm
   output: file.htm.php

   scan through file.htm line by line
   encase each line in printf() and escape ""

*/

#include <stdio.h>
#include <stdlib.h>  // for system()
#include <string.h>


int main(int argc, char *argv[])
{
   int linecount = 0;
   char input_filename[100], output_filename[105];
   char in_line[200], out_line[250];    // longer to allow for printf("\n"); and escaping of ""
   char *source = in_line;
   char *target = out_line;
   FILE *ifp, *ofp;

   if (argc !=2) {
      system("cls");
      printf("\n\t\tHTML to PHP - by Andrew J Clarkin\n\n");
      printf("This tool surrounds every line on a file with printf() commands\n");
      printf("It will save as original filename.php\n");
      printf("Usage: htmltophp <filename>\n\n");
      printf("Enter filename to open: ");
      scanf("%s", input_filename);
   } else {
      sprintf(input_filename, "%s", argv[1]);
   }




   if (!(ifp = fopen(input_filename, "r"))) {
      printf("File not found\n");
   } else {
      sprintf(output_filename, "%s.php", input_filename);
      ofp = fopen(output_filename, "w");

      while (fgets(in_line, 250, ifp))
      {
         //in_line[strlen(in_line) - 1] = '\0';    // in_line has \n at end because fgets() reads that as well; this removes it

         source = in_line;
         target = out_line;
         while (*source != '\n')
         {
            if (*source == 34)    // 34 is "
            {
               *target++ = 92;      /* 92 is \ */
            }
            *target++ = *source++;
         }
         *target++ = '\0';

         fprintf(ofp, "printf(\"%s\\n\");\n", out_line);
         linecount++;
      }

      fclose(ifp);
      fclose(ofp);
      printf("%d lines converted -> %s\n", linecount, output_filename);
  }
  return 0;
}
