#include <iostream>
#include <vector>
using namespace std;


class Matrix {
	int m;
	int n;
	double* data;

public:
	Matrix(int _m, int _n) {
		m = _m;
		n = _n;
		data = new double[m*n];
	}

	Matrix(int _m, int _n, double* buffer) {
		m = _m;
		n = _n;
		data = new double[m*n];

		for (int i=0; i<n*m; i++) {
			data[i] = buffer[i];
		}
	};

	~Matrix() {
		delete [] data;
	}

	Matrix(Matrix& A) {
		m = A.m;
		n = A.n;
		data = new double[m*n];
		for (int i=0; i<m*n; i++) data[i] = A.data[i];
		cout << "Copy Constructor" << endl;
	}

	Matrix(Matrix&& A) {
		cout << "Move Constructor" << endl;
		m = A.m;
		n = A.n;
		data = A.data;
		A.data = nullptr;
	}

	Matrix& operator = (Matrix A) {
		double* tmp;
		tmp = data;
		data = A.data;
		A.data =  tmp;
		cout << "Assignment operator" << endl;
		return *this;
	}

	double& operator()(int i, int j) {
		return data[(i-1)*n+j-1];
	}

	int nrows() {return m; }
	int ncols() {return n; }

	void Print(ostream& c = cout) {
		for (int i =0; i<m; i++) {
			for (int j =0; j<n; j++) {
				c << data[i*n+j] << " ";
			}
			c << endl;
		}
	}

	Matrix operator*(Matrix& B) {
		Matrix temp(m, B.ncols());

		double* tempdata = temp.data;
		//if (n!=B.nrows()) exit(-1);
		for (int i=0; i<m; i++) {
			for (int j=0; j<B.ncols(); j++) {
				tempdata[i*B.ncols()+j] = 0;
				for (int k=0; k<n; k++) {
					tempdata[i*B.ncols()+j]+= data[i*n+k]*B.data[k*B.ncols()+j];
				}
			}
		}
		return temp;
	}
};

ostream& operator<<(ostream& c, Matrix& M) {
	M.Print(c);
	return c;
}

int main() {
	double buffer[] = {1,2,3,4,5,6,7,8,9};
	Matrix M(3,3, buffer);
	Matrix Y(3,3, buffer);

	M(1,2) = 0;
	M(1,3) = M(3,3);

	cout << M << endl;
	Matrix A = Y*M;


	//cout << endl;
	cout << A << endl;
	return 0;
}
