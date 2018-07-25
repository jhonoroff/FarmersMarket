//////////////////////////////////////////////////////////////////////////////////
//							Tree.cpp  
//				Farmers Market console application.
//
//	Contains the implementaitons of class Node and Tree 
//
//	Written by: Joe Honoroff		07/23/2018
//
//////////////////////////////////////////////////////////////////////////////////

#include "Tree.h"
#include <stdio.h>

#include <iostream>
#include <fstream>
#include <string>
#include <deque>

using namespace std;

Node::Node(std::string name)
	: m_name(name)
{
}

Node::~Node()
{
	m_children.clear();
}

string Node::GetName() const
{
	return m_name;
}

void Node::Print(int level)
{
	cout << string(level, '-') << m_name << endl;
}


///////////////////////////////////////////////////////////////////
//			Tree Public Functions

Tree::Tree(string inFileName)
{
	ifstream file(inFileName,  ios::in);
	if (file.is_open())
	{
		string parentName;
		string childName;

		while (!file.eof())
		{
			getline(file, parentName, '|');
			getline(file, childName);

			if (parentName == "")
			{
				m_Top = std::make_shared<Node>(childName);
			}
			else
				AddNode(m_Top, childName, parentName);
		}
	}
}

Tree::~Tree() {};

void Tree::PrintLeaves()
{
	cout << "Print Leaves\n";
	m_bPrintLeavesOnly = true;
	Print(m_Top, 0);
}

void Tree::PrintTree()
{
	cout << "Print Tree\n";
	m_bPrintLeavesOnly = false;
	Print(m_Top, 0);
}

void Tree::Find(string name)
{
	cout << "Find " << name << endl << endl;

	FindChildren(m_Top, name);
	//for (Node* node : m_FindPathQueue)
	while (!m_FindPathDeque.empty())
	{
		cout << m_FindPathDeque.front(); 
		if (m_FindPathDeque.front() != name)
			cout << '-';
		m_FindPathDeque.pop_front();
	}
	cout << endl;
}


/////////////////////////////////////////////////////////////
//			Tree Private/Protected Functions


/////////////////////////////////////////////////////////////
//		Use deque so I can push_back and pop_back here when
//		building it with the result path strings, and pop_front
//		when used in Tree::Find(string) above.
//		
bool Tree::FindChildren(shared_ptr<Node> node, string name)
{
	bool ret = false;
	bool bFound = false;
	if (!node.get())
		return false;
	
	m_FindPathDeque.push_back(node->GetName());

	if (name != node->GetName())
	{
		// Showing use of iterator
		for (vector<Node_Shared_ptr>::const_iterator it = node->m_children.begin(); it != node->m_children.end(); ++it)
		{
			if (*it)
			{		
				bFound = FindChildren((*it), name);
				if (bFound)
					break;
			}
		}
		if (bFound)
			ret = true;
		else
			m_FindPathDeque.pop_back();
	}
	else
	{
		ret = true;
	}
	return ret;
		
}

void Tree::AddNode(shared_ptr<Node> node, string childName, string parentName)
{	
	if (node->GetName() == parentName)
	{
		shared_ptr<Node> childNode = make_shared<Node>(childName);
		childNode->m_parent = node;
		node->m_children.push_back(childNode);
	}
	else
	{	// Showing use of modern range based for
		for (auto& childNode : node->m_children) // easy way to traverse a vector, intead of for (i=0; i<...; i++
			AddNode(childNode, childName, parentName); // search recursively
	}
}


void Tree::Print(shared_ptr<Node> node, int level)
{
	if(!m_bPrintLeavesOnly || node->m_children.empty())
		node->Print(level);
	for (auto& childNode : node->m_children)
		Print(childNode, level + 1);

}





