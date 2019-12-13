#include "ShopSim.h"


Q::Q() //CONSTRUCTOR FOR QUEUE CLASS
{
	head = NULL;
	tail = NULL;
	total = 0;
}

Q::~Q()
{

	node* temp = tail;
	node* toDelete;
	if (temp != NULL) //CHECK TO MAKE SURE TAIL IS NOT NULL
	{
		while (temp != head) //DELETE FROM TAIL IN.
		{
			toDelete = temp;
			if (temp != NULL)
				temp = temp->prev; //Exception being thrown here
			delete toDelete;
		}
	}
}


void Q::enQ(int time, string name, int items)
{
	node* n = new node;
	n->time = time;
	n->name = name;
	n->next = NULL;//try this
	n->items = items;
	if (head == NULL)
	{
		head = n;
		tail = n;
	}
	else
	{
		node* oldtail = tail;
		oldtail->next = n;
		n->prev = oldtail;
		tail = n;
	}
	total++;
}

int Q::deQ(int& time, string& name, int& items)
{
	node* temp = head;
	if (head == NULL)
	{
		cout << "ERROR: DEQUEUE FROM EMPTY QUEUE" << endl;
		return(1);
	}
	if (head->next != NULL)
	{
		time = temp->time;
		name = temp->name;
		items = temp->items;
		head = head->next;
		head->prev = NULL; //Since it is the head of the line, no one is before.
	}
	else
	{
		time = head->time;
		name = head->name;
		items = head->items;
		head = NULL;
		tail = NULL;
	}
	total--;
	delete temp;
	return(0);
}

int Q::deQEnd(int& time, string& name, int& items) //Remove from end of line
{
	node* temp = tail;
	if (tail == NULL)
	{
		cout << "Error popping from end of queue" << endl;
		return(1);
	}
	if (tail->prev != NULL)
	{
		time = temp->time;
		name = temp->name;
		items = temp->items;
		tail = tail->prev;
		tail->next = NULL;
	}
	else
	{
		time = temp->time;
		name = temp->name;
		items = temp->items;
		tail = NULL;
		head = NULL;
	}
	total--;
	delete temp;
	return(0);
}

int Q::length() //returns total length of queue
{
	return total;
}

int Q::time() //returns the time that the head of the queue enters the sim.
{
	if (head == NULL)
		return(0);
	else
		return(head->time);
}

int Q::items() //returns the number of items at the head of the queue, for determining express or not
{
	if (head == NULL)
		return(0);
	else
		return(head->items);
}

void Q::print() //Prints the queue, somewhat formatted
{
	node* ptr = head;
	while ((ptr != NULL) && (total != 0))
	{
		cout << ptr->time << " " << ptr->name << " " << ptr->items << endl;
		ptr = ptr->next;
	}
}

void findShortest(Q& line1, Q& line2, Q& line3, bool& s1, bool& s2, bool& s3)
{//function that returns by reference a boolean if that line is currently the shortest.
	s1 = s2 = s3 = false;
	int l1, l2, l3;
	l1 = line1.length();
	l2 = line2.length();
	l3 = line3.length();
	int shortest = min(l1, min(l2, l3));
	if (l1 == shortest) s1 = true;
	if (l2 == shortest) s2 = true;
	if (l3 == shortest) s3 = true;
}

void findLongest(Q& line1, Q& line2, Q& line3, bool& s1, bool& s2, bool& s3)
{//function that returns by reference a boolean if that line is currently the longest.
	s1 = s2 = s3 = false;
	int l1, l2, l3;
	l1 = line1.length();
	l2 = line2.length();
	l3 = line3.length();
	int longest = max(l1, max(l2, l3));
	if (longest > 1) {//only use this function if the lines are 2 or above.
		if (l1 == longest) s1 = true;
		if (l2 == longest) s2 = true;
		if (l3 == longest) s3 = true;
	}//otherwise the booleans remain false
}

void MoveLine(Q& q1, Q& q2) { //move one customer from end of q1 to end of q2
	int time, items;
	string name;
	q1.deQEnd(time, name, items);
	q2.enQ(time, name, items);
}

void PrintAll(Q& q1, Q& q2, Q& q3, Q& q4) {
	cout << "STORE: " << endl;
	cout << setfill('*') << setw(10) << "*" << endl;
	q1.print();
	if (q1.length() == 0) cout << "Empty!" << endl;
	cout << setfill('*') << setw(10) << "*" << endl;
	cout << "LINE 1: " << endl;
	cout << setfill('*') << setw(10) << "*" << endl;
	q2.print();
	if (q2.length() == 0) cout << "Empty!" << endl;
	cout << setfill('*') << setw(10) << "*" << endl;
	cout << "LINE 2: " << endl;
	cout << setfill('*') << setw(10) << "*" << endl;
	q3.print();
	if (q3.length() == 0) cout << "Empty!" << endl;
	cout << setfill('*') << setw(10) << "*" << endl;
	cout << "EXPRESS: " << endl;
	cout << setfill('*') << setw(10) << "*" << endl;
	q4.print();
	if (q4.length() == 0) cout << "Empty!" << endl;
	cout << setfill('*') << setw(10) << "*" << endl;
}
