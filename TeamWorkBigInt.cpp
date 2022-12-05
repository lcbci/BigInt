/*
 * @Author: hhl && 1914638062@qq.com
 * @Date: 2022-08-07 11:56:56
 * @LastEditors: hhl && 1914638062@qq.com
 * @LastEditTime: 2022-12-05 11:32:14
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
		vector<int> vec;
		int symbol;
	public:
		TeamWorkBigInt() //���캯�� 
		{
			symbol=0;
	        vec.push_back(0);//��ʼ�� 
		}
		TeamWorkBigInt operator=(TeamWorkBigInt a); 
		TeamWorkBigInt(int b);
		
		TeamWorkBigInt operator+=(const TeamWorkBigInt& x) {*this=*this+x; return *this;}//˫Ŀ���� 1
		TeamWorkBigInt operator-=(const TeamWorkBigInt& x) {*this=*this-x; return *this;}
		TeamWorkBigInt operator*=(const TeamWorkBigInt& x) {*this=*this*x; return *this;}
		TeamWorkBigInt operator/=(const TeamWorkBigInt& x) {*this=*this/x; return *this;}

		
		TeamWorkBigInt operator+=(const int& x) {*this=*this+x; return *this;}//˫Ŀ���� 2
		TeamWorkBigInt operator-=(const int& x) {*this=*this-x; return *this;}
		TeamWorkBigInt operator*=(const int& x) {*this=*this*x; return *this;}
		TeamWorkBigInt operator/=(const int& x)	{*this=*this/x; return *this;}
		
		friend TeamWorkBigInt operator+(const TeamWorkBigInt& x,const TeamWorkBigInt& y);//������������ 
		friend TeamWorkBigInt operator-(const TeamWorkBigInt& x,const TeamWorkBigInt& y);
		friend TeamWorkBigInt operator*(const TeamWorkBigInt& x,const TeamWorkBigInt& y);
		friend TeamWorkBigInt operator/(const TeamWorkBigInt& x,const TeamWorkBigInt& y);
		
		friend TeamWorkBigInt operator+(const TeamWorkBigInt& x,const int& y) {TeamWorkBigInt t; t=y; return x+t;}
		friend TeamWorkBigInt operator-(const TeamWorkBigInt& x,const int& y) {TeamWorkBigInt t; t=y; return x-t;}
		friend TeamWorkBigInt operator*(const TeamWorkBigInt& x,const int& y) {TeamWorkBigInt t; t=y; return x*t;}
		friend TeamWorkBigInt operator/(const TeamWorkBigInt& x,const int& y) ;//��Դ��⣬�����ع����������Ч�� 
		
		friend ostream& operator<<(ostream& out,const TeamWorkBigInt& a);                   //������� 
		friend TeamWorkBigInt pow(const TeamWorkBigInt& a,int b);                           //�ݺ��� 
		friend inline int compare_size(const TeamWorkBigInt& x,const TeamWorkBigInt& y);    //�Ƚ�����������ֵ��С 
};



TeamWorkBigInt TeamWorkBigInt::operator=(TeamWorkBigInt a)
{
	int i;
	vec.clear();
	symbol=a.symbol;
	vec.swap(a.vec);//swapЧ�ʸߣ� 
	
//����д��Ч�ʵ� 
//	vec.resize(a.vec.size(),0);
//	for(i=0;i<a.vec.size();i++)
//	{
//		vec[i]=a.vec[i];
//	}
	return *this;
}

TeamWorkBigInt::TeamWorkBigInt(int b)
{
	int temp,i=0,a=b;
	vec.clear();
	if(a>=0)symbol=0;
	else 
	{
		symbol=1;
		a=-a;
	}
	while(a>9) //�����θ���������ֵ������������push_back�����ڴ��Ϊ���� 
	{
		temp=a%10;
		vec.push_back(temp);
		a/=10;
		i++; 
	}
	vec.push_back(a); 
}

TeamWorkBigInt operator+(const TeamWorkBigInt& x,const TeamWorkBigInt& y)
{
	TeamWorkBigInt c,a(x),b(y);
	if(a.symbol==0&&b.symbol==1){b.symbol=0;return a-b;}// a+(-b)
	if(a.symbol==1&&b.symbol==0){a.symbol=0;return b-a;}// -a+b
	if(a.symbol==1&&b.symbol==1)// -a+(-b)
	{
		a.symbol=0;
		b.symbol=0;
		c=a+b;
		c.symbol=1;
		return c;
	}
	if(a.symbol==0&&b.symbol==0)// a+b
	{
		int max,i,s=0;
		if(a.vec.size()>=b.vec.size())//�жϴ�С 
		{
			max=a.vec.size();
			b.vec.resize(max,0);
		}
		else 
		{
			max=b.vec.size();
			a.vec.resize(max,0);
		}
		
		c.vec.resize(max+1,0);//���ٿռ�
		 
		for(i=0;i<max;i++)//�����㷨 
		{
			int s=a.vec[i]+b.vec[i]+c.vec[i];
			c.vec[i+1]=s/10;
			c.vec[i]=s%10;
			
		}
		
		for(i=max;i>=0;i--)//ɾ�������0 
		{
			if(c.vec[i]!=0)break;
			else
			{
				c.vec.pop_back();
			}
		}
		return c;
	}	
}

TeamWorkBigInt operator-(const TeamWorkBigInt& x,const TeamWorkBigInt& y)
{
	TeamWorkBigInt c,a(x),b(y);
	if(a.symbol==0&&b.symbol==1)//a-(-b)
	{b.symbol=0;return a+b;}
	if(a.symbol==1&&b.symbol==0)//-a-b
	{
		a.symbol=0;
		c=a+b;
		c.symbol=1;
		return c;
	}
	if(a.symbol==1&&b.symbol==1)//-a-(-b)
	{
		a.symbol=0;
		b.symbol=0;
		return b-a;
	}
	if(a.symbol==0&&b.symbol==0)//a-b
	{
		if(compare_size(x,y)==0)//x-x=0
		{
			return c;
		}
		
		if(compare_size(x,y)==1)
		{
			int max,i;
			max=a.vec.size();
			b.vec.resize(max,0);//��ǰ���ٿռ䣬������ѭ���￪�٣��������Ч�� 
			c.vec.resize(max+1,0);
			for(i=0;i<max;i++)//�����㷨 
			{
				int s=a.vec[i]-b.vec[i]+c.vec[i];
				if(s<0) 
				{
					c.vec[i+1]=-1;
					c.vec[i]=s+10;
				}
				else 
				{
					c.vec[i+1]=0;
					c.vec[i]=s;
				}
			
			}
			for(i=max;i>=0;i--)//ɾ�������0 
			{
				if(c.vec[i]!=0)break;
				else
				{
					c.vec.pop_back();
				}
			}
			return c;
		}	
	}
		
		if(compare_size(x,y)==-1)
		{
			a=y;b=x;
			c=a-b;
			c.symbol=1;
			return c;
		}
	}
	
TeamWorkBigInt operator*(const TeamWorkBigInt& x,const TeamWorkBigInt& y)
{
	int i,j,max,min;
	TeamWorkBigInt c,s,a(x),b(y);
	if(a.symbol==0&&b.symbol==1)//a*(-b)
	{
		b.symbol=0;
		c=a*b;
		c.symbol=1;
		return c;
	}
	if(a.symbol==1&&b.symbol==0)//-b*a
	{
		a.symbol=0;
		c=a*b;
		c.symbol=1;
		return c;
	}
	if(a.symbol==1&&b.symbol==1)//(-a)*(-b)
	{
		a.symbol=0;
		b.symbol=0;
		return a*b;
	}
	if(a.symbol==0&&b.symbol==0)//a*b
	{
		if(compare_size(x,y)==-1)//���С 
		{
			a=y;
			b=x;
		}
		max=a.vec.size();
		min=b.vec.size();
		for(i=0;i<min;i++)
		{
			for(j=0;j<i;j++) c.vec.push_back(0);
			for(j=0;j<max;j++) 
			{
				int t=a.vec[j]*b.vec[i]+c.vec[j+i];
				c.vec[j+i]=t%10;
				c.vec.push_back(t/10);
			}
			s=s+c;
			c.vec.clear();
	        c.vec.push_back(0);
		}
		return s;
	}
	
}

inline int compare_size(const TeamWorkBigInt& x,const TeamWorkBigInt& y)    //�Ƚ�����������ֵ��С 
{
	int i;
	if(x.vec.size()>y.vec.size()) return 1;
	if(x.vec.size()<y.vec.size()) return -1;
	if(x.vec.size()==y.vec.size())
	{
		for(i=x.vec.size()-1;i>=0;i--)
		{
			if(x.vec[i]==y.vec[i])continue;
			if(x.vec[i]>y.vec[i]) {return 1; break;}
			if(x.vec[i]<y.vec[i]) {return -1; break;}
		}
		return 0;
	}
}

TeamWorkBigInt operator/(const TeamWorkBigInt& x,const TeamWorkBigInt& y)
{
	int i,r=0,min,max,q,clen;
	TeamWorkBigInt a(x),b(y),c,t,n(10);
	if(b.vec.back()==1&&b.vec.front()==0)//�������10�ı�����ֱ��ɾ��λ�� ���ж�����������ȫ������Դ��⣩ 
	{
		q=b.vec.size()-1;
		a.vec.erase(a.vec.begin(),a.vec.begin()+q);
		return a;
	}
	if(a.symbol==0&&b.symbol==1)//a/-b
	{
		b.symbol=0;
		c=a/b;
		c.symbol=1;
		return c;
	}
	if(a.symbol==1&&b.symbol==0)//-a/b
	{
		a.symbol=0;
		c=a/b;
		c.symbol=1;
		return c;
	}
	if(a.symbol==1&&b.symbol==1)//-a/-b
	{
		a.symbol=0;
		b.symbol=0;
		return a/b;
	}
	// a/b ���������ڴ����� �����ò��� 
//	if(a.symbol==0&&b.symbol==0)
//	{
//		if(compare_size(x,y)==-1){t=0; return t;}
//		if(compare_size(x,y)==0) {t=1; return t;}
//		if(compare_size(x,y)==1) 
//		{
//			q=0;
//			c.vec.clear();
//			max=a.vec.size();
//			min=b.vec.size();
//			clen=max-min+1;
//			c.vec.resize(clen,0);
//			t=b*pow(n,clen-1);
//			for(i=clen-1;i>=0;i--)
//			{
//				while(compare_size(a,t*(r+1))==1||compare_size(a,t*(r+1))==0)
//				{	
//					r++;
//				}
//				a-=t*r;
//				c.vec[i]=r;
//				if(compare_size(a,q)==0)break;
//			
//				r=0;
//				t=t/n;
//			}
//			if(compare_size(x,b*pow(n,clen-1))==-1)c.vec.pop_back();
//			return c;
//		}
//	}
}

ostream& operator<<(ostream& out,const TeamWorkBigInt& a)
{
	int i;
	if(a.symbol==1&&a.vec[a.vec.size()-1]!=0) out<<"-";
	for(i=a.vec.size()-1;i>=0;i--)
	{
		out<<a.vec[i];
	}
	return out;
}


TeamWorkBigInt pow(const TeamWorkBigInt& a,int b)
{
	//��Ա���ֱ�����0���������Ч�� 
	TeamWorkBigInt t;
	int i;
	t.vec.resize(b+1,0);
	t.vec[b]=1;
	return t;
// ��׼д�� 
//	t=a;
//	for(i=1;i<b;i++)
//	{
//		t*=a;
//	} 
//	return t;
}

TeamWorkBigInt operator/(const TeamWorkBigInt& x,const int& y)  
{
	int i,r=0,clen,b=y;
	TeamWorkBigInt a(x),z(y),c,n(10);
	if(a.symbol==0&&b<0)
	{
		b=-b;
		c=a/b;
		c.symbol=1;
		return c;
	}
	if(a.symbol==1&&b<0)
	{
		a.symbol=0;
		b=-b;
		c=a/b;
		c.symbol=0;
		return c;
	}
	if(a.symbol==1&&b>0)
	{
		a.symbol=0;
		c=a/b;
		c.symbol=1;
		return c;
	}
	if(compare_size(x,z)==0){c=0;return c;}
	if(compare_size(x,z)==1) 
	{
		clen=a.vec.size();
		c.vec.resize(clen,0);
		for(i=clen-1;i>=0;i--)
		{
			c.vec[i]=(r*10+a.vec[i])/b;
			r=(r*10+a.vec[i])%b;
		}
		for(i=clen-1;i>=0;i--)
		{
			if(c.vec[i]==0)c.vec.pop_back();
			else break;
		}
		
		return c;
	}
}

void calculate_pi()
{
	int i,N;
	clock_t startTime,endTime;
    TeamWorkBigInt  n=10,b,x1,x2,s,t,pi;
	cout<<"--------------------------------------------------"<<endl;
	cout << "������Ҫ���㵽��Բ����λ��:"<<endl;
    cin>>N;
	startTime =clock();
	N--;  
	b=pow(n,N+10);

	x1=b*4/5;
	x2=b/-239;
	s=x1+x2;
	
	for(i=3;i<=N*2;i+=2)
	{	x1/=-25;
		x2/=-57121;
		t=(x1+x2)/i;
		s+=t;	
	}
	pi=s*4;
	cout <<endl<<"������Ϊ:"<<endl;
	cout<< (pi/pow(n,10))<<endl<<endl;
	endTime =clock();
	cout<< "The run time is: "<<(double)(endTime-startTime)/1000.0<<"s"<<endl;
	cout<< "--------------------------------------------------" <<endl;
	cin.get();
}

//StudybarCommentBegin
int main()
{	
	while (1)
	{
		calculate_pi();
	}
	
}
//StudybarCommentEnd
