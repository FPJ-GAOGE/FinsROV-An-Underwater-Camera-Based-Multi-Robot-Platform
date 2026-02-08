//
// Created by admin on 2023/11/21.
//
#include "matrix.h"

void Matrix::eye()
{
    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (i == j)
                mat[i][j] = 1;
            else
                mat[i][j] = 0;
        }
    }
}
bool Matrix::inv(Matrix a)
{
    if (a.n != a.m)
    {
        
        return false;
    }
    m = a.m; n = a.n;
    eye(); // Create an identity matrix. //创建单位矩阵

		// Perform top-down elementary row operations to transform `a.mat` into an upper-triangular matrix with unit diagonal.
    //下来进行自上而下的初等行变换，使得矩阵 a.mat 变成单位上三角矩阵
    for (int i = 1; i <= m; i++) // Note that here `i <= m`, which differs from the earlier upper-triangular transformation, for we must check whether the last row’s last-column entry becomes zero after triangularization. 
    {                         	//注意这里要 i<=m，和之前的上三角矩阵有不同，因为要判断最后一行化为上三角矩阵的最后一行最后一列元素是否为 0
        // Search for a non-zero entry in column `i`.
				//寻找第 i 列不为零的元素
        int k;
        for (k = i; k <= m; k++)
        {
            if (fabs(a.mat[k][i]) > 1e-10) // When this condition is met, the entry is considered non-zero. //满足这个条件时，认为这个元素不为0
                break;
        }
        if (k <= m) // This indicates that column `i` contains at least one non-zero element. //说明第 i 列有不为0的元素
        {
            if (k != i) // This indicates that `a.mat[i][i]` is zero and a row swap is required. //说明第 i 行 第 i 列元素为零，需要和其他行交换
            {
								// Swap all elements of row `i` and row `k`.
                //交换第 i 行和第 k 行所有元素
                for (int j = 1; j <= n; j++) // The swap must start from the first element; note that this differs from the previous triangularization procedure.//需从第一个元素交换，注意与之前化上三角矩阵不同
                {// Use `mat[0][j]` as a temporary variable to swap elements; both matrices must be swapped accordingly. //使用mat[0][j]作为中间变量交换元素,两个矩阵都要交换
                    a.mat[0][j] = a.mat[i][j]; a.mat[i][j] = a.mat[k][j]; a.mat[k][j] = a.mat[0][j];
                    mat[0][j] = mat[i][j]; mat[i][j] = mat[k][j]; mat[k][j] = mat[0][j];
                }
            }
            float b = a.mat[i][i];//Multiplier. //倍数
            // Normalize the main diagonal elements of `a.mat` to 1.
						//将矩阵 a.mat 的主对角线元素化为 1
            for (int j = 1; j <= n; j++) // Start from the first element. //从第一个元素开始
            {
                a.mat[i][j] /= b;
                mat[i][j] /= b;
            }
            for (int j = i + 1; j <= m; j++)
            {
								//Note that the factor would normally be `-a.mat[j][i] / a.mat[i][i]`; since `a.mat[i][i] = 1`, the division is unnecessary.
                //注意本来为 -a.mat[j][i]/a.mat[i][i],因为a.mat[i][i]等于 1，则不需要除它
                b = -a.mat[j][i];
                for (k = 1; k <= n; k++)
                {
                    a.mat[j][k] += b * a.mat[i][k]; // Add (b × row i) to row j.//第 i 行 b 倍加到第 j 行
                    mat[j][k] += b * mat[i][k];
                }
            }
        }
        else
        {
            
            return false;
        }
    }

		// Next, perform bottom-up row operations to reduce `a.mat` to the identity matrix.
    //下面进行自下而上的行变换，将 a.mat 矩阵化为单位矩阵
    for (int i = m; i > 1; i--)
    {
        for (int j = i - 1; j >= 1; j--)
        {
            float b = -a.mat[j][i];
            a.mat[j][i] = 0;  // In practice, elementary row operations are applied to eliminate this entry. //实际上是通过初等行变换将这个元素化为 0
            for (int k = 1; k <= n; k++)
            {
							// Apply the same elementary row operations to transform the matrix on the right-hand side.
							//通过相同的初等行变换来变换右边矩阵
                mat[j][k] += b * mat[i][k];
            }
        }
    }
    return true;
}



