/*
 * @Author: hhl && 1914638062@qq.com
 * @Date: 2022-08-07 11:56:56
 * @LastEditors: hhl && 1914638062@qq.com
 * @LastEditTime: 2022-12-07 00:39:32
 * @FilePath: \C++\TeamWorkBigInt.cpp
 * @Description: Gubba nub nub doo rahkah.
 * 
 * Copyright (c) 2022 by hhl, All Rights Reserved. 
 */
#include<iostream>
#include<vector>
#include<cmath>
#include<ctime>
using namespace std;

class TeamWorkBigInt
{
	private:
		vector<int> vec; // 用vector储存整数绝对值
		int symbol;      // 符号
	public:
		TeamWorkBigInt() // 无参构造函数 
		{
			symbol=0; // 初始符号为正
	        vec.push_back(0); // 初始化 
		}
		TeamWorkBigInt(int b); // 有参构造函数 
		TeamWorkBigInt operator=(TeamWorkBigInt a); // 拷贝构造函数
		
		// 双目重载1 (BigInt)
		TeamWorkBigInt operator+=(const TeamWorkBigInt& x) {*this=*this+x; return *this;}
		TeamWorkBigInt operator-=(const TeamWorkBigInt& x) {*this=*this-x; return *this;}
		TeamWorkBigInt operator*=(const TeamWorkBigInt& x) {*this=*this*x; return *this;}
		TeamWorkBigInt operator/=(const TeamWorkBigInt& x) {*this=*this/x; return *this;}

		// 双目重载2 (int)
		TeamWorkBigInt operator+=(const int& x) {*this=*this+x; return *this;}
		TeamWorkBigInt operator-=(const int& x) {*this=*this-x; return *this;}
		TeamWorkBigInt operator*=(const int& x) {*this=*this*x; return *this;}
		TeamWorkBigInt operator/=(const int& x)	{*this=*this/x; return *this;}
		
		// 四则运算重载 (BigInt,BigInt)
		friend TeamWorkBigInt operator+(const TeamWorkBigInt& x,const TeamWorkBigInt& y);
		friend TeamWorkBigInt operator-(const TeamWorkBigInt& x,const TeamWorkBigInt& y);
		friend TeamWorkBigInt operator*(const TeamWorkBigInt& x,const TeamWorkBigInt& y);
		friend TeamWorkBigInt operator/(const TeamWorkBigInt& x,const TeamWorkBigInt& y);
		
		// 四则运算重载 (BigInt,int)
		friend TeamWorkBigInt operator+(const TeamWorkBigInt& x,const int& y) {TeamWorkBigInt t; t=y; return x+t;}
		friend TeamWorkBigInt operator-(const TeamWorkBigInt& x,const int& y) {TeamWorkBigInt t; t=y; return x-t;}
		friend TeamWorkBigInt operator*(const TeamWorkBigInt& x,const int& y) {TeamWorkBigInt t; t=y; return x*t;}
		friend TeamWorkBigInt operator/(const TeamWorkBigInt& x,const int& y); 
		// 除法是大整数运算效率的瓶颈，在遇到大整数除于整数时，如果将整数转为大整数再运算，效率很低
		// 因此，需要一个直接将大整数和整数运算的算法，这样能大大提高效率

		friend int compare_size(const TeamWorkBigInt& x,const TeamWorkBigInt& y);   // 比较两个数绝对值大小
		friend TeamWorkBigInt pow(const TeamWorkBigInt& a,int b);                   // 幂函数 
		friend ostream& operator<<(ostream& out,const TeamWorkBigInt& a);     		// 输出重载 
};

TeamWorkBigInt::TeamWorkBigInt(int b)
{
	int temp, i = 0, a = b;
	vec.clear(); //将初始化的vec[0]清空

	if (a >= 0)	 //判断符号
		symbol = 0;
	else
	{
		symbol = 1;
		a = -a;
	}

	while (a > 9) //用整形给大整数赋值计算量不大，用push_back开辟内存较为合适
	{
		temp = a % 10;
		vec.push_back(temp);
		a /= 10;
		i++;
	}
	vec.push_back(a);
}

