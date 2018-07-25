//////////////////////////////////////////////////////////////////////////////////
//							Tree.h  
//				Farmers Market console application.
//
//	Defines a Node and Tree classes.  The three is a N Array tree with a vector as 
//			the Node's children.
//
//	Written by: Joe Honoroff		07/23/2018
//
//////////////////////////////////////////////////////////////////////////////////

#include <fstream>
#include <vector>
#include <deque>
#include <memory>
#include <string>


class Tree;
class Node;
typedef std::shared_ptr<Node> Node_Shared_ptr;


class Node
{
	friend class Tree;
public:

	Node(std::string name);
	virtual ~Node();

	std::string GetName() const;
	void Print(int level);

	void FindChildren(std::string const& name);

protected:

	std::string m_name;
	std::weak_ptr<Node> m_parent;
	std::vector<Node_Shared_ptr> m_children;

};

// Tree Class implements the ITree interface
class Tree
{
public:
	Tree(std::string inFileName);
	virtual ~Tree();

	void PrintLeaves();
	void PrintTree();
	void Find(std::string name);

private:
	
	bool FindChildren(std::shared_ptr<Node> node, std::string name);
	void AddNode(std::shared_ptr<Node> child, std::string childName, std::string parentName);
	void Print(std::shared_ptr<Node> node, int level);


	bool m_bPrintLeavesOnly;
	std::shared_ptr<Node> m_Top;
	std::deque<std::string> m_FindPathDeque;
};
