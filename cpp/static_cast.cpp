#include <iostream>
#include <stdlib.h>

using namespace std;

class A {
	public:
		int a;   
		virtual void foo(){};
};

class B:public A {
	public:
		int b;
};

class C:public B {
	public:
		int c;
};

int main(void)
{
	B *pb = new B;
	A *pa = pb;
	A *paa = dynamic_cast<A *>(pb);
	if(!paa)
	{
		cout<< "error"<<endl;
		exit(-1);
	}
	//指针的上行转换
	C *pc1 = new C;
	B *pb1 = pc1;
	A *pa1 = static_cast<A *>(pc1);
	A *paa1 = dynamic_cast<A *>(pc1);

	//指针的下行转化
//	B *pb2 = pa1; //error
	B *pb3 = static_cast<B *>(pa1); // ok! not safe
	B *pb4 = dynamic_cast<B *>(pa1); // ok! safe
#if 0	
	int tmp = 10;
	A a1;
	a1.a = 20;

	cout<<"tmp  =  "<<tmp<<endl;
	cout<<"a1.a= "<<a1.a<<endl;

//	B *pb = &a1; //error
//	B *pb = static_cast<B *>(&a1); 
	B *pb = dynamic_cast<B *>(&a1);
	if(pb == NULL)
	{
		cout<<"error"<<endl;
		exit(-1);
	}
	//使子类指针指向父类指针
	static_cast<>
	静态类型转化 不包括安全检查 故 不安全
	dynamic_cast<> 
	动态类型转化 包括安全检查 但是必须 类为多态  虚函数 
	
	pb->b=98;
	cout<<"tmp = "<<tmp<<endl;
#endif	

	return 0;
}
