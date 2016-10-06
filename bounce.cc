// N.B. This program contains a bug, on purpose.
#include <iostream>
#include <fstream>
#include <cstdlib>
#include "Particle.hh"
#include "Screen.hh"

int main() {
  int timeStep = 0;
  const int stopTime = 60;
  int num_particles = -1;
  double pos, vel;
  char sym;
  Particle* p;
  Screen screen(1+(maxColumn-minColumn));

  //Particle P = {Particle(0,  6.3, 'x'), Particle(79, -4.4, 'o'), Particle(50,  3.0, '+')}; Better declaration
  std::ifstream in("particles.dat");
  if(!in) {
    std::cerr << "Could not open file!" << std::endl;
    return EXIT_FAILURE;
  } else {
    std::cout << "Reading";
    while(!in.eof()) {
      in >> sym >> pos >> vel;
      std::cout << ".";
      num_particles++;
    }
    p = new Particle[num_particles];
    in.close(); // Couldn't find reset
    in.open("particles.dat");
  }

  std::cout << " found " << num_particles << " particles." << std::endl;

  for(int i=0; i<num_particles; i++) {
    in >> pos >> vel >> sym;
    std::cout << pos << vel << sym << std::endl;
    if(in.good()) {
      p[i] = Particle(pos, vel, sym);
      std::cout << "(" << i+1 << "/" << num_particles << ") " << p[i] << std::endl;
    } else { 
      std::cerr << "Error!" << std::endl;
      return EXIT_FAILURE;
    } 
  }

  std::cout << "Read in " << num_particles << " particles." << std::endl;

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
  std::cout << "Listing " << num_particles << " particles:" << std::endl;
  for(int i=0; i<num_particles; i++) {
    std::cout << p[i] << std::endl;
  }
}

