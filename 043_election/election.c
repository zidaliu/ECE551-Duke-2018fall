#include "election.h"

#include <stdio.h>
#include <string.h>
//include any other headers you need here...

state_t parseLine(const char * line) {
  //STEP 1: write me
  state_t line_struct;
  int lenth_colon_1 = 0;
  int lenth_colon_2 = 0;
  int lenth_colon_3 = 0;
  int i = 0, j = 0, k = 0;
  char population[50];
  char electoralVotes[20];
  char * ptr;

  while (line[lenth_colon_1] != ':') {
    line_struct.name[i] = line[lenth_colon_1];
    i++;
    lenth_colon_1++;
  }
  line_struct.name[lenth_colon_1] = '\0';
  lenth_colon_2 = lenth_colon_1 + 1;
  while (line[lenth_colon_2] != ':') {
    population[j] = line[lenth_colon_2];
    j++;
    lenth_colon_2++;
  }
  population[j] = '\0';
  lenth_colon_3 = lenth_colon_2 + 1;
  uint64_t temp_popu = strtoul(population, &ptr, 10);
  line_struct.population = temp_popu;
  while (line[lenth_colon_3] != '\0') {
    electoralVotes[k] = line[lenth_colon_3];
    k++;
    lenth_colon_3++;
  }
  electoralVotes[k] = '\0';
  unsigned temp_ele = strtoul(electoralVotes, &ptr, 10);
  line_struct.electoralVotes = temp_ele;

  return line_struct;
}

unsigned int countElectoralVotes(state_t * stateData, uint64_t * voteCounts, size_t nStates) {
  //STEP 2: write me
  unsigned int vote = 0;
  for (size_t i = 0; i < nStates; i++) {
    if (voteCounts[i] > (stateData[i].population / 2))
      vote = vote + stateData[i].electoralVotes;
  }

  return vote;
}

void printRecounts(state_t * stateData, uint64_t * voteCounts, size_t nStates) {
  //STEP 3: write me
  double lower_bound = 0;
  double upper_bound = 0;
  for (size_t i = 0; i < nStates; i++) {
    lower_bound = stateData[i].population * 0.495;
    upper_bound = stateData[i].population * 0.505;
    if (lower_bound < voteCounts[i] && voteCounts[i] < upper_bound) {
      double percentage = voteCounts[i] / (double)(stateData[i].population);
      printf("%s requires a recount (Candidate A has %.2f%% of the vote)\n",
             stateData[i].name,
             100.0 * percentage);
    }
  }
}

void printLargestWin(state_t * stateData, uint64_t * voteCounts, size_t nStates) {
  //STEP 4: write me
  double largestPercentage = 0;
  size_t largestIndex = 0;
  for (size_t i = 0; i < nStates; i++) {
    double percentage = voteCounts[i] / (double)(stateData[i].population);
    if (percentage > largestPercentage) {
      largestPercentage = percentage;
      largestIndex = i;
    }
  }
  printf("Candidate A won %s with %.2f%% of the vote\n",
         stateData[largestIndex].name,
         100.0 * largestPercentage);
}
