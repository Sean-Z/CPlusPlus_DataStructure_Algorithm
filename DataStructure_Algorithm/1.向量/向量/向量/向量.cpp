// 向量.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#define DEFAULT_CAPACITY  3
typedef int Rank;  //疑问1：为什么用Rank代替int?
template <typename T>
class Vector
{
protected:
    Rank _size;     //数组规模
    int _capacity;  //数组容量
    T* _elem;       //数据存储位置

    void copyFrom(T const* A, Rank lo, Rank hi)
    {
        _elem = new T[_capacity = 2 * (hi - lo)];
        _size = 0;
        while (lo < hi)
        {
            _elem[_size++] = A[lo++];
        }
        
    }
public:
    Vector(int c = DEFAULT_CAPACITY, int s = 0, T v = 0)  //向量初始化为0
    {
        _elem = new T[_capacity = c];
        for (_size = 0; _size < s; _size++)
        {
            _elem[_size] = 0;
        }
    }

    Vector(T const* A, Rank n)  //数组整体复制到Vector
    {
        copyFrom(A, 0, n);
    }
    Vector(T const* A, Rank lo, Rank hi) //数组部分复制到Vector，注意区间的左闭右开
    {
        copyFrom(A, lo, hi);
    }
    Vector(Vector<T> const& V)
    {
        copyFrom(V._elem, 0, V._size);
    }
    Vector(Vector<T> const& V, Rank lo, Rank hi)
    {
        copyFrom(V._elem, lo, hi);
    }

    void PrintVector()
    {
        for (int i = 0; i < _size; ++i)
        {
            std::cout << _elem[i] << std::endl;
        }
    }


};

int main()
{   
    Vector<int> V1(10, 5, 1);
    V1.PrintVector();
    std::cout << "***********" << std::endl;

    int array1[5] = { 1,2,3,4,5 };
    Vector<int> V2(array1,5);
    V2.PrintVector();
    std::cout << "***********" << std::endl;

    int array2[7] = { 1,2,3,4,5,6,7 };
    Vector<int> V3(array2, 2, 7);
    V3.PrintVector();
    std::cout << "***********" << std::endl;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
