// N.B. This program contains a bug, on purpose.
#include <iostream>


const char tail_short = '-';
const char tail_long = '=';
const int maxColumn = 79;
const int minColumn =  0;

class Screen {
public:
  Screen ( unsigned width )   : width(width),   screen(new char[width])   { return; }
  Screen ( const Screen& s )  : width(s.width), screen(new char[s.width]) {
    std::copy(s.screen, s.screen+s.width, this->screen);
  }
  ~Screen () {
    delete [] this->screen;
  }
  void draw( const int pos, const char sym ) {
    if(pos >= 0 && pos < this->width && charvalid(this->screen[pos]))
    {
      this->screen[pos] = sym;
    }
  }
  void clear() {
    for (int i = 0; i < this->width; i++) {
      this->screen[i] = ' ';
    }  
  }
  void print() const {
    for(int i=0; i< this->width; i++)
    {
      std::cout << this->screen[i];
    }
    std::cout << std::endl;    
  }
private:
  const unsigned width;
  char *screen;
  bool charvalid( const char test ) {
    return( test == ' ' || test == '-');
  }
};

class Particle {
public:
  void init( const float pos, const float vel, const char sym ) {
    this->pos = pos;
    this->vel = vel;
    this->sym = sym;
  }

  void move() {
    this->pos += this->vel;

    if (this->pos >= maxColumn) {
      this->pos = maxColumn;
      this->vel *= -1.0;
    } else if (this->pos <= minColumn) {
      this->pos = minColumn;
      this->vel *= -1.0;
    }     
  }
  void draw( Screen& screen ) const {
    int ipos = static_cast<int>(this->pos);
    screen.draw(ipos, this->sym);
    if(this->vel < 0.0) {
      screen.draw(ipos+1, tail_long);
      screen.draw(ipos+2, tail_short);
    } else {
      screen.draw(ipos-1, tail_long);
      screen.draw(ipos-2, tail_short);
    }
  }
private:
  float pos, vel;
  char sym;
};

int main() {
  int timeStep = 0;
  const int stopTime = 60;
  const int num_particles = 3;
  Particle *p = new Particle[num_particles];
  Screen screen(1+(maxColumn-minColumn));
  p[0].init( 0,  6.3, 'x');
  p[1].init(79, -4.4, 'o');
  p[2].init(50,  3.0, '+');

  while (timeStep < stopTime) {
    screen.clear();
    for(int i=0; i<num_particles; i++)
    {
      p[i].draw(screen);
      p[i].move();
    }
    screen.print();
    timeStep++;
  }
  delete [] p;
}

