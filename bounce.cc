// N.B. This program contains a bug, on purpose.

#include <iostream>

struct Particle {
  float pos, vel;
  char sym;
};

void particle_init( Particle *const, const float, const float, const char);
void screen_clear(char *const), screen_print(const char *const);
void screen_draw(const Particle *const, char *const);
bool charvalid(const char);

const char tail_short = ' ';
const char tail_long = '~';
const int maxColumn = 79;
const int minColumn =  0;

void move( Particle *const p ) {
  p->pos += p->vel;

  if (p->pos >= maxColumn) {
    p->pos = maxColumn;
    p->vel *= -1.0;
  } else if (p->pos <= minColumn) {
    p->pos = minColumn;
    p->vel *= -1.0;
  } 
}

int main() {
  int timeStep = 0;
  const int stopTime = 60;
  const int num_particles = 3;
  char* screen = new char[maxColumn+1];
  Particle *p = new Particle[3];
  particle_init(&p[0],  0,   6.3, 'x');
  particle_init(&p[1], 79,  -4.4, 'o');
  particle_init(&p[2], 50,   3.0, '+');

  while (timeStep < stopTime) {
    screen_clear(screen);
    for(int i=0; i<num_particles; i++)
    {
      screen_draw(&p[i], screen);
      move(&p[i]);
    }
    screen_print(screen);
    timeStep++;
  }
  delete [] screen;
}

void screen_clear( char *const screen ) {
  for (int i = 0; i <= maxColumn; i++) {
    screen[i] = ' ';
  }  
}

void screen_draw( const Particle *const p, char *const screen )
{
  int ipos = static_cast<int>(p->pos);
  screen[ipos] = p->sym;
  if(p->vel < 0.0) {
    if(ipos < maxColumn-1 && charvalid(screen[ipos+1])) screen[ipos+1] = tail_long;
    if(ipos < maxColumn-2 && charvalid(screen[ipos+2])) screen[ipos+2] = tail_short;
  } else {
    if(ipos > minColumn+1 && charvalid(screen[ipos-1])) screen[ipos-1] = tail_long;
    if(ipos > minColumn+2 && charvalid(screen[ipos-2])) screen[ipos-2] = tail_short;
  }
}

void particle_init( Particle *const p, const float position, const float velocity, const char symbol )
{
  p->pos = position;
  p->vel = velocity;
  p->sym = symbol;
}

void screen_print( char const *const screen ) {
  for(int i=0; i<=maxColumn; i++)
  {
    std::cout << screen[i];
  }
  std::cout << std::endl;
}

bool charvalid( const char test ) {
  return( test == ' ' || test == '-');
}
