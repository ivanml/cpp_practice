#include <iostream>

using namespace std;

#define SIZE 4

template <class T>
class Queue {
 private:
  T arr[SIZE];
  int front;
  int rear;

 public:
  Queue() : front(-1), rear(-1) {}
  void enqueue(T item);
  void dequeue();
  T& offer();
  bool empty() const;
};

template <class T>
void Queue<T>::enqueue(T item) {
  if ((rear + 1) % SIZE == front) {
    cout << "Queue is full!" << endl;
    return;
  } 

  if (empty()) {
    front = 0;
    rear = 0;
  } else {
    rear = (rear + 1) % SIZE;
  }

  arr[rear] = item;
}

template <class T>
void Queue<T>::dequeue() {
  if (empty()) {
    cout << "Queue is empty!" << endl;
    return;
  }

  if (front == rear) { // only one element
    cout << "deleted " << arr[front] << endl;
    front = rear = -1;
  } else {
    cout << "deleted " << arr[front] << endl;
    front = (front + 1) % SIZE;
  }
}

template <class T>
T & Queue<T>::offer() {
  if (empty()) {
    cout << "Queue is empty!" << endl;
  }
  return arr[front];
}

template <class T>
bool Queue<T>::empty() const {
  return (front == -1 && rear == -1);
}

int main() {

  Queue<int> q;

  for (int i = 1; i <= 4; ++ i) {
    cout << q.offer() << endl;
    q.enqueue(i);
  }

  q.dequeue();
  cout << q.offer() << endl;

  q.dequeue();
  cout << q.offer() << endl;

  q.enqueue(18);
  q.dequeue();
  q.dequeue();
  q.dequeue();
  q.dequeue();

  return 0;
}
