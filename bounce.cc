// N.B. This program contains a bug, on purpose.

#include <iostream>

void screen_clear(char[]), screen_print(char[]);
void screen_draw(const double, const double, const char, char[]);
bool charvalid(const char);

const char tail_short = ' ';
const char tail_long = '~';
const int maxColumn = 79;
const int minColumn =  0;
char screen[maxColumn];

void move( double& position, double& speed ) {
  position += speed;

  if (position >= maxColumn) {
    position = maxColumn;
    speed = -speed;
  } else if (position <= minColumn) {
    position = minColumn;
    speed = -speed;
  } 
}

int main() {
  int timeStep = 0;
  const int stopTime = 60;
  const int num_particles = 5;
  double position[num_particles] =    {0,   79,   7,    50,   60};
  double speed[num_particles] =       {6.3, -4,   3,    1,    -5};
  const char symbol[num_particles] =  {'x', '+',  'o',  '@',  '#'};
  char* screen = new char[maxColumn+1];

  while (timeStep < stopTime) {
    screen_clear(screen);
    for(int i=0; i<num_particles; i++)
    {
      screen_draw(position[i], speed[i], symbol[i], screen);
      move(position[i], speed[i]);
    }
    screen_print(screen);
    timeStep++;
  }
  delete [] screen;
}

void screen_clear( char screen[] ) {
  for (int i = 0; i <= maxColumn; i++) {
    screen[i] = ' ';
  }  
}

void screen_draw( 
    const double position, const double speed, 
    const char symbol, char screen[])
{
  int ipos = static_cast<int>(position);
  screen[ipos] = symbol;
  if(speed < 0.0) {
    if(position < maxColumn-1 && charvalid(screen[ipos+1])) screen[ipos+1] = tail_long;
    if(position < maxColumn-2 && charvalid(screen[ipos+2])) screen[ipos+2] = tail_short;
  } else {
    if(position > minColumn+1 && charvalid(screen[ipos-1])) screen[ipos-1] = tail_long;
    if(position > minColumn+2 && charvalid(screen[ipos-2])) screen[ipos-2] = tail_short;
  }
}

void screen_print( char screen[80] ) {
  for(int i=0; i<=maxColumn; i++)
  {
    std::cout << screen[i];
  }
  std::cout << std::endl;
}

bool charvalid( const char test ) {
  return( test == ' ' || test == '-');
}
