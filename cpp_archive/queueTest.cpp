#include <iostream>
#include <string>
using namespace std;

class Queue;

template <typename T>
class Node {
	friend class Queue<T>;

public:
	Node() : link(0) {};
	Node(const T&);

private:
	T data;
	Node* link;
};


template <typename T>
Node<T>::Node(const T& _data) {
	this->data = _data;
	link = 0;
};

template <typename T>
class Queue {
	friend osream& operator<<(ostream& os, Queue queue){
		Note<T>* current = queue.head;
		while(current->link != queu.head){
			current = current->link;
			os << current->data << " ";
		}
		os << endl;
		return os;
	};

public:
	Queue();
	void Enqueue(const T&);
	void Dequeue();
	T& Front();
	T& Rear();
	bool isEmpty();

private:
	Node<T>* head;

};

template <typename T>
Queue<T>::Qeueue(){
	head->link = head;
}


template <typename T>
bool Queue<T>::isEmpty(){
	bool is_empty = false;

	if(head->link == head){
		is_empty = true;
		cout << "\t Queue is Empty. " << endl;
	}
	return is_empty;
}

template <typename T>
void Queue<T>::Enqueue(const T& data){
	Node<T>* newNode = new Node<T>(data);

	if(isEmpty()){
		head->link = newNode;
	}
	else{
		Node<T>* current = head;
		while(current->link != head)
			current = current->link;

		current->link = newNode;
	}
	newNode->link = head;
}

template <typename T>



int main(int argc, const char *argv[]){
	

	return 0;
}


