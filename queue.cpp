#include <iostream>
using namespace std;

template <typename T>
class Queue
{
private:
    struct Node
    {
        T data;
        Node *next;
        Node(T value) : data(value), next(nullptr) {}
    };

    Node *front; 
    Node *rear;  

public:
    Queue() : front(nullptr), rear(nullptr) {}

    ~Queue()
    {
        while (!isEmpty())
        {
            dequeue();
        }
    }

    void enqueue(T value)
    {
        Node *newNode = new Node(value);
        if (rear == nullptr)
        {
            front = rear = newNode;
        }
        else
        {
            rear->next = newNode;
            rear = newNode;
        }
    }

 
    T dequeue()
    {
        if (isEmpty())
        {
            cout << "Queue is empty, cannot dequeue.\n";
            return T();
        }

        Node *temp = front;
        T data = temp->data;
        front = front->next;

        if (front == nullptr)
        { 
            rear = nullptr;
        }

        delete temp;
        return data;
    }

   
    bool isEmpty() 
    {
        return front == nullptr;
    }
};
