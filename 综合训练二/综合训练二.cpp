#include<iostream>
#include<string>
#include<cmath>
#include<cstdlib>
using namespace std;

class Complex {
	private:
		double real;
		double imag;
		
	public:
		Complex(double r=0.0,double i=0.0) {
			real=r;
			imag=i;
		}
		double getModulus();
		Complex operator+(Complex &B);
		Complex operator-(Complex &B);
		Complex operator*(Complex &B);
		Complex operator/(Complex &B);
		friend ostream& operator<<(ostream& os, const Complex& A);
		friend istream& operator>>(istream& is, Complex& A);
};

double Complex::getModulus() {
	return (sqrt(real*real+imag*imag));
}

Complex Complex::operator+(Complex &B) {
	Complex C;
	C.real=real+B.real;
	C.imag=imag+B.imag;
	return C;
}

Complex Complex::operator-(Complex &B) {
	Complex C;
	C.real=real-B.real;
	C.imag=imag-B.imag;
	return C;
}

Complex Complex::operator*(Complex &B) {
	Complex C;
	C.real=real*B.real-imag*B.imag;
	C.imag=imag*B.real+real*B.imag;
	return C;
}

Complex Complex::operator/(Complex &B) {
	Complex C;
	double temp=B.real*B.real+B.imag*B.imag;
	C.real=(real*B.real+imag*B.imag)/temp;
	C.imag=(imag*B.real-real*B.imag)/temp;
	return C;
}

ostream& operator<<(ostream& os, const Complex& A) {
	if (A.real==0 && A.imag==0) {
		os<<"0";
		return os;
	}
	if (A.real!=0) {
		os<<A.real;
	}
	if (A.imag!=0) {
		if(A.real!=0 && A.imag>0)
			os<<"+";
		if(A.imag==1) os<<"i";
		else if(A.imag==-1)
			os<<"-i";
		else
			os<<A.imag<<"i";
	}
	return os;
}

bool IsValidNumber(string s) {
	if (s.empty()) return false;
	int dotCount = 0;
	for (int k=0; k < s.length(); k++) {
		if (k==0 && (s[k]=='-' || s[k]=='+'))
			continue;
		if (s[k]=='.') {
			dotCount++;
			if(dotCount>1)
				return false;
		} else if(s[k]<'0' || s[k]>'9') {
			return false;
		}
	}
	return true;
}

istream& operator>>(istream& is, Complex& A) {
	string strPtr;
	if(is.peek()=='\n')
		is.ignore();
	getline(is,strPtr);
	int n=strPtr.length();
	if (n==0) {
		is.setstate(ios::failbit);
		return is;
	}
	int i_pos=-1;
	for (int j=0; j<n; j++) {
		if(strPtr[j]=='i') {
			i_pos =j;
			break;
		}
		char c = strPtr[j];
		if (!((c>='0' && c<='9') || c=='.' || c=='+' || c=='-' || c=='i')) {
			is.setstate(ios::failbit);
			return is;
		}
	}
	if(i_pos!=-1 && i_pos!=n-1) {
		is.setstate(ios::failbit);
		return is;
	}
	if(i_pos==-1) {
		if(IsValidNumber(strPtr)) {
			A.real=atof(strPtr.c_str());
			A.imag=0;
		} else {
			is.setstate(ios::failbit);
		}
	}
	else {
		string temp=strPtr.substr(0, i_pos);
		int splitPos=-1;
		for(int k=temp.length()-1;k>0;k--) {
			if (temp[k]=='+' || temp[k]=='-') {
				splitPos=k;
				break;
			}
		}
		string s_real,s_imag;
		if(splitPos==-1) {
			s_real="0";
			s_imag=temp;
		} else {
			s_real=temp.substr(0, splitPos);
			s_imag=temp.substr(splitPos);
		}
		if(s_real=="" || s_real=="+")
			A.real=0;
		else if(IsValidNumber(s_real))
			A.real=atof(s_real.c_str());
		else
			A.real=0;
		if(s_imag=="" || s_imag=="+")
			A.imag=1;
		else if(s_imag=="-")
			A.imag=-1;
		else if(IsValidNumber(s_imag))
			A.imag=atof(s_imag.c_str());
		else {
			is.setstate(ios::failbit);
		}
	}
	return is;
}

void Input(Complex &A) {
	while(1) {
		cout<<"请输入一个虚数：";
		if(cin>>A) {
			break;
		} else {
			cout<<"\n输入格式错误，请重新输入。\n";
			cin.clear();
		}
	}
}

void menu(Complex &A,Complex &B) {
	cout<<"\n当前A="<<A<<"  B="<<B<<endl;
	cout<<"\n\n1. 修改复数\n";
	cout<<"2. 加法运算\n";
	cout<<"3. 减法运算\n";
	cout<<"4. 乘法运算\n";
	cout<<"5. 除法运算\n";
	cout<<"0. 退出系统\n\n";
}

void Arr(Complex &A,Complex &B) {
	Complex C;
	C=A+B;
	cout<<"("<<A<<")+("<<B<<")="<<C<<endl;
	cout<<"\n加法运算完成。\n";
}

void Sub(Complex &A,Complex &B) {
	Complex C;
	C=A-B;
	cout<<"("<<A<<")-("<<B<<")="<<C<<endl;
	cout<<"\n减法运算完成。\n";
}

void Mul(Complex &A,Complex &B) {
	Complex C;
	C=A*B;
	cout<<"("<<A<<")*("<<B<<")="<<C<<endl;
	cout<<"\n乘法运算完成。\n";
}

void Div(Complex &A,Complex &B) {
	Complex C;
	if(B.getModulus()==0)
		cout<<"该复数不能进行除法运算。\n" ;
	else {
		C=A/B;
		cout<<"("<<A<<")/("<<B<<")="<<C<<endl;
		cout<<"\n除法运算完成。\n";
	}
}

int main() {
	Complex A,B;
	cout<<"所有虚数必须按照a+bi的格式输入，";
	cout<<"如3+5i;-i;5。"<<endl;
	Input(A);
	Input(B);
	while(1) {
		int n;
		menu(A,B);
		if (!(cin>>n)) {
			cout <<"\n输入字符无效，请输入数字。\n";
			cin.clear();
			cin.ignore(1024,'\n');
			system("pause");
			continue;
		}
		switch(n) {
			case 1:
				Input(A);
				Input(B);
				cout<<"虚数修改完成。\n";
				break;
			case 2:
				Arr(A,B);
				break;
			case 3:
				Sub(A,B);
				break;
			case 4:
				Mul(A,B);
				break;
			case 5:
				Div(A,B);
				break;
			case 0:
				cout<<"\n正在退出中...\n";
				system("pause") ;
				return 0;
			default:
				cout<<"\n输入数字无效，请重新输入。\n";
				system("pause");
				break;
		}
	}
	system("pause") ;
	return 0;
}