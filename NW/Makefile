.PHONY: clean all

all: Alignment

CXXFLAGS = -std=c++11

Alignment: Alignment.o fasta2string.o SimilarityMatrix.o
	c++ $(CXXFLAGS) -o $@ $^

%.o: %.cpp $(wildcard *.h)
	c++  $(CXXFLAGS) -gstabs+ -Wall -o $@ -c $<

clean:
	rm -f Alignment *.o *~