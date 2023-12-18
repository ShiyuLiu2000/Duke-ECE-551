#include "outname.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Add suffix '.counts' to input files
char * computeOutputFileName(const char * inputName) {
  const char * suffix = ".counts";
  size_t len = strlen(inputName) + strlen(suffix) + 1;
  char * ans = malloc(len * sizeof(*ans));
  snprintf(ans, len, "%s%s", inputName, suffix);
  return ans;
}
