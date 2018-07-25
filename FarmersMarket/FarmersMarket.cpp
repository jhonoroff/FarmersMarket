//////////////////////////////////////////////////////////////////////////////////
//						FarmersMarket.cpp  
//		Defines the entry point for the Farmers Market console application.
//
//	Written by: Joe Honoroff		07/23/2018
//
//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <tchar.h>

#include <iostream>
#include <fstream>
#include <vector>
#include <memory>

#include "Tree.h"

using namespace std;

int main()
{
	Tree tree("Evaluation_Assignment_data.txt");

	int input;
	string itemName;

	cout << "Farmers Market Program Options" << endl;
	cout << "1 Print Tree" << endl;
	cout << "2 Print Leaves" << endl;
	cout << "3 Find [Item Name]" << endl;
	cin >> input;
	
	switch (input)
	{
		case 1 :
			tree.PrintTree();
			break;
		case 2 :
			tree.PrintLeaves();
			break;
		case 3 : 
			cout << "Enter Item name to Find" << endl;
			cin >> itemName;
			tree.Find(itemName);
			break;
		default :
			tree.PrintTree();
	}
	
    return 0;
}

