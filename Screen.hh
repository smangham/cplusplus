#ifndef Screen_hh
#define Screen_hh

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
#endif
