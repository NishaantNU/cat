#include <stdio.h>
#include <string.h>

int checkArgs(int *ac, char **argv, char *term, int removeTerm) {
  for (int i = 1; i < *ac; i++) {
    if ((strcmp(argv[i], term)) == 0) {
      // Term exists, remove from args if needed.
      if (removeTerm == 1) {
        for (int j = i; j < *ac - 1; j++) {
          argv[j] = argv[j + 1];
        }
        argv[*ac - 1] = NULL;
        (*ac)--;
      }
     return 0;
    }
  }
  return -1;
}

int main(int argc, char **argv) {
  int decorateEnd = 0;
  int printLineNumber=0;
  int lineNumber=1;
  FILE *fp;

  if (argc == 1) {
    char ch;
    while ((ch = fgetc(stdin)) != EOF) {
      printf("%c", ch);
    }

  } else {
    if (argc > 1) {
      if (checkArgs(&argc, argv, "-n", 1) == 0) {
        printLineNumber=1;
      }
      if (checkArgs(&argc, argv, "-e", 1) == 0) {
        decorateEnd=1;
      }

      for (int i = 1; i < argc; i++) {
        if (checkArgs(&argc, argv, "--h", 0) == 0) {
          const char *help =
              "Nishaant's cat implementation!\n"
              "Usage: cat [OPTION]... [FILE]...\n"
              "ConCATenate FILE(s) to the standard output.\n"
              "\nWith no FILE, or when file is -, read standard input.\n"
              "\nOptions:\n"
              "\t-n: Number each line\n"
              "\t-e: Append end of each line with $";

          printf("%s\n", help);
          break;
        }
        else if ((strcmp(argv[i], "-")) == 0) {
	  int isNewLine=1;
          char ch;
          while ((ch = fgetc(stdin)) != EOF) {
            if (isNewLine && printLineNumber) {
              printf("%d ", lineNumber);
              isNewLine = 0;
            }
            if (ch == '\n') {
              if (decorateEnd == 1) {
                printf("$");
              }
              lineNumber += 1;
             isNewLine=1;
            }
            printf("%c", ch);
          }
        } else {
	  //      printf("Trying to open: %s\n", argv[i]);
	  fp = fopen(argv[i], "r");
	  if (fp == NULL) {
            printf("%s: %s: No such file or dir.\n", argv[0], argv[i]);
            continue;
          }
          int isNewLine=1;
	  char ch;
          while ((ch = fgetc(fp)) != EOF) {
            if (isNewLine && printLineNumber) {
              printf("%d ", lineNumber);
              isNewLine=0;
            }
            if (ch == '\n') {
              if (decorateEnd == 1) {
                printf("$");
              }
              lineNumber += 1;
              isNewLine = 1;
            }
            printf("%c", ch);
	  }
	  fclose(fp);
	  //      printf("\n");
        }
      }
    }
  }
  return 0;
}
