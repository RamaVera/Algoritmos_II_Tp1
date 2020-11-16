#ifndef QUEUE_H
#define QUEUE_H
#include <cstddef>

template<typename T>
class Queue
{
    private:
        struct Node{
            T data;
            Node *next;
        };

        Node *frontPtr;
        Node *backPtr;
        int count;

    public:
		Queue();
		~Queue();
		bool isEmpty();
		void enqueue(T data);
		T dequeue();
};

#endif // QUEUE_H 
