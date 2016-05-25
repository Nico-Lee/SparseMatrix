#pragma once
#include<iostream>
#include<vector>
using namespace std;
template<class T>
struct Triple
{
	int _cow;
	int _col;
	T _value;
	Triple(int cow,int col,T value)
		:_cow(cow)
		, _col(col)
		, _value(value)
	{}
	Triple()
		:_cow(0)
		, _col(0)
	{

	}
};


template<class T>
class SparseMatrix
{
public:
	SparseMatrix(T* a, int m, int n, const T& invalid)
		:_cow(m)
		, _col(n)
		, _invalue(invalid)
	{
		for (int i = 0; i < m; ++i)
		{
			for (int j = 0; j < n; ++j)
			{
				if (a[i*n + j] != invalid)
				{
					Triple<T> tmp(i, j, a[i*n + j]);
					_a.push_back(tmp);
				}
			}
		}
	}
	SparseMatrix()
		:_cow(0)
		, _col(0)
	{}
	
	//矩阵的转置
	SparseMatrix<T> Transport()
	{
		SparseMatrix<T> tmp;
		tmp._cow = _col;
		tmp._col = _cow;
		tmp._invalue = _invalue;
		for (size_t i = 0; i < _col; ++i)
		{
			size_t index = 0;
			while (index < _a.size())
			{
				if (_a[index]._col == i)
				{
					Triple<T> tp;
					tp._col = _a[index]._cow;
					tp._cow = _a[index]._col;
					tp._value = _a[index]._value;
					tmp._a.push_back(tp);
				}
				index++;
			}
		}
		return tmp;
	}
	//矩阵的快速转置
	SparseMatrix<T> FastTransport()
	{
		SparseMatrix<T> tmp;
		tmp._cow = _col;
		tmp._col = _cow;
		tmp._invalue = _invalue;
		tmp._a.resize(_a.size());//resever相当于开辟容量，有的空间不可用
		int* cowCount = new int[_col];//统计转置后矩阵每一行的数据的个数
		int* cowStart = new int[_col];//统计转置后矩阵每行在压缩矩阵中存储的位置
		memset(cowCount, 0, sizeof(int)*_col);
		memset(cowStart, 0, sizeof(int)*_col);
		size_t index = 0;
		while (index < _a.size())
		{
			cowCount[_a[index++]._col]++;
			cowStart[0];
			for (size_t i = 1; i < _col; ++i)
			{
				cowStart[i] = cowStart[i - 1] + cowCount[i - 1];
			}
		}
		index = 0;
		while (index < _a.size())
		{
			int& cowBegin = cowStart[_a[index]._col];
			Triple<T> tp;
			tp._col = _a[index]._cow;
			tp._cow = _a[index]._col;
			tp._value = _a[index]._value;
			tmp._a[cowBegin] = tp;
			cowBegin++;
			index++;
		}
		return tmp;
	}
	void Display()
	{
		size_t index = 0;
		for (int i = 0; i < _cow; i++)
		{
			for (int j = 0; j < _col; j++)
			{
				if (index < _a.size()//此处必须加index<_a.size()这个条件，
					//并且在最前面访问到最后一个有效值后再_a[index]会访问越界
					&&_a[index]._cow == i && _a[index]._col == j)
				{
					cout << _a[index]._value << " ";
					++index;
				}
				else
				{
					cout << _invalue << " ";
				}
			}
			cout << endl;
		}
		cout << endl;
	}

protected:
	vector<Triple<T>> _a;
	int _cow;//矩阵行数
	int _col;//矩阵列数
	T _invalue;
};