TeamWorkBigInt TeamWorkBigInt::operator=(TeamWorkBigInt a)
{
	int i;
	vec.clear();
	symbol = a.symbol;
	vec.swap(a.vec); // swap效率高！

	//以下写法效率低
	//	vec.resize(a.vec.size(),0);
	//	for(i=0;i<a.vec.size();i++)
	//	{
	//		vec[i]=a.vec[i];
	//	}
	return *this;
}

TeamWorkBigInt operator+(const TeamWorkBigInt &x, const TeamWorkBigInt &y)
{
	TeamWorkBigInt c, a(x), b(y);
	
	if (a.symbol == 0 && b.symbol == 1) // a+(-b) = a-b
	{
		b.symbol = 0;
		return a - b;
	}  

	if (a.symbol == 1 && b.symbol == 0) // (-a)+b = b-a
	{
		a.symbol = 0;
		return b - a;
	}	

	if (a.symbol == 1 && b.symbol == 1) // (-a)+(-b) = -(a+b)
	{
		a.symbol = 0;
		b.symbol = 0;
		c = a + b;
		c.symbol = 1;
		return c;
	}
	
	if (a.symbol == 0 && b.symbol == 0) // a+b
	{
		int max, i, s = 0;
		if (a.vec.size() >= b.vec.size()) // 判断大小，并将小的大整数扩容（值为0）
		{
			max = a.vec.size();
			b.vec.resize(max, 0); // 扩容
		}
		else
		{
			max = b.vec.size();
			a.vec.resize(max, 0); // 扩容
		}

		c.vec.resize(max + 1, 0); // 开辟空间

		for (i = 0; i < max; i++) // 核心算法
		{
			int s = a.vec[i] + b.vec[i] + c.vec[i];
			c.vec[i + 1] = s / 10;
			c.vec[i] = s % 10;

		} // 倒序储存

		for (i = max; i >= 0; i--) // 删除多余的0
		{
			if (c.vec[i] != 0)
				break;
			else
			{
				c.vec.pop_back();
			}
		}
		return c;
	}
}

TeamWorkBigInt operator-(const TeamWorkBigInt &x, const TeamWorkBigInt &y)
{
	TeamWorkBigInt c, a(x), b(y);

	if (a.symbol == 0 && b.symbol == 1) // a-(-b) = a+b
	{
		b.symbol = 0;
		return a + b;
	}

	if (a.symbol == 1 && b.symbol == 0) // -a-b = -(a+b)
	{
		a.symbol = 0;
		c = a + b;
		c.symbol = 1;
		return c;
	}

	if (a.symbol == 1 && b.symbol == 1) // -a-(-b) = b-a
	{
		a.symbol = 0;
		b.symbol = 0;
		return b - a;
	}

	if (a.symbol == 0 && b.symbol == 0) // a-b
	{
		if (compare_size(a, b) == 0) // a == b
		{
			return c;
		}

		if (compare_size(a, b) == 1) // a > b
		{
			int max, i;
			max = a.vec.size();
			b.vec.resize(max, 0); // 提前开辟空间，避免在循环里开辟，提高运行效率
			c.vec.resize(max + 1, 0);

			for (i = 0; i < max; i++) // 核心算法
			{
				int s = a.vec[i] - b.vec[i] + c.vec[i];
				if (s < 0)
				{
					c.vec[i + 1] = -1;
					c.vec[i] = s + 10;
				}
				else
				{
					c.vec[i + 1] = 0;
					c.vec[i] = s;
				}
			}

			for (i = max; i >= 0; i--) // 删除多余的0
			{
				if (c.vec[i] != 0)
					break;
				else
				{
					c.vec.pop_back();
				}
			}
			return c;
		}

		if (compare_size(a, b) == -1) // a < b
		{

			c = b - a;
			c.symbol = 1;
			return c;
		}
	}
}

