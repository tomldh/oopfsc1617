#include <iostream>
#include <memory>

class Node
{

public:
	Node();
	Node(int val);
	~Node();


	int value;

private:
	//std::shared_ptr<Node> prev;
	std::weak_ptr<Node> prev; // shared pointer that can point to a node
	std::shared_ptr<Node> next;

	friend class List;
};

Node::Node():value(0), prev(std::shared_ptr<Node>(nullptr)), next(nullptr)
{

}

Node::Node(int val):value(val), prev(std::shared_ptr<Node>(nullptr)), next(nullptr)
{

}

Node::~Node()
{

}

class List
{

public:
	List();
	~List();
	std::shared_ptr<Node> first() const;
	std::shared_ptr<Node> next(const std::shared_ptr<Node> n) const;
	std::shared_ptr<Node> previous(const std::shared_ptr<Node> n) const;
	void append(int i);
	void insert(std::shared_ptr<Node> n, int i);
	void erase(std::shared_ptr<Node> n);

private:
	std::shared_ptr<Node> head;
	std::shared_ptr<Node> tail;

};

List::List(): head(nullptr), tail(nullptr)
{

}

List::~List()
{
/*
	// clear all nodes
	std::shared_ptr<Node> n;

	while(head)
	{
		n = head->next;
		head->prev = nullptr;
		head->next = nullptr;
		head = n;

	}

	// set head to NULL
	if (!head)
	{
		head = 0;
	}

	if (!tail)
	{
		tail = 0;
	}
*/
}

// return a pointer to the first entry
std::shared_ptr<Node> List::first() const
{
	return head;
}

// return a pointer to the node after n
std::shared_ptr<Node> List::next(const std::shared_ptr<Node> n) const
{
	return n->next;
}

// return a pointer to the node after n
std::shared_ptr<Node> List::previous(const std::shared_ptr<Node> n) const
{
	return n->prev.lock();
}

// append a value to the end of the list
void List::append(int i)
{

	std::shared_ptr<Node> node = std::make_shared<Node>(i);

	if (!head)
	{
		head = node;
	}

	if (tail)
	{
		node->prev = tail;
		tail->next = node;
	}

	tail = node;

}

// insert a value before n
void List::insert(std::shared_ptr<Node> n, int i)
{

	std::shared_ptr<Node> node = std::make_shared<Node>(i);

	if (n->prev.lock())
	{
		n->prev.lock()->next = node; // node -1 should point to node
		node->prev = n->prev; // node should point to n-1
		n->prev = node; // n should point to node now
		node->next = n; // node should point to n
	}
	else
	{
		if (head == n) // if n has no previous, check if it is head
		{
			node->next = n;
			n->prev = node;
			head = node;
		}
	}

}

// remove n from the list
void List::erase(std::shared_ptr<Node> n)
{

	if(n->prev.lock()) //non-head
	{
		n->prev.lock()->next = n->next;
	}
	else //head
	{
		if (head == n) //ensure n is head
			head = n->next;
	}


	if (n->next) //non-tail
	{
		n->next->prev = n->prev;
	}
	else //tail
	{
		if (tail == n) //ensure n is tail
			tail = n->prev.lock();
	}

}



int main()
{
	List list;

	list.append(2);
	list.append(3);

	list.insert(list.first(), 1);
	list.insert(list.next(list.first()), 4);

	list.erase(list.first());
/*
	for (std::shared_ptr<Node> n = list.first(); n != 0; n = list.next(n))
			std::cout << n->value << std::endl;
*/
	return 0;
}
