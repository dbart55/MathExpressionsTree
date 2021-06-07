#ifndef __LIST_H__
#define __LIST_H__
using namespace std;
template <typename T>
class List
{
    struct Node
    {
        T data;
        Node *next=nullptr;
        Node(T _data, Node *_next=nullptr)
        {
            data = _data;
            next = _next;
        }
        T getData()
        {
            return data;
        }
        void setData(T &_data)
        {
            data = _data;
        }
        Node *getNext()
        {
            return next;
        }
        void setNext(Node *_next)
        {
            next = _next;
        }
    };
protected:
    Node *head = nullptr;
    Node *tail = nullptr;
public:
    void pushFront(T data);
    void pushBack(T data);
    T popFront();
    T popBack();
    bool isEmpty();
    void print();
};

template <typename T>
bool List<T>::isEmpty()
{
    return head == NULL;
}

template <typename T>
void List<T>::pushFront(T data)
{
    Node *newNode = new Node(data, head);
    if(isEmpty())
    {
        tail = newNode;
    }
    head = newNode;
}

template <typename T>
void List<T>::pushBack(T data)
{
    Node *newNode = new Node(data);
    if(isEmpty())
    {
        head = newNode;
    }
    tail = newNode;
}

template <typename T>
T List<T>::popFront()
{
    T data;
    if(isEmpty())
    {
        throw "The List is empty.";
    }
    else if(head == tail)
    {
        data = head->getData();
        delete(head);
        head = nullptr;
        tail = nullptr;
    }
    else
    {
        Node *temp = head;
        data = head->getData();
        head = head->getNext();
        delete(temp);
    }
    return data;
}

template <typename T>
T List<T>::popBack()
{
    T data;
    if(isEmpty())
    {
        return nullptr;
    }
    else if(head == tail)
    {
        data = head->getData();
        delete(head);
        head = nullptr;
        tail = nullptr;
    }
    else
    {
        Node *temp = head;
        while(temp != NULL && temp->getNext() != tail)
        {
            temp  = temp->getNext();
        }
        temp->setNext(NULL);
        data = tail->getData();
        delete(tail);
        tail = temp;
    }
    return data;
}

template <typename T>
void List<T>::print()
{
    Node *temp = head;
    while(temp != NULL)
    {
        cout<<temp->getData()<<" ";
        temp = temp->getNext();
    }
    cout<<endl;
}

#endif // __LIST_H__
