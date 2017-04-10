//============================================================================
// Name        : ders.cpp
// Author      : Can Candan
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>

using namespace std;

class Matrix {
public:
	int numRows;
	int numCols;
	vector<vector<int> > data;

	int getNumRows() {
		return numRows;
	};
	int getNumCols() {
		return numCols;
	}


	Matrix(int m, int n) {
		data.resize(m);
		for (int i=0; i<data.size(); i++) {
		    data[i].resize(n);
		}
		numRows=m;
		numCols=n;
	}

	int& operator() (int i, int j) {
		return this->data[i][j];
	}

	Matrix operator*(Matrix& rhs) {
	  int rows = numRows;
	  int cols = rhs.getNumCols();
	  Matrix result(rows, cols);
	  for (int i=0; i<rows; i++) {
	    for (int j=0; j<cols; j++) {
	      for (int k=0; k<numCols; k++) {
	        result(i,j) += this->data[i][k] * rhs(k,j);
	      }
	    }
	  }
	  return result;
	}

	Matrix operator+(Matrix& rhs) {
		Matrix result(numRows, numCols);

		for (int i=0; i<numRows; i++) {
			for (int j=0; j<numCols; j++) {
				result(i,j) = this->data[i][j] + rhs(i,j);
			}
		}

		return result;
	}


	Matrix& operator*=(Matrix& rhs) {
	  Matrix result = (*this) * rhs;
	  (*this) = result;
	  return *this;
	}
};

ostream& operator<<(ostream& os, Matrix& m)
{
	for (int i=0;i<m.numRows;i++) {
		for (int j=0;j<m.numCols;j++) {
			os << m(i,j) << " ";
		}
		os << endl;
	}
    return os;
}

int main() {
	Matrix m1= Matrix(3,2);
	m1(0,0)=1;m1(0,1)=2;
	m1(1,0)=3;m1(1,1)=4;
	m1(2,0)=5;m1(2,1)=6;

	cout << m1;
	cout << endl;

	Matrix m2= Matrix(2,3);
	m2(0,0)=1;m2(0,1)=2;m2(0,2)=3;
	m2(1,0)=4;m2(1,1)=5;m2(1,2)=6;
	cout << m2;
	cout << endl;

	cout << "Prod:" << endl;
	Matrix prod=m1*m2;
	cout << prod << endl;

	cout << "-------" << endl;

	Matrix m3= Matrix(3,2);
	m1(0,0)=4;m1(0,1)=4;
	m1(1,0)=2;m1(1,1)=3;
	m1(2,0)=6;m1(2,1)=8;

	cout << m1 << endl;


	return 0;
}
