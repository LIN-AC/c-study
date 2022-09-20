#ifndef QUEUE_H_
#define QUEUE_H_
class Customer
{
private:
    long arrive_;      //到达时间
    long processtime_; //结束时间
public:
    Customer() { arrive_ = processtime_ = 0; };
    void set(long when);
    long when() const { return arrive_; };
    int ptime() const { return processtime_; };
};

typedef Customer Item;

class Queue
{
private:
    typedef struct Node_s
    {
        Item item;
        struct Node_s *next;
    } Node;
    enum
    {
        Q_SIZE = 10
    };
    Node *front_; //头指针
    Node *rear_;  //尾指针
    int items_;   //计数器
    const int qsize_;
    Queue(const Queue &q) : qsize_(0){};
    Queue &operator=(const Queue &q) { return *this; };

public:
    Queue(int qs = Q_SIZE);
    ~Queue();
    bool isempty() const;
    bool isfull() const;
    int queuecount() const;
    bool enqueue(const Item &item); //入队
    bool dequeue(Item &item);       //出队
};
#endif