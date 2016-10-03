// N.B. This program contains a bug, on purpose.

#include <iostream>

void screen_clear(), screen_flush();
void screen_draw(const double, const double, const char);
bool charvalid(const char);

const int maxColumn = 79;
const int minColumn =  0;
char screen[maxColumn];

void move( double& position, double& speed ) {
  position += speed;

  if (position >= maxColumn) {
    position = maxColumn;
    speed = -speed;
  } else if (position < minColumn) {
    position = minColumn;
    speed = -speed;
  } 
}

int main() {
  int timeStep = 0;
  const int stopTime = 60;
  int num_particles = 5;
  double position[5] = {0, 79, 7, 8, 10};
  double speed[5] = {6.3, -4, 3, 1, -8};
  const char symbol[5] = {'x','y','z','@','#'};
  

  while (timeStep < stopTime) {
    screen_clear();
    for(int i=0; i<num_particles; i++)
    {
      screen_draw(position[i], speed[i], symbol[i]);
      move(position[i], speed[i]);
    }
    screen_flush();
    timeStep++;
  }
}

void screen_clear() {
  for (int i = 0; i <= maxColumn; i++) {
    screen[i] = ' ';
  }  
}

void screen_draw( const double position, const double speed, const char symbol ) {
  int ipos = static_cast<int>(position);
  screen[ipos] = symbol;
  // if(speed < 0.0) {
  //   if(position < maxColumn-1 && charvalid(screen[ipos+1])) screen[ipos+1] = '=';
  //   if(position < maxColumn-2 && charvalid(screen[ipos+2])) screen[ipos+2] = '-';
  // } else {
  //   if(position > minColumn+1 && charvalid(screen[ipos-1])) screen[ipos-1] = '=';
  //   if(position > minColumn+2 && charvalid(screen[ipos-2])) screen[ipos-2] = '-';
  // }
}

void screen_flush() {
  std::cout << screen << std::endl;
}

bool charvalid( const char test ) {
  return( test == ' ' || test == '-');
}
