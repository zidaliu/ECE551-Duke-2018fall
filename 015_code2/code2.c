int printTriangle(int size) {
  int starCount = 0;  //start with starCount being 0

  for (int i = 0; i < size; i++) {  //count from 0 (inclusive) to size (exclusive),
    for (int j = 0; j <= i; j++) {  //count from 0 (inclusive) to i (inclusive),
      printf("*");                  //print a "*"
      starCount++;
    }  //increment starCount
    printf("\n");
  }
  //when you finish counting on j,

  //print a newline ("\n")

  //when you finish counting on i,

  return starCount;  //your answer is starCount
}

int main(void) {
  int numStars;
  printf("Here is a triangle with height 4\n");
  numStars = printTriangle(4);
  printf("That triangle had %d total stars\n", numStars);
  printf("Here is a triangle with height 7\n");
  numStars = printTriangle(7);
  printf("That triangle had %d total stars\n",
         numStars);  //now print "Here is a triangle with height 7\n"

  //then call printTriangle, passing in 7, and assign the result to
  //numStars

  //finally, print "That triangle had %d total stars\n", such that
  //the %d prints the value of numStars

  return 0;
}
