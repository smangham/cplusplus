// N.B. This program contains a bug, on purpose.
#include <iostream>


const char tail_short = '-';
const char tail_long = '=';
const int maxColumn = 79;
const int minColumn =  0;

class Screen {
public:
  // CONSTRUCTORS
  Screen ( unsigned width )       : width(width),       buffer(new char[width]      ) { return; }
  Screen ( const Screen& other )  : width(other.width), buffer(new char[other.width]) {
    std::copy(other.buffer, other.buffer+other.width, this->buffer);
  }
  ~Screen () {
    delete [] this->buffer;
  }
  //OPERATORS
  friend void swap(Screen&, Screen& );
  char& operator[] ( const int );
  Screen& operator=( Screen );
  //MEMBERS
  void clear();
  void print() const;
private:
  unsigned width;
  char *buffer, junk;
  bool charvalid( const char );
};

char& Screen::operator[]( const int pos ) {
  if(pos >= 0 && pos < this->width && charvalid(this->buffer[pos])) {
    return buffer[pos];
  } else {
    //Aha! We need more advanced C++ techniques here, or to not use this technique
    return junk;
  }
}
Screen& Screen::operator=( Screen other) {
  swap(*this, other);
  //This lets us swap every member easily. 
  //We just need a swap function for each type in the same scope the type is defined in 
  return *this;
}
//MEMBERS
void Screen::clear() {
  for (unsigned i = 0; i < this->width; i++) {
    this->buffer[i] = ' ';
  }  
}
void Screen::print() const {
  for(int i=0; i< this->width; i++)
  {
    std::cout << this->buffer[i];
  }
  std::cout << std::endl;    
}
bool Screen::charvalid( const char test ) {
  return( test == ' ' || test == '-');
}

void swap(Screen& one, Screen& two) {
  using std::swap;
  swap(one.width,  two.width);
  swap(one.buffer, two.buffer);
}

class Particle {
public:
  // CONSTRUCTORS
  Particle () : pos(0), vel(0), sym('?') { return; };
  Particle ( const float pos, const float vel, const char sym ) : 
    pos(pos), vel(vel), sym(sym) { return; };
  // OPERATORS
  friend void swap(Particle& one, Particle& two);
  friend std::ostream& operator<<(std::ostream& os, const Particle &p);
  Particle& operator=( Particle );
  // MEMBERS
  void move();
  void draw( Screen& ) const;
private:
  float pos, vel;
  char sym;
};

void Particle::move() {
  this->pos += this->vel;

  if (this->pos >= maxColumn) {
    this->pos = maxColumn;
    this->vel *= -1.0;
  } else if (this->pos <= minColumn) {
    this->pos = minColumn;
    this->vel *= -1.0;
  }     
}

void Particle::draw( Screen& screen ) const {
  int ipos = static_cast<int>(this->pos);
  screen[ipos] = this->sym;
  if(this->vel < 0.0) {
    screen[ipos+2] = tail_short;
    screen[ipos+1] = tail_long;
  } else {
    screen[ipos-2] = tail_short;
    screen[ipos-1] = tail_long;
  }
}
Particle& Particle::operator=( Particle other ) {
  swap(*this, other);
  return (*this);
}


void swap(Particle& one, Particle& two) {
  using std::swap;
  swap(one.sym, two.sym);
  swap(one.pos, two.pos);
  swap(one.vel, two.vel);
}

std::ostream& operator<<(std::ostream& os, const Particle &p) {
  return os << p.sym << ", Pos: " << p.pos << ", Vel: " << p.vel;
}

int main() {
  int timeStep = 0;
  const int stopTime = 60;
  const int num_particles = 3;
  Screen screen(1+(maxColumn-minColumn));
  Particle p[num_particles];
  // = {Particle(0,  6.3, 'x'), Particle(79, -4.4, 'o'), Particle(50,  3.0, '+')}; Better declaration
  p[0] = Particle(0,  6.3, 'x');
  p[1] = Particle(79, -4.4, 'o');
  p[2] = Particle(50,  3.0, '+');

  Screen test_screen(9);
  test_screen = screen;

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
  for(int i=0; i<num_particles; i++) {
    std::cout << p[i] << std::endl;
  }
}

