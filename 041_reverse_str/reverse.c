#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void swap(char * a, char * b) {
  char temp;
  temp = *b;
  *b = *a;
  *a = temp;
}

void reverse(char * str) {
  //WRITE ME!

  if (!str) {  //Null Pointer
    return;
  }

  size_t n = strlen(str);
  if (n == 0) {
    return;
  }
  if (n % 2 == 0) {
    for (int i = 0; i <= (n - 2) / 2; i++) {
      swap(str + i, str + n - 1 - i);
    }
  }
  else {
    for (int i = 0; i <= (n - 1) / 2 - 1; i++) {
      swap(&(str[i]), &(str[n - 1 - i]));
    }
  }
}

int main(void) {
  char str0[] = "";
  char str1[] = "123";
  char str2[] = "abcd";
  char str3[] = "Captain's log, Stardate 42523.7";
  char str4[] = "Hello, my name is Inigo Montoya.";
  char str5[] = "You can be my wingman anyday!";
  char str6[] =
      "Executor Selendis! Unleash the full power of your forces! There may be no tomorrow!";
  char * array[] = {str0, str1, str2, str3, str4, str5, str6};
  for (int i = 0; i < 7; i++) {
    reverse(array[i]);
    printf("%s\n", array[i]);
  }
  return EXIT_SUCCESS;
}
