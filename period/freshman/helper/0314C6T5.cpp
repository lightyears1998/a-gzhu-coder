#include <iostream>
using namespace std;

class Point
{
private:
	double x_, y_;
public:
	Point(double x = 0, double y = 0) 
	{
		x_ = x, y_ = y;
	}
	void print() const
	{
		cout << "(" << x_ << ", " << y_ << ")" << endl; 
	}
};

class Line
{
private:
	double a_, b_;
public:
	Line(double a, double b)
	{
		a_ = a, b_ = b;
	}
	void print() const
	{
		cout << "y=" << a_ << "x+" << b_ << endl;
	}
	double getA() const { return a_; }
	double getB() const { return b_; }
};

class setPoint
{
private:
	Line l1_, l2_;
	Point p_;
public:
	setPoint(const Line &l1, const Line &l2) : l1_(l1), l2_(l2)
	{
		double a1 = l1.getA(), a2 = l2.getA();
		double b1 = l1.getB(), b2 = l2.getB();
		p_ = Point((b2-b1)/(a1-a2), a1*(b2-b1)/(a1-a2)+b1);
	}
	void print() const
	{
		cout << "setPoint: "; 
		p_.print(); 
	}
};

int main()
{
	Line a(2, 1), b(1, 2);
	a.print();
	b.print();
	setPoint ab(a, b);
	ab.print();
}
