#include "Particle.hh"
#include "Screen.hh"

const int maxColumn = 80;
const int minColumn = 0;
const char tail_short = '-';
const char tail_long  = '=';


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
