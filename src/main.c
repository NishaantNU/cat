#include <stdio.h>
#include <string.h>

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
        if ((strcmp(argv[i], "-")) == 0) {
          char ch;
	  while ((ch = fgetc(stdin)) != EOF) {
	    printf("%c", ch);
	  }
        } else {
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
