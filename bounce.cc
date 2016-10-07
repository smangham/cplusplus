// N.B. This program contains a bug, on purpose.
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <vector>
#include "Screen.hh"
#include "Particle.hh"
//#include "Array.hh"

int main() {
  int timeStep = 0;
  const int stopTime = 60;

  std::string filename("particles.dat");
  
  std::vector<Particle*> p;
  Screen screen(1+(maxColumn-minColumn));

  std::ifstream in(filename.c_str());
  std::cout << "Reading from "<<filename;
 
  if(!in) {
    std::cerr << "Could not open file " << filename << std::endl;
    return EXIT_FAILURE;
  } else {
    RealParticle* temp;
    MagicParticle* temp_magic;
    char type;
      
    while(in) {
      in >> type;
      std::cout << ".";
      if(!in) {
        break;
      } else {
        if(type == 'm') {
          temp_magic = new MagicParticle();
          in >> *temp_magic;
          p.push_back(temp_magic);
        } else {
          temp = new RealParticle();
          in >> *temp;
          p.push_back(temp);
        }
      }
    }
    std::cout << std::endl;
  }

  for(int i=0; i<p.size(); i++) {
    std::cout << *p[i] << std::endl;
  }

  Particle *p_add = new RealParticle(1.0,1.0,'#');
  p.push_back(p_add);
  std::cout << "Added " << (*p[p.size()-1]) << std::endl;

  while (timeStep < stopTime) {
    screen.clear();
    for(int i=0; i<p.size(); i++)
    {
      p[i]->draw(screen);
      p[i]->move();
    }
    screen.print();
    timeStep++;
  }
  for(int i=0; i<p.size(); i++) {
    std::cout << *p[i] << std::endl;
    delete p[i];
  }
  return EXIT_SUCCESS;
}

