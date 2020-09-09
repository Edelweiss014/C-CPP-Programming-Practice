#include <stdio.h>
#include <stdlib.h>
//I've provided "min" and "max" functions in
//case they are useful to you
int min (int a, int b) {
  if (a < b) {
    return a;
  }
  return b;
}
int max (int a, int b) {
  if (a > b) {
    return a;
  }
  return b;
}

//Declare your rectangle structure here!
struct rect_t
{
    int x;
    int y;
    int width;
    int height;
};
typedef struct rect_t rectangle;




rectangle canonicalize(rectangle r) {
  //WRITE THIS FUNCTION
  if (r.height < 0) {
      r.y = r.y + r.height;
      r.height = -r.height;
  }
  if (r.width < 0) {   
      r.x = r.x + r.width;
      r.width = -r.width;
  }

  return r;
}

rectangle situation1 (rectangle r1, rectangle r2) {
  // When x1 <= x2 and y1 >= y2

  rectangle r3;
  r1 = canonicalize(r1); r2 = canonicalize(r2);
  int x1 = r1.x; int x2 = r2.x; int y1 = r1.y; int y2 = r2.y; 
  int w1 = r1.width; int w2 = r2.width; int h1 = r1.height; int h2 = r2.height; 

  r3.x = x2; r3.y = y1;
  r3.width = min(w2, w1 - (x2 - x1));
  r3.height = min(h1, h2 - (y1 - y2));

  if (r3.width < 0 || r3.height < 0) {
    r3.width = 0; r3.height = 0;
  }
  
  return r3;
}

rectangle situation2 (rectangle r1, rectangle r2) {
  // When x1 <= x2 and y1 <= y2
  
  rectangle r3;
  r1 = canonicalize(r1); r2 = canonicalize(r2);
  int x1 = r1.x; int x2 = r2.x; int y1 = r1.y; int y2 = r2.y; 
  int w1 = r1.width; int w2 = r2.width; int h1 = r1.height; int h2 = r2.height; 
  
  r3.x = x2; r3.y = y2;
  //printf("x1 = %d, x2 = %d, r3.x = %d\n", x1, x2, r3.x);
  r3.width = min(w2, w1 - (x2 - x1));
  r3.height = min(h2, h1 - (y2 - y1));

  if (r3.width < 0 || r3.height < 0) {
    r3.width = 0; r3.height = 0;
  }

  return r3;
}

rectangle intersection(rectangle r1, rectangle r2) {
  //WRITE THIS FUNCTION
  r1 = canonicalize(r1); r2 = canonicalize(r2); 
  int x1 = r1.x; int x2 = r2.x; int y1 = r1.y; int y2 = r2.y; 
  if (x1 <= x2 && y1 >= y2) {
    r1 = situation1(r1, r2);
  }
  else if (x1 >= x2 && y1 <= y2) {
    r1 = situation1(r2, r1);
  }
  else if (x1 <= x2 && y1 <= y2) {
    r1 = situation2(r1, r2);
  }
  else if (x1 >= x2 && y1 >= y2) {
    r1 = situation2(r2, r1);
  }
  else {
    r1.x = 0;
    r1.y = 0;
    r1.height = 0;
    r1.width = 0;
  }
  
  return r1;
}

//You should not need to modify any code below this line
void printRectangle(rectangle r) {
  r = canonicalize(r);
  if (r.width == 0 && r.height == 0) {
    printf("<empty>\n");
  }
  else {
    printf("(%d,%d) to (%d,%d)\n", r.x, r.y, 
	                           r.x + r.width, r.y + r.height);
  }
}

int main (void) {
  rectangle r1;
  rectangle r2;
  rectangle r3;
  rectangle r4;

  r1.x = 2;
  r1.y = 3;
  r1.width = 5;
  r1.height = 6;
  printf("r1 is ");
  printRectangle(r1);

  r2.x = 4;
  r2.y = 5;
  r2.width = -5;
  r2.height = -7;
  printf("r2 is ");
  printRectangle(r2);
  
  r3.x = -2;
  r3.y = 7;
  r3.width = 7;
  r3.height = -10;
  printf("r3 is ");
  printRectangle(r3);

  r4.x = 0;
  r4.y = 7;
  r4.width = -4;
  r4.height = 2;
  printf("r4 is ");
  printRectangle(r4);

  //test everything with r1
  rectangle i = intersection(r1,r1);
  printf("intersection(r1,r1): ");
  printRectangle(i);

  i = intersection(r1,r2);
  printf("intersection(r1,r2): ");
  printRectangle(i);
  
  i = intersection(r1,r3);
  printf("intersection(r1,r3): ");
  printRectangle(i);

  i = intersection(r1,r4);
  printf("intersection(r1,r4): ");
  printRectangle(i);

  //test everything with r2
  i = intersection(r2,r1);
  printf("intersection(r2,r1): ");
  printRectangle(i);

  i = intersection(r2,r2);
  printf("intersection(r2,r2): ");
  printRectangle(i);
  
  i = intersection(r2,r3);
  printf("intersection(r2,r3): ");
  printRectangle(i);

  i = intersection(r2,r4);
  printf("intersection(r2,r4): ");
  printRectangle(i);

  //test everything with r3
  i = intersection(r3,r1);
  printf("intersection(r3,r1): ");
  printRectangle(i);

  i = intersection(r3,r2);
  printf("intersection(r3,r2): ");
  printRectangle(i);
  
  i = intersection(r3,r3);
  printf("intersection(r3,r3): ");
  printRectangle(i);

  i = intersection(r3,r4);
  printf("intersection(r3,r4): ");
  printRectangle(i);

  //test everything with r4
  i = intersection(r4,r1);
  printf("intersection(r4,r1): ");
  printRectangle(i);

  i = intersection(r4,r2);
  printf("intersection(r4,r2): ");
  printRectangle(i);
  
  i = intersection(r4,r3);
  printf("intersection(r4,r3): ");
  printRectangle(i);

  i = intersection(r4,r4);
  printf("intersection(r4,r4): ");
  printRectangle(i);


  return EXIT_SUCCESS;

}

