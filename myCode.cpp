#include <iostream>
#include <cctype>
#include <cstdio>
#include <algorithm>
using namespace std;
struct BigInteger
{
	int n[10001];
	int length;
	BigInteger()
	{
		length=1;
		n[1]=0;
	}
	void set(int a)
	{
		if(!a)
		{
			return ;
		}
		int i=0;
		int aCopy=a;
		while(aCopy)
		{
			n[++i]=aCopy%10;
			aCopy/=10;
		}
		reverse(n+1,n+i+1);
		length=i;
	}
	void baseRead(int num,int pos)
	{
		n[pos]=num;
	} 
	void read()
	{
		char ch;
		while(1)
		{
			ch=getchar();
			if(isdigit(ch))
			{
				break;
			}
		}
		length=1;
		while(1)
		{
			if(!isdigit(ch))
			{
				break;
			}
			baseRead(ch-'0',length);
			length++;
			ch=getchar();
		}
		length--;
	} 
	void outputWithSpace()
	{
		for(int i=1;i<=length;i++)
		{
			cout<<n[i]<<" ";
		}
		cout<<endl;
	}
	void output()
	{
		for(int i=1;i<=length;i++)
		{
			cout<<n[i];
		}
		cout<<endl;
	}
	BigInteger clone()
	{
		BigInteger b;
		for(int i=1;i<=length;i++)
		{
			b.n[i]=n[i];
		}
		b.length=length;
		return b;
	}
	BigInteger cut(int start,int end)
	{
		BigInteger b;
		for(int i=start;i<=end;i++)
		{
			b.n[i]=n[i];
		}
		b.length=end-start+1;
		return b;
	}
	int baseCompare(BigInteger b)
	{
		for(int i=1;i<=length;i++)
		{
			if(n[i]!=b.n[i])
			{
				return (n[i]>b.n[i])?1:-1;
			}
		}
		return 0;
	}
	int compare(BigInteger b)
	{
		if(length!=b.length)
		{
			return (length>b.length)?1:-1;
		}
		return baseCompare(b);
	}
	void add(int adder)
	{
		if(length==1 && !n[1])
		{
			n[length]=adder;
			return ;
		}
		n[++length]=adder;
	}
	void leftMove(int offset)
	{
		for(int i=offset+1;i<=length;i++)
		{
			n[i-offset]=n[i];
		}
		length-=offset;
	}
	void minus(BigInteger sub)
	{
		bool borrow=false;
		for(int i=length,j=sub.length;i>=1;i--,j--)
		{
			n[i]-=borrow+sub.n[j];
			borrow=false;
			if(n[i]<0)
			{
				borrow=true;
				n[i]+=10;
			}
		}
		int i;
		for(i=1;i<=length;i++)
		{
			if(n[i])
			{
				break;
			}
		}
		leftMove(--i);
		if(!length)
		{
			length=1;
			n[1]=0;
		}
	}
	int baseDiv(BigInteger divisor)
	{
		int result=0;
		while(compare(divisor)>=0)
		{
			minus(divisor);
			result++;
		}
		return result;
	}
	BigInteger div(BigInteger divisor)
	{
		BigInteger remainder,result;
		int startPos=1,endPos=1;
		for(endPos=1;endPos<=length;endPos++)
		{
			remainder.add(n[endPos]);
//			cout<<endPos<<endl;
			if(remainder.compare(divisor)<0)
			{
				result.add(0);
				continue;
			}
//			cout<<remainder.baseDiv(divisor)<<endl;
			result.add(remainder.baseDiv(divisor));
		}
		return result;
	}
	bool equal(BigInteger bi)
	{
		if(bi.length!=length)
		{
			return false;
		}
		for(int i=1;i<=length;i++)
		{
			if(n[i]!=bi.n[i])
			{
				return false;
			}
		}
		return true;
	}
	bool equalInteger(int a)
	{
		BigInteger aCopy;
		aCopy.set(a);
		return equal(aCopy);
	}
};
int main()
{
//	freopen("p2005test.out","w",stdout);
	BigInteger a,b/*,c*/;
//	a.output();
//	b.output();

	a.read();
	b.read();
	a.div(b).output();

	for(int i=1;i<=10000;i++)
	{
		for(int j=1;j<=10000;j++)
		{
			a.set(i);
			b.set(j);
			if(!a.div(b).equalInteger(i/j))
			{
//				a.output();
//				b.output();
				cout<<"Wrong!\nAt "<<i<<" / "<<j<<"\nIt says the answer is: ";
				a.div(b).output();
				cout<<"But the correct answer is: "<<i/j<<"\n";
			}
		}
	}

//	cout<<a.baseDiv(b)<<endl;
//	a.minus(b);
//	b=a.cut(1,4);
//	b=a.clone();
//	a.output();
//	b.output();
//	a.outputWithSpace();
	return 0;
}
