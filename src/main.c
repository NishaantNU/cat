#include <stdio.h>
#include <stdbool.h>
#include <string.h>

// For when arguments are used
bool replaceTab = false;
bool decorateEnd = false;
bool printLineNumber = false;
bool isNewLine = false;

// Global line number count
int lineNumber = 1;

bool checkArgs(int *ac, char **argv, char *term, int removeTerm) {
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
      return true;
    }
  }
  return false;
}

void printChar(char ch) {
  if (isNewLine && printLineNumber) {
    printf("%d ", lineNumber);
    isNewLine = false;
  }
  if (ch == '\n') {
    if (decorateEnd == 1) {
      printf("$");
    }
    lineNumber += 1;
    isNewLine = true;
  } else if (ch == '\t' && replaceTab) {
    printf("^I");
    return;
  }
  printf("%c", ch);
}

int main(int argc, char **argv) {

  FILE *fp;

  if (argc == 1) {
    char ch;
    while ((ch = fgetc(stdin)) != EOF) {
      printf("%c", ch);
    }

  } else {
    if (argc > 1) {
      if (checkArgs(&argc, argv, "-n", 1)) {
        printLineNumber = true;
      }

      if (checkArgs(&argc, argv, "-e", 1)) {
        decorateEnd = true;
      }

      if (checkArgs(&argc, argv, "-t", 1)) {
        replaceTab = true;
      }

      for (int i = 1; i < argc; i++) {
        if (checkArgs(&argc, argv, "--h", 0)) {
          const char *help =
            "Nishaant's cat implementation!\n"
            "Usage: cat [OPTION]... [FILE]...\n"
            "ConCATenate FILE(s) to the standard output.\n"
            "\nWith no FILE, or when file is -, read standard input.\n"
            "\nOptions:\n"
            "\t-n: Number each line\n"
            "\t-t: Replace TAB with ^I\n"
            "\t-e: Append end of each line with $";

          printf("%s\n", help);
          break;
        }
        else if ((strcmp(argv[i], "-")) == 0) {
          isNewLine = true;
          char ch;
          while ((ch = fgetc(stdin)) != EOF) {
            printChar(ch);
          }
        } else {
	  fp = fopen(argv[i], "r");
	  if (fp == NULL) {
            printf("%s: %s: No such file or dir.\n", argv[0], argv[i]);
            continue;
          }
          isNewLine = true;
	  char ch;
          while ((ch = fgetc(fp)) != EOF) {
            printChar(ch);
          }
	  fclose(fp);
        }
      }
    }
  }
  return 0;
}
