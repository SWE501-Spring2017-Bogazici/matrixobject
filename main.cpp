#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <thread>
using namespace std;

class Matrix{
	int row, column, size;
	double* matrix;
	
	public:
	Matrix(int m, int n){
		row = m; column = n; size = m*n;
		matrix = new double[m*n]; 
	}
	Matrix(int m, int n, string fileloc){
		row = m; column = n; size = m*n;
		matrix = new double[m*n];
		ifstream ifs;
		ifs.open(fileloc, ifstream::in);
		for(int i=0; i<size; i++){ ifs >> matrix[i]; }
		ifs.close();
	}
	
	void print(){
		for(int i=0; i<row; i++){
			for(int j=0;j<column; j++){
				cout << matrix[i*column+j] << "\t";
			}
			cout << endl;
		}
	}
	
	double operator()(int i, int j){ return matrix[i*column+j]; }
	void operator+=(Matrix A){
		if(column==A.column && row==A.row){
			for(int i=0; i<size; i++){ matrix[i] += A(i/column, i%column); }
		}
	}
	void operator*=(Matrix B){
		if(column==B.column && B.column==B.row){
			for(int p=0; p<row; p++){
				int temp[column]; for(int i=0; i<column; i++){ temp[i]=0; }
				for(int r=0; r<column; r++){
					for(int j=0; j<column; j++){
						temp[r] += matrix[p*column+j]*B(j,r);
					}
				}
				for(int k=0; k<column; k++){
					matrix[p*column+k] = temp[k];
				}
			}
		}
	}
	Matrix operator*(Matrix C){
		if(column==C.row){
			Matrix rslt(row, C.column); for(int i=0; i<rslt.size; i++){ rslt.matrix[i]=0; }
			for(int i=0; i<row; i++){
				for(int j=0; j<C.column; j++){
					for(int k=0; k<column; k++){
						rslt.matrix[i*C.column + j] += matrix[i*column + k]*C.matrix[k*C.column + j];
					}
				}
			}
			return rslt;
		}
		else throw;
	}
};

int main()
{
	Matrix dnm1(3, 5);
	dnm1.print();
	
	Matrix dnm2(2, 3, "test1.txt");
	dnm2.print();
	
	Matrix dnm3(2, 2, "test2.txt");
	dnm3.print();
	for(int i=0; i<4; i++){ cout << dnm3(i/2, i%2); } cout << endl;
	
	Matrix dnm4(3, 2, "test1.txt");
	dnm4.print();
	
	dnm2 += dnm2; dnm2.print();
	dnm4 *= dnm3; cout << "Printing dnm4 after multiplication:\n"; dnm4.print();
	Matrix dnm5 = dnm4*dnm3; cout << "Printing dnm5:\n"; dnm5.print();
	
	return 0;
}
