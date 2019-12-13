// ShopSim.cpp 
// Code By Cory Holt
// October 23, 2019
// Simple store simulation using queues

#include "ShopSim.h"

int main()
{
	//INPUT FILENAME
	string filename;
	cout << "SIMPLE SHOPPING SIM\nCODE BY CORY HOLT" << endl;
	cout << "Enter the name of the .dat file to use: " << endl;
	getline(cin, filename);
	cout << "File to be read is: " << filename << endl;
	//BEGIN FILESTREAM
	ifstream fIn;
	fIn.open(filename);
	if (!fIn)
	{
		cout << "ERROR OPENING FILE. EXITING..." << endl;
		exit(1);
	}
	Q store;
	int time, items;
	string name;
	while (!fIn.eof())
	{
		fIn >> time >> name >> items;
		store.enQ(time, name, items);
	}
	cout << "Beginning Data:" << endl;
	store.print();
	//cout << "Made it" << endl;
	//Create empty queues, two normal, one express
	Q line1, line2, express;
	int simtime = 1;
	int start1 = 0, start2 = 0, startEx = 0; //integers for holding start times of each transaction.
	bool isShort1, isShort2, isShortEx; //Booleans for use with findShortest()
	bool isLong1, isLong2, isLongEx; //Booleans for use with findLongest()

	while ((store.length() != 0) || (line1.length() != 0) || (line2.length() != 0) || (express.length() != 0)) 
	{ //while loop that only loops when there are customers in any queue.
		while (store.time() == simtime)//move customers from store to checkout lines.
		{
			findShortest(line1, line2, express, isShort1, isShort2, isShortEx); //Find shortest lines

			if (isShortEx && store.items() <= EXPRESS_ITEMS) {
				store.deQ(time, name, items);
				express.enQ(time, name, items);
				if (express.length() == 1) startEx = simtime;//If this is the first customer, mark the start time.
			}
			else if (isShort1) {
				store.deQ(time, name, items);
				line1.enQ(time, name, items);
				if (line1.length() == 1) start1 = simtime;
			}
			else if (isShort2) {
				store.deQ(time, name, items);
				line2.enQ(time, name, items);
				if (line2.length() == 1) start2 = simtime;
			}
		}
		//Begin checking if customers may move to an empty line
		while ((line1.length() == 0) || (line2.length() == 0) || (express.length() == 0))//If an empty line currently exists
		{
			findLongest(line1, line2, express, isLong1, isLong2, isLongEx); //Find longest lines
			findShortest(line1, line2, express, isShort1, isShort2, isShortEx); //Find shortest lines

			if (isLong1) {//if line 1 is longest
				if (isShort2) {
					MoveLine(line1, line2);
				}
				else if ((isShortEx) && (line1.length() <= EXPRESS_ITEMS)) {
					MoveLine(line1, express);
				}
			}
			else if (isLong2) {//if line 2 is longest
				if (isShort1) {
					MoveLine(line2, line1);
				}
				else if ((isShortEx) && (line1.length() <= EXPRESS_ITEMS)) {
					MoveLine(line2, express);
				}
			}
			else if (isLongEx) {//if express is longest
				if (isShort1) {
					MoveLine(express, line1);
				}
				else if (isShort2) {
					MoveLine(express, line2);
				}
			}
			else
				break;
		}
		//Begin checking if customers can leave
		if ((simtime - startEx) == (EXPRESS_RATE*express.items())) {
			express.deQ(time, name, items);
			startEx = simtime;
		}
		if ((simtime - start1) == (LINE_RATE * line1.items())) {
			line1.deQ(time, name, items);
			start1 = simtime;
		}
		if ((simtime - start2) == (LINE_RATE * line2.items())) {
			line2.deQ(time, name, items);
			start2 = simtime;
		}
		cout << setfill('-') << setw(20) << "-" << endl;
		cout << "Simulation time: " << simtime << endl;
		cout << setfill('-') << setw(20) << "-" << endl;
		PrintAll(store, line1, line2, express);
		simtime++;
	} //End of while loop
	cout << "\nSimulation complete. All customers have exited the store." << endl;
	exit(1);
}