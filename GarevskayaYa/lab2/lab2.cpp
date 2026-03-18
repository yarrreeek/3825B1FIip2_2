#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

class Matrix {

private:
    int** a;    
    int n;        

public:

    Matrix() {
        n = 2;
        a = new int* [n];
        for (int i = 0; i < n; i++) {
            a[i] = new  int[n];
            for (int j = 0; j < n; j++) {
                a[i][j] = 0;
            }
        }
        cout << "Matrix created" << endl;
    }

   
    Matrix(int size) {
        if (size < 2) size = 2;
        if (size > 8) size = 8;
        n = size;
        a = new int* [n];
        for (int i = 0; i < n; i++) {
            a[i] = new int[n];
            for (int j = 0; j < n; j++) {
                a[i][j] = 0;
            }
        }
        cout << "Matrix created" << endl;
    }

 
    Matrix(const Matrix& m) {
        n = m.n;
        a = new int* [n];
        for (int i =  0; i < n; i++) {
            a[i] = new int[n];
            for (int j = 0; j < n; j++) {
                a[i][j] = m.a[i][j];
            }
        }
        cout << "Matrix copied" << endl;
    }

    ~Matrix() {
        for (int i = 0; i < n; i++) {
            delete[] a[i];
        }
        delete[] a;
        cout << "Matrix deleted" << endl;
    }

    Matrix& operator=(const Matrix& m) {
        if (this != &m) {
            for (int i = 0; i < n; i++) {
                delete[] a[i];
            }
            delete[] a;

            n = m.n;
            a = new int* [n];
            for (int i = 0; i < n; i++) {
                a[i] = new int[n];
                for (int j = 0; j < n; j++) {
                    a[i][j] = m.a[i][j];
                }
            }
        }
        cout << "Matrix assigned" << endl;
        return *this;
    }

  
    void setSize(int newSize) {
        if (newSize < 2 || newSize > 8) {
            cout << "Error size" << endl;
            return;
        }

        int** temp = new int* [newSize];
        for (int i = 0; i < newSize; i++) {
            temp[i] = new int[newSize];
            for (int j = 0; j < newSize; j++) {
                temp[i][j] = 0;
            }
        }

        for (int i = 0; i < min(n, newSize); i++) {
            for (int j = 0; j < min(n, newSize); j++) {
                temp[i][j] = a[i][j];
            }
        }

        for (int i = 0; i < n; i++) {
            delete[] a[i];
        }
        delete[] a;

        a = temp;
        n = newSize;
        cout << "Size changed" << endl;
    }

  
    int getSize() {
        return n;
    }

    void setEl(int i, int j, int val) {
        if (i >= 0 && i < n && j >= 0 && j < n) {
            a[i][j] = val;
        }
    }

    int getEl(int i, int j) {
        if (i >= 0 && i < n && j >= 0 && j < n) {
            return a[i][j];
        }
        return 0;
    }

    bool diagDom() {
        for (int i = 0; i < n; i++) {
            int diag = abs(a[i][i]);
            int sum = 0;
            for (int j = 0; j < n; j++) {
                if (i != j) {
                    sum += abs(a[i][j]);
                }
            }
            if (diag <= sum) {
                return false;
            }
        }
        return true;
    }

    Matrix sum(Matrix& m) {
        if (n != m.n) {
            cout << "Different sizes" << endl;
            return *this;
        }

        Matrix res(n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                res.a[i][j] = a[i][j] + m.a[i][j];
            }
        }
        return res;
    }

    void print() {
        cout << "Matrix:" << endl;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cout << a[i][j] << " ";
            }
            cout << endl;
        }
    }

    void input() {
        cout << "Enter matrix:" << endl;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cin >> a[i][j];
            }
        }
    }
};

int main() {

    Matrix m1;
    m1.print();

    Matrix m2(3);
    m2.setEl(0, 0, 5);
    m2.setEl(0, 1, 1);
    m2.setEl(0, 2, 2);
    m2.setEl(1, 0, 3);
    m2.setEl(1, 1, 8);
    m2.setEl(1, 2, 1);
    m2.setEl(2, 0, 2);
    m2.setEl(2, 1, 3);
    m2.setEl(2, 2, 7);
    m2.print();

    cout << "Size: " << m2.getSize() << endl;

    if (m2.diagDom()) {
        cout << "Yes" << endl;
    }
    else {
        cout << "No" << endl;
    }

    Matrix m3(3);
    m3.setEl(0, 0, 1);
    m3.setEl(0, 1, 1);
    m3.setEl(0, 2, 1);
    m3.setEl(1, 0, 1);
    m3.setEl(1, 1, 1);
    m3.setEl(1, 2, 1);
    m3.setEl(2, 0, 1);
    m3.setEl(2, 1, 1);
    m3.setEl(2, 2, 1);
    m3.print();

    Matrix m4 = m2.sum(m3);
    m4.print();

    Matrix m5 = m2;
    m5.print();

    m2.setSize(4);
    m2.print();

    return 0;
}