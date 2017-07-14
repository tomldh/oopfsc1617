#include <iostream>

class Node
{

public:
	Node();
	Node(int val);
	~Node();


	int value;

private:
	Node* prev;
	Node* next;

	friend class List;
};

Node::Node():value(0), prev(0), next(0)
{

}

Node::Node(int val):value(val), prev(0), next(0)
{

}

Node::~Node()
{

	if (!next)
	{
		next = 0;
	}
}

class List
{

public:
	List();
	~List();
	Node* first() const;
	Node* next(const Node* n) const;
	Node* previous(const Node* n) const;
	void append(int i);
	void insert(Node* n, int i);
	void erase(Node* n);

private:
	Node* head;
	Node* tail;

};

List::List(): head(0), tail(0)
{

}

List::~List()
{
	// clear all nodes
	Node *n;

	while(head)
	{
		n = head->next;
		delete head;
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
}

// return a pointer to the first entry
Node* List::first() const
{
	return head;
}

// return a pointer to the node after n
Node* List::next(const Node* n) const
{
	return n->next;
}

// return a pointer to the node after n
Node* List::previous(const Node* n) const
{
	return n->prev;
}

// append a value to the end of the list
void List::append(int i)
{

	Node *node = new Node();
	node->value = i;

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
void List::insert(Node* n, int i)
{

	Node *node = new Node(i);

	if (n->prev)
	{
		n->prev->next = node; // node -1 should point to node
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
void List::erase(Node* n)
{

	if(n->prev) //non-head
	{
		n->prev->next = n->next;
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
			tail = n->prev;
	}

	delete n;
}



int main()
{
	List list;

	list.append(2);
	list.append(3);

	list.insert(list.first(), 1);
	list.insert(list.next(list.first()), 4);

	list.erase(list.first());

	for (Node* n = list.first(); n != 0; n = list.next(n))
			std::cout << n->value << std::endl;

	return 0;
}
