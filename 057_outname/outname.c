#include "outname.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * makeFileName(char * file);

char * computeOutputFileName(const char * inputName) {
  //WRITE ME
  const char * frame = ".counts";
  unsigned len = strlen(inputName) + strlen(frame) + 1;
  char * ans = malloc(len * sizeof(*ans));
  snprintf(ans, len, "%s%s", inputName, frame);
  return ans;
}
