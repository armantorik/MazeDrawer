
// Definitions
template <class type>
Stack<type>::Stack()
{
	top = NULL;
}

template <class type>
Stack<type>::~Stack()
{
	StackNode<type>* ptr = top;
	StackNode<type>* temp;
	while (ptr != NULL)
	{
		temp = ptr->next;
		delete ptr;
		ptr = temp;
	}
}

template <class type>
void Stack<type>::push(const type& val)
{
	StackNode<type>* newNode;


	newNode = new StackNode<type>(val);


	if (isEmpty())
	{
		top = newNode;
		newNode->next = NULL;
	}
	else
	{
		newNode->next = top;
		top = newNode;
	}
}

template <class type>
void Stack<type>::pop(type& val)
{
	StackNode<type>* temp;

	if (isEmpty())
	{
		cout << "The stack is empty.\n";
	}
	else	// pop value off top of stack
	{
		val = top->value;
		temp = top->next;
		delete top;
		top = temp;
	}
}

template <class type>
bool Stack<type>::isEmpty()
{
	bool status;

	if (top == NULL)
		status = true;
	else
		status = false;

	return status;
}

template <class type>
type Stack<type>::currentCell()
{
	return top;
}

template <class type>
void Stack<type>::clear()
{
	StackNode<type>* ptr;
	while (top != NULL)
	{
		ptr = top->next;
		delete top;
		top = ptr;
	}
}