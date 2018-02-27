#include "SimilarityMatrix.h"
#include <algorithm> // max
#include <iomanip> // setw

using namespace std;

string SimilarityMatrix::getRepetition(int count, const char* elt)
{
  string ret = "";
  while (count > 0) {
    ret.append(elt);
    count--;
  }
  return ret;
}


void SimilarityMatrix::printAlignmentsFrom(int r, int c,
                                           std::string align_suffix1,
                                           std::string align_suffix2)
{
  //cerr << "printAlignmentsFrom(" << r << ", " << c << ")" << endl;

  if (r == 1 && c == 1 || (local && e(r,c) == 0)) {

    if (local) {
      // add context for local alignment
      align_suffix1 = s1.substr(0, r-1) + align_suffix1;
      align_suffix2 = getRepetition(r-1, " ") + align_suffix2;
    }

    int from = 0, to = align_suffix1.length() - 1;
    while (from <= to) {
      int chunkto = min((int)align_suffix1.length() - 1, from + 75);
      if (from == 0)
        cout << setw(3) << ali_nr << ": "
             << align_suffix1.substr(from, chunkto-from+1) << endl
             << "     " << align_suffix2.substr(from, chunkto-from+1) << endl;
      else
        cout << align_suffix1.substr(from, chunkto-from+1) << endl
             << align_suffix2.substr(from, chunkto-from+1) << endl;
      from = chunkto + 1;
    }
    ali_nr++;
  }
  else {
    bool found_way = false;

    if (r > 1 && c > 1 &&
        e(r,c) == e(r-1,c-1) + (isMatch(r,c) ? match : mismatch)) {
      if (found_way && ali_count > 1) { // start new alignment branch (up to ali_count times)
        ali_count--;
        printAlignmentsFrom(r-1, c-1,
                            s1.at(r-2)+align_suffix1,
                            s2.at(c-2)+align_suffix2);
      } else if (!found_way) // continue with current alignment
        printAlignmentsFrom(r-1, c-1,
                            s1.at(r-2)+align_suffix1,
                            s2.at(c-2)+align_suffix2);
      found_way = true;
    }

    // the second option r == 1 && e(r,c-1)==0 is for freegapstart2
    if (c > 1 && (e(r,c) == e(r,c-1) + gap || (freegapstart2 && r == 1 && e(r,c-1) == 0))) {
      if (found_way && ali_count > 1) { // start new alignment branch (up to ali_count times)
        ali_count--;
        printAlignmentsFrom(r, c-1,
                            string("-")+align_suffix1,
                            s2.at(c-2)+align_suffix2);
      } else if (!found_way) // continue with current alignment
        printAlignmentsFrom(r, c-1,
                            string("-")+align_suffix1,
                            s2.at(c-2)+align_suffix2);
      found_way = true;
    }
    
    // the second option c == 1 && e(r-1,c)==0 is for freegapstart1
    if (r > 1 && (e(r,c) == e(r-1,c) + gap || (freegapstart1 && c == 1 && e(r-1,c) == 0))) {
      if (found_way && ali_count > 1) { // start new alignment branch (up to ali_count times)
        ali_count--;
        printAlignmentsFrom(r-1, c,
                            s1.at(r-2)+align_suffix1,
                            string("-")+align_suffix2);
      } else if (!found_way) // continue with current alignment
        printAlignmentsFrom(r-1, c,
                            s1.at(r-2)+align_suffix1,
                            string("-")+align_suffix2);
      found_way = true;
    }

  }
}

