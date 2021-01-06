// 向量.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#define DEFAULT_CAPACITY  3  //默认的最小容量
typedef int Rank;  //疑问1：为什么用Rank代替int?
template <typename T>
class Vector
{
protected:
    Rank _size;     //数组规模
    int _capacity;  //数组容量
    T* _elem;       //数据存储位置

    /*1.复制初始化
    注意区间lo和hi是左闭右开这一个约定俗成
    */
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
    Vector(Vector<T> const& V)      //向量的整体复制初始化
    {
        copyFrom(V._elem, 0, V._size);
    }
    Vector(Vector<T> const& V, Rank lo, Rank hi)        //向量的部分复制
    {
        copyFrom(V._elem, lo, hi);
    }

    void PrintVector()    //打印向量
    {
        for (int i = 0; i < _size; ++i)
        {
            std::cout << _elem[i] << std::endl;
        }
    }
    //2.动态扩容
    //注意该方法的时间复杂度为O(n)
    //了解分摊时间复杂度的计算
    void expand()
    {
        if (_size < _capacity) return; //向量空间足够用，不需要扩容
        if (_capacity < DEFAULT_CAPACITY) _capacity = DEFAULT_CAPACITY;//选取最大的空间作为数组的空间
        T* oldElem = _elem;//保存下当前的数组
        _elem = new T[_capacity << 1];//对数组扩容一倍
        for (int i = 0; i < _size; ++i)
        {
            _elem[i] = oldElem[i];
        }
        delete[]oldElem;
    }

    //3.直接引用元素
    //重载方括号
    //由于返回值是引用，因此可以作为左值使用  V[i] = 10;

    T& operator[](Rank r) const
    {
        return _elem[r];
    }

    //4.插入
    //注意扩容的问题
    //注意元素后移是从最后一个元素往前进行后移，防止数据被覆盖
    Rank Insert(Rank r, T const& e)
    {
        expand();//如果有必要，先扩容
        for (int i = _size; i > r; ++i)
        {
            _elem[r] = _elem[r - 1];
        }
        _elem[r] = e;
        _size++;
        return r;
    }

    //5.区间删除
    //
    int Remove(Rank lo, Rank hi)
    {
        if (lo == hi) return 0;
        while (hi < _size)
            _elem[lo++] = _elem[hi++];
        _size = lo;
        return hi - lo;
    }
    //6.单个元素删除,
    //使用区间删除思想，时间复杂度更小
    T remove(Rank r)
    {
        T e = _elem[r];
        remove(r, r + 1);
        return e;
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
