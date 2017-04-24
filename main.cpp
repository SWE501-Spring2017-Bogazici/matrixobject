#include <iostream>
#include <vector>
using namespace std;

class Matrix {
private:
    vector<int> mat;
    int height;
    int width;
public:
    Matrix(int height, int width) {
        this->height = height;
        this->width = width;
        mat.resize(height*width);
        for (int i = 0; i < mat.size(); ++i) {
            mat[i] = 0;
        }
    }
    Matrix(int height, int width, int *data) {
        this->height = height;
        this->width = width;
        mat.resize(height*width);
        for (int i = 0; i < mat.size(); ++i) {
            mat[i] = data[i];
        }
    }
    Matrix(int height, int width, double *data) {
        this->height = height;
        this->width = width;
        mat.resize(height*width);
        for (int i = 0; i < mat.size(); ++i) {
            mat[i] = data[i];
        }
    }
    void operator+=(Matrix matsec) {
        for (int i = 0; i < mat.size(); ++i) {
            mat[i] = matsec.mat[i];
        }
    }
    void operator*=(Matrix matsec) {
        if (height == matsec.width) {
            for (int i = 0; i < width; ++i) {
                int temp = 0;
                for (int j = 0; j < height; ++j) {
                    for (int k = 0; k < 2; ++k) {
                        mat[i*width+j] += this->GetNumberRet(i, k) * matsec.GetNumberRet(k,j);
                    }
                }
            }
        }
    }
//    void operator = (int x) {
//        this = x;
//    }
//    void operator()(int i, int y) {
//        mat[i*width+y] =
//    }
    void PrintOut() {
        for (int i = 0; i < mat.size(); ++i) {
            cout << mat[i] << ' ' ;
            if(i%width == 1) {
                cout << endl;
            }
        }
        cout << endl;
    }
    void Print() {
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                cout << mat[width*i+j] << ' ';
            }
            cout << endl;
        }
    }
    void GetNumber(int row, int column){
        cout << mat[row*width+column] << endl;
    }
    int GetNumberRet(int row, int column){
        return mat[row*width+column] ;
    }
};

int main() {
    int v[6] = {1,2,3,4};
    Matrix matrix1(2,2,v);
    int z[6] = {5,6,7,8};
    Matrix matrix2(2,2,z);
    matrix2.Print();
//    matrix1+=matrix2;
    matrix1.Print();
    matrix1.GetNumber(1,1);
    matrix1*=matrix2;
    matrix1.Print();
    return 0;
}