#ifndef SIMILARITYMATRIX_H
#define SIMILARITYMATRIX_H

#include <string>
#include "Matrix.h"

class SimilarityMatrix : public Matrix<int> {
protected:
  std::string s1;
  std::string s2;
  int mismatch, match, gap;
  bool freegapstart1, freegapend1;
  bool freegapstart2, freegapend2;
  bool local;
  int ali_count;
  int ali_nr;

  void init();
  bool isMatch(int x1, int x2);
  std::string getRepetition(int count, const char* elt);

  void printAlignmentsFrom(int r, int c,
                           std::string align_suffix1, std::string align_suffix2);
  
public:

  void printAlignments(int count);

  int getAlignmentScore();

  void print() {
    std::cout << "match=+" << match
              << ", mismatch="<< mismatch
              << ", gap=" << gap
              << ", freegapstart1: " << freegapstart1
              << ", freegapstart2: " << freegapstart2
              << ", freegapend1: " << freegapend1
              << ", freegapend2: " << freegapend2
              << ", local: " << local
              << std::endl;
    Matrix<int>::print(std::string(" ") + s2, std::string(" ") + s1);
  }
 
 SimilarityMatrix(std::string s1, std::string s2,
                  int match, int mismatch, int gap,
                  bool freegapstart1, bool freegapend1,
                  bool freegapstart2, bool freegapend2,
                  bool local) 
    : Matrix<int>(s1.length()+1, s2.length()+1)
  {
    this->mismatch = mismatch;
    this->match = match;
    this->gap = gap;
    this->s1 = s1;
    this->s2 = s2;
    this->freegapstart1 = freegapstart1;
    this->freegapend1 = freegapend1;
    this->freegapstart2 = freegapstart2;
    this->freegapend2 = freegapend2;
    this->local = local;
    init();
  }
  ~SimilarityMatrix() {
  }
};

#endif
