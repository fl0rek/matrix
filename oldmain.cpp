#include "matrix.hh"
#include <functional>
#include <iostream>
#include <limits>

#ifdef _DEBUG
#define  D(x) x
#else 
#define D(x)
#endif

/**
 * laods matrix from cin
 */
inline Matrix load_matrix() {
	int64_t ms[9];
	int64_t n;
	const uint v_size = 9;
	for(uint i = 0; i < v_size;)
		if(std::cin >> n) {
			ms[i] = n;
			++i;
			D(std::cout << "ok["  << i << "]" << std::endl;)
		} else {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "podano nie-liczb? (zignorowano lini?)" << std::endl;
		}
	return Matrix(ms[0], ms[1], ms[2], ms[3], ms[4], ms[5], ms[6], ms[7], ms[8]);
}

int main() {
	std::cout << "Projekt 1605 (Miko?aj Florkiewicz)" << std::endl;
	int64_t n;

	bool repeat;
	do {
		// pierwsza macierz
		std::cout << "Podaj 9 wyrazow pierwszej macierzy" << std::endl;
		Matrix m1 = load_matrix();
		std::function<const Matrix(Matrix&,Matrix&)> op;

		//operator
		std::cout << "1) +\n2) -\n3) *\n4) wyznacznik" << std::endl;
		bool done = false;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		while(!done)  {
			if(std::cin >> n) {
				done = true;
				switch(n) {
					case 1 :
						op = (&Matrix::operator+);
						break;
					case 2 :
						op = (&Matrix::operator-);
						break;
					case 3 :
						op = (&Matrix::operator*);
						break;
					case 4 :
						std::cout << m1.denominator() << std::endl;
						break;
					default :
						done = false;
						std::cin.clear();
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						std::cout << "nieoczekiwane wej??ie spr?buj ponownie" << std::endl;
				}
			} else {
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cout << "nieoczekiwane wej??ie spr?buj ponownie" << std::endl;
			}
		}

		if(op) {
			//ew druga macierz
			std::cout << "Podaj 9 wyrazow drugiej macierzy" << std::endl;
			Matrix m2 = load_matrix();
			std::cout << std::bind(op, m1, m2)();
		}

		std::cout << "Powtorzyc? [y/n]";
		char c;
		while(true)
			if(std::cin >> c) {
				if(c == 'y') {
					repeat = true;
					break;
				} else {
					repeat = false;
					break;
				}
			} else {
				repeat = false;
				break;
			}
	} while(repeat);
}

/*
 * == autor: Miko?aj Florkiewicz
 * == grupa: 2I3
 * == zadanie: macierze 
 * == projekt: 1605
 */
