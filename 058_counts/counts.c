#include "counts.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
counts_t * createCounts(void) {
  //WRITE ME
  counts_t * countAll = malloc(sizeof(*countAll));
  countAll->name_list = NULL;
  countAll->len = 0;
  countAll->unknown = 0;
  return countAll;
}

void addCount(counts_t * c, const char * name) {
  //WRITE ME
  size_t i;
  int flag = 0;  //decide whether find it in original array
  if (name == NULL) {
    c->unknown++;
    return;
  }
  for (i = 0; i < c->len; i++) {
    printf("name = %s\n", name);
    if (strcmp(c->name_list[i].name, name) == 0) {
      c->name_list[i].number++;
      flag = 1;
      break;
    }
  }
  if (flag == 0) {
    c->name_list = realloc(c->name_list, (c->len + 1) * sizeof(c->name_list[0]));
    c->len++;
    c->name_list[i].name = strdup(name);
    c->name_list[i].number = 1;
  }
}
void printCounts(counts_t * c, FILE * outFile) {
  //WRITE ME
  size_t i;
  one_count_t * p;

  for (i = 0; i < c->len; i++) {
    p = &c->name_list[i];
    fprintf(outFile, "%s: %d\n", p->name, p->number);
  }
  if (c->unknown > 0) {
    fprintf(outFile, "<unknown> : %d\n", c->unknown);
  }
}

void freeCounts(counts_t * c) {
  //WRITE ME
  size_t i;
  one_count_t * p;

  for (i = 0; i < c->len; i++) {
    p = &c->name_list[i];
    free(p->name);
  }
  free(c->name_list);
  free(c);
}
