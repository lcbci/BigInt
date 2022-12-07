# BigInt
Description:  
32位整数的计算机可以表示整数的范围近似为－20亿到＋20亿。  
在这个范围内操作一般不会出现问题，但是有的应用程序可能需要使用超出上述范围的整数。  
C++可以满足这个需求，创建功能强大的新的数据类型。

根据后缀,定义一个大整数类，实现大整数的加、减、乘、除、幂、输出重载等，并能去计算pi的值。  
输入一个整数n，输出圆周率的前n位数字（不包含小数点）

样例输入:  
3

样例输入：  
314


后缀代码:	
--------------------------------------------------



int main()  
{	  

	int i,N;
        TeamWorkBigInt  n=10,b,x1,x2,s,t,pi;
        cin>>N;
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
	cout<< (pi/pow(n,10))<<endl;
    	return 0;
}



--------------------------------------------------