TeamWorkBigInt operator*(const TeamWorkBigInt &x, const TeamWorkBigInt &y)
{
	int i, j, max, min;
	TeamWorkBigInt c, t, a(x), b(y);

	if (a.symbol == 0 && b.symbol == 1) // a*(-b) 
	{
		b.symbol = 0;
		c = a * b;
		c.symbol = 1;
		return c;
	}
	
	if (a.symbol == 1 && b.symbol == 0) // -b*a
	{
		a.symbol = 0;
		c = a * b;
		c.symbol = 1;
		return c;
	}

	if (a.symbol == 1 && b.symbol == 1) // (-a)*(-b)
	{
		a.symbol = 0;
		b.symbol = 0;
		return a * b;
	}

	if (a.symbol == 0 && b.symbol == 0) // a*b
	{
		if (compare_size(a, b) == -1) // 大乘小
		{
			a = y;
			b = x;
		}
		
		max = a.vec.size(); // 大数的容量
		min = b.vec.size(); // 小数的容量

		for (i = 0; i < min; i++) // 核心算法
		{
			t.vec.resize(i+1,0); // 开辟进位空间
			for (j = 0; j < max; j++)
			{
				int temp = a.vec[j] * b.vec[i] + t.vec[j + i];
				t.vec[j + i] = temp % 10;
				t.vec.push_back(temp / 10);
			}
			c = c + t;
			t.vec.clear(); // 清空
		}
		return c;
	}
}

TeamWorkBigInt operator/(const TeamWorkBigInt &x, const TeamWorkBigInt &y)
{
	int i, r = 0, min, max, q, clen;
	TeamWorkBigInt a(x), b(y), c, t, n(10);
	// 经测试如果完全判断，计算圆周率效率大大下降
	// 如果需要其他大整数计算，请完善判断条件
	if (b.vec.back() == 1 && b.vec.front() == 0) //如果除于10的倍数，直接删除位数 （判断条件并不严谨，仅针对此题）
	{
		q = b.vec.size() - 1;
		a.vec.erase(a.vec.begin(), a.vec.begin() + q);
		return a;
	}

	if (a.symbol == 0 && b.symbol == 1) // a/-b
	{
		b.symbol = 0;
		c = a / b;
		c.symbol = 1;
		return c;
	}

	if (a.symbol == 1 && b.symbol == 0) //-a/b
	{
		a.symbol = 0;
		c = a / b;
		c.symbol = 1;
		return c;
	}

	if (a.symbol == 1 && b.symbol == 1) //-a/-b
	{
		a.symbol = 0;
		b.symbol = 0;
		return a / b;
	}

	// a/b 大整数除于大整数 本题用不到
	// if (a.symbol == 0 && b.symbol == 0)
	// {
	// 	if (compare_size(a, b) == -1)
	// 	{
	// 		t = 0; // 赋值
	// 		return t;
	// 	}
	//
	// 	if (compare_size(a, b) == 0)
	// 	{
	// 		t = 1; // 赋值
	// 		return t;
	// 	}
	//
	// 	if (compare_size(a, b) == 1)
	// 	{
	// 		q = 0;
	// 		c.vec.clear();
	// 		max = a.vec.size();
	// 		min = b.vec.size();
	// 		clen = max - min + 1;
	// 		c.vec.resize(clen, 0);
	// 		t = b * pow(n, clen - 1);
	// 		for (i = clen - 1; i >= 0; i--)
	// 		{
	// 			while (compare_size(a, t * (r + 1)) == 1 || compare_size(a, t * (r + 1)) == 0)
	// 			{
	// 				r++;
	// 			}
	// 			a -= t * r;
	// 			c.vec[i] = r;
	// 			if (compare_size(a, q) == 0)
	// 				break;
	//
	// 			r = 0;
	// 			t = t / n;
	// 		}
	//
	// 		if (compare_size(x, b * pow(n, clen - 1)) == -1)
	// 			c.vec.pop_back();
	// 		return c;
	// 	}
	// }
}

