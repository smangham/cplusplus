// N.B. This program contains a bug, on purpose.

#include <iostream>

struct Particle {
  float pos, vel;
  char sym;
};

void screen_clear(char[]), screen_print(char[]);
void screen_draw(Particle& p, char[]);
bool charvalid(const char);

const char tail_short = ' ';
const char tail_long = '~';
const int maxColumn = 79;
const int minColumn =  0;

char screen[maxColumn];


void move( Particle& p ) {
  p.pos += p.vel;

  if (p.pos >= maxColumn) {
    p.pos = maxColumn;
    p.vel *= -1;
  } else if (p.pos <= minColumn) {
    p.pos = minColumn;
    p.vel *= -1;
  } 
}

int main() {
  int timeStep = 0;
  const int stopTime = 60;
  const int num_particles = 3;
  char* screen = new char[maxColumn+1];

  Particle* p = new Particle[num_particles];
  p[1].vel = 6.3;   p[1].pos = 0;   p[1].sym = 'x';
  p[2].vel = -4.0;  p[2].pos = 79;  p[2].sym = '+';
  p[3].vel = 3.0;   p[3].pos = 50;  p[3].sym = 'o';

  while (timeStep < stopTime) {
    screen_clear(screen);
    for(int i=0; i<num_particles; i++)
    {
      screen_draw(p[i], screen);
      move(p[i]);
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

void screen_draw( Particle& p, char screen[])
{
  int ipos = static_cast<int>(p.pos);
  screen[ipos] = p.sym;
  if(p.vel < 0.0) {
    if(ipos < maxColumn-1 && charvalid(screen[ipos+1])) screen[ipos+1] = tail_long;
    if(ipos < maxColumn-2 && charvalid(screen[ipos+2])) screen[ipos+2] = tail_short;
  } else {
    if(ipos > minColumn+1 && charvalid(screen[ipos-1])) screen[ipos-1] = tail_long;
    if(ipos > minColumn+2 && charvalid(screen[ipos-2])) screen[ipos-2] = tail_short;
  }
}

void screen_print( char screen[] ) {
  for(int i=0; i<=maxColumn; i++)
  {
    std::cout << screen[i];
  }
  std::cout << std::endl;
}

bool charvalid( const char test ) {
  return( test == ' ' || test == '-');
}
