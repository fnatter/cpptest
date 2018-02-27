#include <fstream>
#include <cctype>
#include "fasta2string.h"

class FileNotFoundException : public std::exception {
  std::string file;
public:
  virtual const char* what() const throw() {
    return std::string("File not found: " + file).c_str();
  }
  
  FileNotFoundException(std::string filename) {
    file = filename;
  }
  ~FileNotFoundException() throw() { }
};

std::string fasta2string(std::string filename)
{
  char buffer[8192];
  std::ifstream is(filename.c_str(), std::ifstream::in);
  if (!is.is_open())
    throw FileNotFoundException(filename);
  is.getline(buffer, 8191); // discard information header
  std::string ret;
  while (is.good()) {
    char c = std::tolower(is.get());
    if (c >= 'a' && c <= 'z')
      ret += c;
  }
  return ret;
}
