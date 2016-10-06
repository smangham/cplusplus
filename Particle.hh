#ifndef Particle_hh
#define Particle_hh

#include "Screen.hh"

const char tail_short = '-';
const char tail_long = '=';

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
#endif
