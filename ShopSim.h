//ShopSim.h
#include <iostream>
#include<algorithm>//for min,max function.
#include<string>
#include<fstream>
#include<iomanip>

#define EXPRESS_ITEMS 10
#define LINE_RATE 4
#define EXPRESS_RATE 2

using namespace std;

class Q {
public:
	Q();
	~Q();

	void enQ(int time, string name, int items);
	int deQ(int& time, string& name, int& items);
	int deQEnd(int& time, string& name, int& items);

	int length();
	int time();
	int items();
	void print();

private:
	struct node
	{
		int time;
		string name;
		int items;

		node* next;
		node* prev;
	};
	typedef node* nodePtr;

	node* head;
	node* tail;
	int total;
};

void findShortest(Q& line1, Q& line2, Q& line3, bool& s1, bool& s2, bool& s3);
void findLongest(Q& line1, Q& line2, Q& line3, bool& s1, bool& s2, bool& s3);
void MoveLine(Q& q1, Q& q2);
void PrintAll(Q& q1, Q& q2, Q& q3, Q& q4);