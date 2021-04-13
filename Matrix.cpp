#include "Matrix.h"


void do_something(){}

std::pair<int, int> maxIndex(const Matrix& x) {
	double val = -1;
	std::pair<int, int> itr(0,0);
	for (int i = 0; i < x.getN(); i++) {
		for (int j = 0; j < x.getM(); j++) {
			if (x.get(i, j) > val) {
				val = x.get(i, j);
				itr.first = i;
				itr.second = j;
			}
		}
	}
	return itr;
}
