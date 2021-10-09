// convert_to_lf.c
// scan a file and convert CR to LF

#include <stdio.h>
#include <stdlib.h>		// for system()
#define TEMPFILE "temp_delete-me.txt"

int main(void)
{
	char filename[100], command_string[100];
	FILE *ifp, *ofp;
	char readchar;
	int instance_count = 0;

	system("cls");
	printf("\n\t\tConvert To LF - by Andrew J Clarkin\n\n");
	printf("This tool scans a file for carriage returns and replaces them with line feeds.\n");
	printf("It will replace the original file with the processed version\n\n");
	printf("Enter filename to open: ");
	scanf("%s", filename);

	if (!(ifp = fopen(filename, "r"))) {
		printf("File not found\n");
	} else {
		ofp = fopen(TEMPFILE, "w");
		while ((readchar = fgetc(ifp)) != EOF) {
			if (readchar == '\r') {
				instance_count++;
				readchar = fgetc(ifp);
				if (readchar == '\n') {
					fputc(readchar, ofp);
				} else {
					fputc('\n', ofp);
					fputc(readchar, ofp);
				}
			} else {
				fputc(readchar, ofp);
			}
		}
		fclose(ofp);
		fclose(ifp);

		sprintf(command_string, "copy %s \"%s\" >NUL", TEMPFILE, filename);
		system(command_string);

		sprintf(command_string, "del %s", TEMPFILE);
		system(command_string);

		printf("Operation complete: %d carrriage returns removed.\n", instance_count);
	}
	return 0;
}

/*
	Prompts for a file. If it opens it then reads character at a time and copies to a temp file.
	If a CR is encountered it is not written to the temp file. If the next character is a LF then
	that is written. If not LF then one is written, followed by the next character which is already
	in a variable.
*/