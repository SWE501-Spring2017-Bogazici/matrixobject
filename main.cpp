#include <iostream>

using namespace std;

template<typename T>
class Matrix {
private:
    int width;
    int height;

    T* data;
public:
    Matrix(int m, int n){
        height = m;
        width = n;
        data = new T[m*n];
    }

    Matrix(int m, int n, T *data)
    {
        height = m;
        width = n;
        this->data = data;
    }

    void Print()
    {
        for (int i = 0; i < height; ++i) {

            for (int j = 0; j < width; ++j) {
                cout << (this->data)[j + (width * i)] << " ";
            }

            cout << endl;
        }

        cout << endl;
    }

    Matrix &operator+=(Matrix &m)
    {
        for (int i = 0; i < width * height; ++i) {
            this->data[i]+= m.data[i];
        }
    }

    Matrix &operator*=(Matrix &m)
    {
        T newData[width*height];
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                T val1 = (this->data)[j + (width * i)];
                T val2 = m.data[i+ (height * j)];
                T val = val1* val2;
                newData[i*width + j] = val;
            }
        }

        for (int k = 0; k < width * height; ++k) {
            this->data[k] = newData[k];

        }
    }

    Matrix operator*(Matrix *m)
    {
        T newData[width*height];
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                T val1 = (this->data)[j + (width * i)];
                T val2 = m->data[i+ (height * j)];
                T val = val1* val2;
                newData[i*width + j] = val;
            }
        }

        for (int k = 0; k < width * height; ++k) {
            this->data[k] = newData[k];

        }

        return Matrix<T>(m->height,m->width, newData);
    }

    T* operator()(int t1, int t2)
    {
        T *d = &(this->data[t1 * width + t2]);

        return d;
    }

};

int main() {
    int data[6] = {1,2,3,4,5,6};
    Matrix<int> matrix(3,2, data);
    Matrix<int> matrix2(2,3, data);

    matrix.Print();
    matrix2.Print();
    *(matrix(0,0)) = 5;
    matrix+=matrix2;

    matrix*=matrix2;
    matrix.Print();

    return 0;
}