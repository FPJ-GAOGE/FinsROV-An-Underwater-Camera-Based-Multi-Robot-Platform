//
// Created by admin on 2023/11/21.
//

#ifndef CONTROL_FRAME_MAIN_MATRIX_H
#define CONTROL_FRAME_MAIN_MATRIX_H

#include <cmath>



const int N_max=10;
class Matrix
{

public:

    int m, n ;//行数和列数
    float mat[N_max][N_max];  //矩阵开始的元素

    Matrix() {}
    Matrix(int mm, int nn)
    {
        m = mm; n = nn;
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                mat[i][j] = 0;
            }
        }
    }

    Matrix(int mm, int nn, float *ele)
    {
        m = mm; n = nn;
        int k=0;
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                mat[i][j] = ele[k];
                ++k;
            }
        }
    }

    void eye();//令矩阵行列下标相同时值为 1，不同时为 0
    void Print();

    bool inv(Matrix a);//求矩阵的逆
};


#endif //CONTROL_FRAME_MAIN_MATRIX_H
