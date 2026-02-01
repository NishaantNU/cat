#include <stdio.h>
#include <string.h>

int checkArgs(int ac, char **argv, char *term) {
  for (int i = 1; i < ac; i++) {
    if((strcmp(argv[i], term)) == 0) return 0;
  }
  return -1;
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
      for (int i = 1; i < argc; i++) {
        if (checkArgs(argc, argv, "--h") == 0) {
          const char *help = "Nishaant's cat implementation!\n"
                             "Usage: cat [OPTION]... [FILE]...\n"
                             "ConCATenate FILE(s) to the standard output.\n"
			     "\nWith no FILE, or when file is -, read standard input.\n";

          printf("%s\n", help);
          break;
        }
        else if ((strcmp(argv[i], "-")) == 0) {
          char ch;
	  while ((ch = fgetc(stdin)) != EOF) {
	    printf("%c", ch);
          }
        } else if ((strcmp(argv[i], "--h")) == 0) {
          const char *help = "Nishaant's cat implementation!\n"
                             "Usage: cat [OPTION]... [FILE]...\n"
                             "ConCATenate FILE(s) to the standard output.\n"
			     "\nWith no FILE, or when file is -, read standard input.\n";

	  printf("%s", help);
        }
        else {
	  //      printf("Trying to open: %s\n", argv[i]);
	  fp = fopen(argv[i], "r");
	  if (fp == NULL) {
            printf("%s: %s: No such file or dir.\n", argv[0], argv[i]);
            continue;
	  }
	  char ch;
	  while ((ch = fgetc(fp)) != EOF) {
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
