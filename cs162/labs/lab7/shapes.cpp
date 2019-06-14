#include <iostream>
#include <cmath>


using namespace std;

class shape
{
	protected:
	   	string name;
		string color;
		double area;
	public:	
		/* Mutator */
		virtual void set_name(string n)
		{
			name = n;
		}
		virtual void set_color(string c)
		{
			color = c;
		}
		virtual void set_area() = 0;

		/* Accessor */
		virtual string get_name()
		{
		   	return name;
		}
		virtual string get_color()
		{
		   	return color;
		}
		virtual double get_area()
		{
		return area;
		}
};

class circle : public shape
{
   	private:
	   	double radius;
	public:
		/* Constructor */
		circle(string c, double r)
		{ 
			set_name("Circle");
			set_color(c);
			this -> radius = r;
		}
		/* Mutator */		
		void set_area()
		{
			area = 3.14*(pow(radius,2));
		}
};

class rectangle : public shape
{
   	private:
	   	double width;
		double length;
	public:
		/* Constructor */
		rectangle(string c, double w, double l)
		{
			set_name("Rectangle");
			set_color(c);
			width = w;
			length = l;
		}
		/* Mutator*/ 
		void set_area()
		{
			area = width*length;
		}
};

void print_shape_info(shape *s)
{
   	cout<<endl;
   	cout<<"name: "<<s->get_name()<<endl;
	cout<<"color: "<<s->get_color()<<endl;
	cout<<"area: "<<s->get_area()<<endl;
	cout<<endl;
}

int main()
{
   	int radius, width, length;
	string color;
			
	cout << "Create a Circle" << endl;
	cout << "Enter a color: ";
	cin >> color;
	cout << "Enter radius: ";
	cin >> radius;


	shape *c = new circle(color, radius);
	c->set_area();

	cout << "Create a Rectangle" << endl;
	cout << "Enter a color: ";
	cin >> color;
	cout << "Enter Length: ";
	cin >> length;
	cout << "Enter Width: ";
	cin >> width;

	shape *r = new rectangle(color, length, width);
	r->set_area();

	print_shape_info(c);
	print_shape_info(r);
									
	return 0;
}

