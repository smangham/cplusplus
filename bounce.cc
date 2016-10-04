// N.B. This program contains a bug, on purpose.
#include <iostream>

void screen_clear(char *const);
void screen_print(const char *const);
bool charvalid(const char);

const char tail_short = '-';
const char tail_long = '=';
const int maxColumn = 79;
const int minColumn =  0;


class Particle {
  float pos, vel;
  char sym;

  public:void init( const float pos, const float vel, const char sym ) {
    this->pos = pos;
    this->vel = vel;
    this->sym = sym;
  }

  public:void move() {
    this->pos += this->vel;

    if (this->pos >= maxColumn) {
      this->pos = maxColumn;
      this->vel *= -1.0;
    } else if (this->pos <= minColumn) {
      this->pos = minColumn;
      this->vel *= -1.0;
    }     
  }

  public:void draw( char *const screen ) {
    int ipos = static_cast<int>(this->pos);
    screen[ipos] = this->sym;
    if(this->vel < 0.0) {
      if(ipos < maxColumn-1 && charvalid(screen[ipos+1])) screen[ipos+1] = tail_long;
      if(ipos < maxColumn-2 && charvalid(screen[ipos+2])) screen[ipos+2] = tail_short;
    } else {
      if(ipos > minColumn+1 && charvalid(screen[ipos-1])) screen[ipos-1] = tail_long;
      if(ipos > minColumn+2 && charvalid(screen[ipos-2])) screen[ipos-2] = tail_short;
    }
  }
};

int main() {
  int timeStep = 0;
  const int stopTime = 60;
  const int num_particles = 3;
  char* screen = new char[maxColumn+1];
  Particle *p = new Particle[3];
  p[0].init( 0,  6.3, 'x');
  p[1].init(79, -4.4, 'o');
  p[2].init(50,  3.0, '+');

  while (timeStep < stopTime) {
    screen_clear(screen);
    for(int i=0; i<num_particles; i++)
    {
      p[i].draw(screen);
      p[i].move();
    }
    screen_print(screen);
    timeStep++;
  }
  delete [] screen;
  delete [] p;
}

void screen_clear( char *const screen ) {
  for (int i = 0; i <= maxColumn; i++) {
    screen[i] = ' ';
  }  
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
