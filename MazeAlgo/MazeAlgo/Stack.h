#ifndef STACKH
#define STACKH
#include <iostream>
using namespace std;

// Stack Class Declarations	
template <class type>
class Stack
{
	private:
		
		template <class type>
		// LinkedList Declaration
		struct StackNode
		{
			type value;
			StackNode<type>* next;
			StackNode(type v):
				value(v) {}
		};

		StackNode<type>* top;

	public:
		Stack();
		~Stack();
		void push(const type&);
		void pop(type&);
		bool isEmpty();
		type currentCell();
		void clear();
};


#include "Stack.cpp"
#endif