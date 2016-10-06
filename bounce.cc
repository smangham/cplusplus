// N.B. This program contains a bug, on purpose.
#include <iostream>
#include "Particle.hh"
#include "Screen.hh"

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

