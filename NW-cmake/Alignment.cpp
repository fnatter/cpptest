#include <iostream>
#include <cmath>
#include <memory>
#include "Matrix.h"
#include "fasta2string.h"
#include "SimilarityMatrix.h"

using namespace std;

int main(int argc, char** argv)
{
  try {
    if (argc != 6 && argc != 7) {
      cout << "Syntax: " << argv[0]
           << " <string1> <string2> <match> <mismatch> <gap> <opt1,opt2,...>" << endl;
      cout << "Known options: freegapstart[12],freegapend[12]" << endl;
      return 1;
    }
    // get options
    string opts;
    if (argc == 7) {
      opts = argv[6];
      if (opts.find("freegapall") != string::npos)
        opts.append("freegapstart1,freegapstart2,freegapend1,freegapend2");
    } else {
      opts = "";
    }
    string s1 = argv[1];
    if (s1.find_first_of(".") != std::string::npos)
      s1 = fasta2string(s1);
    string s2 = argv[2];
    if (s2.find_first_of(".") != std::string::npos)
      s2 = fasta2string(s2);

    unique_ptr<string> myptr(new string("abc"));
    unique_ptr<string> myptr2(move(myptr));

    unique_ptr<SimilarityMatrix> sm(
      new SimilarityMatrix(s1, s2,
                           atoi(argv[3]), atoi(argv[4]), atoi(argv[5]),
                           (opts.find("freegapstart1") == string::npos)? false : true,
                           (opts.find("freegapend1") == string::npos)? false : true,
                           (opts.find("freegapstart2") == string::npos)? false : true,
                           (opts.find("freegapend2") == string::npos)? false : true,
                           (opts.find("local") == string::npos)? false : true));
    sm->print();

    cout << "Score: " << sm->getAlignmentScore() << endl;
    sm->printAlignments(5);

  }
  catch (exception& e) {
    cerr << "Exception: " << e.what() << endl;
    return 2;
  }
  
  return 0;
}