void SimilarityMatrix::printAlignments(int count) {
  ali_count = count;
  ali_nr = 1;
  int maxrow = (int)s1.length()+1;
  int maxcol = (int)s2.length()+1;
  if (!freegapend1 && !freegapend2 && !local)
    printAlignmentsFrom(maxrow, maxcol, "", ""); // global alignment
  else if (local) {
    // local alignment
    int max_score = getAlignmentScore();
    for (int r = 1; r <= maxrow; r++) {
      for (int c = 1; c <= maxcol; c++) {
        if (e(r,c) == max_score) { // bei r-1 anfangen => 012345, n=6
          printAlignmentsFrom(r, c,
                              s1.substr(maxrow-1-(maxrow-r), (maxrow-r)),
                              getRepetition(maxrow-r, " "));
          ali_count--;
        }
      }
    }    
  } else {
    // semi-global alignment
    int max_score = getAlignmentScore();
    if (e(maxrow,maxcol) == max_score)
      printAlignmentsFrom(maxrow, maxcol, "", "");
    if (freegapend2) {
      string align_suffix1;
      string align_suffix2;
      for (int r = maxrow-1; ali_count > 1 && r >= 1; r--) {
        align_suffix1 = s1.at(r-1) + align_suffix1;
        align_suffix2 = string("-") + align_suffix2;
        //cerr << "freegapend1: (" << r << "," << maxcol << ") : "
        //     << align_suffix1 << "/" << align_suffix2 << endl;
        if (e(r,maxcol) == max_score) {
          printAlignmentsFrom(r, maxcol, align_suffix1, align_suffix2);
          ali_count--;
        } 
      }
    }
    if (freegapend1) {
      string align_suffix1;
      string align_suffix2;
      for (int c = maxcol-1; ali_count > 1 && c >= 1; c--) {
        //cerr << "freegapend1: (" << maxrow << "," << c << ") : "
        //     << align_suffix1 << "/" << align_suffix2 << endl;
        align_suffix1 = string("-") + align_suffix1;
        align_suffix2 = s2.at(c-1) + align_suffix2;
        if (e(maxrow,c) == max_score) {
          printAlignmentsFrom(maxrow, c, align_suffix1, align_suffix2);
          ali_count--;
        }
      }
    }
  }
}


int SimilarityMatrix::getAlignmentScore() {
  int maxrow = (int)s1.length()+1;
  int maxcol = (int)s2.length()+1;
  // check only (maxrow,maxcol) when doing global alignment
  int best_score = e(maxrow,maxcol);
  if (local) {
    // local alignment: scan whole matrix
    for (int r = 1; r <= maxrow; r++) {
      for (int c = 1; c <= maxcol; c++) {
        if (e(r,c) > best_score)
          best_score = e(r,c);
      }
    }
  } else {
    // semi-global alignment: check first line/column
    if (freegapend1) {
      for (int i = 2; i <= maxcol; i++) {
        //cerr << "getAlignmentScore: checking ("
        //     << maxrow << "," << i << ")" <<endl;
        if (e(maxrow,i) > best_score)
          best_score = e(maxrow,i);
      }
    }
    if (freegapend2) {
      for (int i = 2; i <= maxrow; i++) {
        //cerr << "getAlignmentScore: checking ("
        //     << i << "," << maxcol << ")" <<endl;
        if (e(i,maxcol) > best_score)
          best_score = e(i,maxcol);
      }
    }
  }
  return best_score;
}

bool SimilarityMatrix::isMatch(int x1, int x2)
{
  char col = s1.at(x1-2);
  char row = s2.at(x2-2);
  //  std::cout << "comparing (" << x1 << "," << x2 << ") "
  //     << col << " with " << row << std::endl;
  return col == row;
}

void SimilarityMatrix::init()
{
  // first column: start-gap penalties for s1
  for (int i = 0; i <= (int)s1.length(); i++)
    e(i+1,1) = ((freegapstart2 || local) ? 0 : i*gap);
  // first row: start-gap penalties for s2
  for (int i = 1; i <= (int)s2.length(); i++)
    e(1,i+1) = ((freegapstart1 || local) ? 0 : i*gap);
  // compute the rest of the matrix
  for (int x1 = 2; x1 <= (int)s1.length()+1; x1++) {
    for (int x2 = 2; x2 <= (int)s2.length()+1; x2++) {
      int score_try_match = e(x1-1,x2-1) + (isMatch(x1,x2) ? match : mismatch);
      int score_gap1 = e(x1-1,x2) + gap;
      int score_gap2 = e(x1,x2-1) + gap;
      e(x1,x2) = max(score_try_match, max(score_gap1, score_gap2));
      if (local)
        e(x1,x2) = max(0, e(x1,x2));
    }
  }
}
      /*
      cout << "e(x1-1,x2-1)=" << e(x1-1,x2-1)
           << ", isMatch(x1,x2)=" << isMatch(x1,x2) 
           << ", score_try_match=" << score_try_match
           << ", " << score_gap1
           << ", " << score_gap2
           << endl;
      */
