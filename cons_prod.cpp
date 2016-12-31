//
//  con_prod.cpp
//  
//
//  Created by Lei Mao on 12/31/16.
//
//

#include <iostream>
#include <thread>
#include <mutex>
#include <string>
#include <sstream>
#include <queue>

using namespace std;

mutex mu;
condition_variable cond;

void safe_print(const string &msg) {
    lock_guard<mutex> guard(mu);
    cout << msg << endl;
    // RAII: guard automatically unlocks the mutex when it goes out of scope
}

string threadInfo() {
    stringstream ss;
    ss << "Thread " << this_thread::get_id() << " running.";
    return ss.str();
}

void produce(queue<int> * q, const int num) {
    safe_print("Producer: " + threadInfo());
    // produce i items
    int i = num;
    while (i) {
        unique_lock<mutex> locker(mu);
        q->push(i);
        locker.unlock();
        safe_print("\tproduced item " + to_string(i));
        i --;
        cond.notify_one(); // wake up one thread that is waiting
        this_thread::sleep_for(chrono::milliseconds(100));
    }
    safe_print("Producer finished, " + to_string(num) + " items produced.");
}

void consume(queue<int> * q) {
    safe_print("Consumer " + threadInfo());
    int i = 0;
    int cur = -1;
    while (cur != 1) {
        unique_lock<mutex> locker(mu);
        // put this thread into sleep until being notified by other thread
        // needs the locker as parameter so this thread will unlock it before goes to sleep
        // and once being waked up, it will lock again before accessing the shared queue
        // needs the lambda function to enforce "go back to sleep in case of spurious wake up
        // (and found that the queue is empty)."
        cond.wait(locker, [&](){ return !q->empty(); });
        // woke up, process data
        cur = q->front();
        q->pop();
        locker.unlock();
        i ++;
        safe_print("\tconsumed item " + to_string(cur));
    }
    safe_print("Consumer finished, " + to_string(i) + " items consumed.");
}

int main() {
    queue<int> q; // shared queue
    
    safe_print("spawning producer thread...");
    thread prod(produce, &q, 30); // must pass q as a pointer, because std::thread takes all params by value
    safe_print("spawning consumer thread...");
    thread cons(consume, &q);
    
    prod.join();
    cons.join();
    
    return 0;
}



/////////////////////////////////////////////////

/*
 
//
    Classic Producer, in pair with Classic Consumer
//
void produceClassic(queue<int> * q, const int num) {
    safe_print("Producer: " + threadInfo());
    // produce i items
    int i = num;
    while (i) {
        unique_lock<mutex> locker(mu);
        q->push(i);
        locker.unlock();
        safe_print("\tproduced item " + to_string(i));
        i --;
        this_thread::sleep_for(chrono::milliseconds(200));
    }
    safe_print("Producer finished, " + to_string(num) + " items produced.");
}

//
    Classic Consumer, sleep and check method,
    works but hard to determine how long
    to sleep for, if too short, it loops a lot;
    if too long, wasting opportunity to consume item.
    To solve this, use condition_variable.
//
void consumeClassic(queue<int> * q) {
    safe_print("Consumer: " + threadInfo());
    int cur = -1;
    int i = 0; // item consumed
    while (cur != 1) {
        // consuming items from queue if it is not empty
        // otherwise, sleep and check again later
        unique_lock<mutex> locker(mu);
        if (q->empty()) {
            locker.unlock();
            this_thread::sleep_for(chrono::milliseconds(200));
        } else {
            cur = q->front();
            q->pop();
            locker.unlock();
            i ++;
            safe_print("\tconsumed item " + to_string(cur));
        }
    }
    safe_print("Consumer finished, " + to_string(i) + " items consumed.");
}

*/
