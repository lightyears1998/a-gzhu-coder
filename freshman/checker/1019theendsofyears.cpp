/* 给The End of Years的C++面向对象例子 */
#include<iostream>
#include<string>

using namespace std;

class Invoice
{
public:

	// 允许无参构造器
	explicit Invoice()
	{
		this->part = "Unknown";
		this->description = "Unknown";
		this->number = 0;
		this->price = 0;
	}

	// 有参构造器
	explicit Invoice(string part, string description, int number, int price)
	{
		this->part = part;
		this->description = description;
		this->number = number;
		this->price = price;
		if(this->number < 0) this->number = 0;
		if(this->price < 0) this->number = 0;
	}

	// 无参方法
	void setpart()
	{
		cout << "Please input the part number: " << endl;
		cin >> part;
	}
	// 有参方法
	void setpart(string part)
	{
		this->part = part;
	}
	string getpart() const
	{
		return part;
	}

	void setdescripyion()
	{
		cout << "Please input the part descripyion: " << endl;
		cin >> description;
	}
	void setdescripyion(string description)
	{
		this->description = description;
	}
	string getdescription() const
	{
		return description;
	}

	void setnumber()
	{
		cout << "Please input the quantity of the item being purchased: "<< endl;
		cin >> number;
		if(number<0) number = 0;
	}
	void setnumber(int number)
	{
		this->number = number;
		if(number<0) number = 0;
	}
	int getnumber() const
	{
		return number;
	}

	void setprice()
	{
		cout << "Please input the price per item: "<<endl;
		cin >> price;
		if(price<0) price = 0;
	}
	void setprice(int price)
	{
		this->price = price;
		if(price<0) price = 0;
	}
	int getprice()
	{
		return price;
	}

	int getInvoiceAmount()
	{
		return price * number;
	}

private:
	string part, description;
	int number, price;
};

int main()
{
	// 无参构造器
	{
		cout << "Example #1:\n";

		Invoice invoice;
		cout << "Part:\t" << invoice.getpart() << endl;
		cout << invoice.getdescription() << endl;
		cout << "Number:\t" << invoice.getnumber() << endl;
		cout << "Price:\t" << invoice.getprice() << endl;
		cout << "Amount:\t" << invoice.getInvoiceAmount() << endl;

		cout << endl;
	}

	// 有参构造器
	{
		cout << "Example #2:\n";

		Invoice invoice("#002", "#002 makes everything possible.", 2, 12);
		cout << "Part:\t" << invoice.getpart() << endl;
		cout << invoice.getdescription() << endl;
		cout << "Number:\t" << invoice.getnumber() << endl;
		cout << "Price:\t" << invoice.getprice() << endl;
		cout << "Amount:\t" << invoice.getInvoiceAmount() << endl;

		cout << endl;
	}

	// 使用无参方法设置成员
	{
		cout << "Example #3:\n";

		Invoice invoice;

		invoice.setpart();
		invoice.setdescripyion();
		invoice.setnumber();
		invoice.setprice();

		cout << "Part:\t" << invoice.getpart() << endl;
		cout << invoice.getdescription() << endl;
		cout << "Number:\t" << invoice.getnumber() << endl;
		cout << "Price:\t" << invoice.getprice() << endl;
		cout << "Amount:\t" << invoice.getInvoiceAmount() << endl;

		cout << endl;
	}

	// 使用有参方法设置成员
	{
		cout << "Example #4:\n";

		Invoice invoice;

		invoice.setpart("#004");
		invoice.setdescripyion("#004 is an important part.");
		invoice.setnumber(12);
		invoice.setprice(3);

		cout << "Part:\t" << invoice.getpart() << endl;
		cout << invoice.getdescription() << endl;
		cout << "Number:\t" << invoice.getnumber() << endl;
		cout << "Price:\t" << invoice.getprice() << endl;
		cout << "Amount:\t" << invoice.getInvoiceAmount() << endl;

		cout << endl;
	}

	return 0;
}