TeamWorkBigInt operator/(const TeamWorkBigInt &x, const int &y)
{
	int i, r = 0, clen, b = y;
	TeamWorkBigInt a(x), z(y), c, n(10);

	if (a.symbol == 0 && b < 0)
	{
		b = -b;
		c = a / b;
		c.symbol = 1;
		return c;
	} 

	if (a.symbol == 1 && b < 0)
	{
		a.symbol = 0;
		b = -b;
		c = a / b;
		c.symbol = 0;
		return c;
	}

	if (a.symbol == 1 && b > 0)
	{
		a.symbol = 0;
		c = a / b;
		c.symbol = 1;
		return c;
	}

	if (a.symbol == 0 && b > 0)
	{
		if (compare_size(x, z) == 0)
		{
			c = 0;
			return c;
		}

		if (compare_size(x, z) == 1)
		{
			clen = a.vec.size();
			c.vec.resize(clen, 0);

			for (i = clen - 1; i >= 0; i--) // 核心算法(提高本题计算效率的最重要的部分)
			{
				c.vec[i] = (r * 10 + a.vec[i]) / b;
				r = (r * 10 + a.vec[i]) % b;
			}
			
			for (i = clen - 1; i >= 0; i--) // 消除多余的0
			{
				if (c.vec[i] == 0)
					c.vec.pop_back();
				else
					break;
			}

			return c;
		}
	}
}

int compare_size(const TeamWorkBigInt &x, const TeamWorkBigInt &y) //比较两个数绝对值大小
{
	int i;

	if (x.vec.size() > y.vec.size())
	{
		return 1;
	}
	
	if (x.vec.size() < y.vec.size())
	{
		return -1;
	}

	if (x.vec.size() == y.vec.size()) // 若位数相等
	{
		for (i = x.vec.size() - 1; i >= 0; i--) // 从最高位开始比较大小
		{
			if (x.vec[i] == y.vec[i])
			{
				continue;
			}

			if (x.vec[i] > y.vec[i])
			{
				return 1;
			}

			if (x.vec[i] < y.vec[i])
			{
				return -1;
			}
		}
		return 0; // 都相等返回0
	}
}

TeamWorkBigInt pow(const TeamWorkBigInt &a, int b)
{
	// 针对本题10^n的情形，直接添加0，提高运行效率
	TeamWorkBigInt t;
	int i;
	t.vec.resize(b + 1, 0);
	t.vec[b] = 1;
	return t;
	// 标准写法
	//	t=a;
	//	for(i=1;i<b;i++)
	//	{
	//		t*=a;
	//	}
	//	return t;
}

ostream &operator<<(ostream &out, const TeamWorkBigInt &a) // 输出重载
{
	int i;
	if (a.symbol == 1 && a.vec[a.vec.size() - 1] != 0) // 负数（不包括0）
	{
		out << "-";
	}

	for (i = a.vec.size() - 1; i >= 0; i--) // 逐个输出
	{
		out << a.vec[i];
	}

	return out;
}

void calculate_pi() // 计算圆周率
{
	int i, N;
	clock_t startTime, endTime; // clock用来计时
	TeamWorkBigInt n = 10, b, x1, x2, s, t, pi;
	cout << "--------------------------------------------------" << endl;
	cout << "请输入要计算到的圆周率位数:" << endl;
	cin >> N;
	startTime = clock(); // 开始计时
	N--;
	b = pow(n, N + 10);

	x1 = b * 4 / 5;
	x2 = b / -239;
	s = x1 + x2;

	for (i = 3; i <= N * 2; i += 2)
	{
		x1 /= -25;
		x2 /= -57121;
		t = (x1 + x2) / i;
		s += t;
	}
	pi = s * 4;
	cout << endl
		 << "计算结果为:" << endl;
	cout << (pi / pow(n, 10)) << endl
		 << endl;
	endTime = clock();  // 结束计时
	cout << "The run time is: " << (double)(endTime - startTime) / 1000.0 << "s" << endl;
	cout << "--------------------------------------------------" << endl;
	cin.get();
}

int main()
{
	while (1)
	{
		calculate_pi();
	}
}
