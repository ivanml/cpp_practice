#include <iostream>
#include "print.h"

using namespace std;

class Base {
private:
public:
  Base() { cout << "Base constructed!" << endl; }
  virtual ~Base() { cout << "Base destructed!" << endl; };

  virtual void doSomething() { cout << "Base doing something!" << endl; }
  void NonVirtualFunc() { cout << "Base non virtual func called! " << endl; }
};

class Derived : public Base {
public:
  // BEFORE constructing a Derived object, it will first call Base constructor to create a Base object
  Derived() { cout << "Derived constructed!" << endl; }
  // AFTER destructing a Derived object, it will call Base destructor to destruct the Base object embedded
  virtual ~Derived() { cout << "Derived destructed!" << endl; };

  virtual void doSomething() { cout << "Derived doing something!" << endl; }
  void NonVirtualFunc() { cout << "Derived non virtual func called! " << endl; }
};

int main() {
  /*
    What happens here are:
    1. Derived constructor is called, but it will first call Base constructor
    2. In creating the Base object, Compiler secretly adds a _vptr to Base class,
    also it sees there is a virtual function in Base,
    it goes ahead to set up a vtable for Base which looks like:
    vtable1:
    ---------------|------------------------
    function entry | actual function pointer
    ---------------|------------------------
    ~Base()    |    ~Base()
    ---------------|------------------------
    doSomething()  |    Base::doSomething()
    ---------------|------------------------
    Then make _vptr points to this vtable1.
    Base object creation completes.
    3. In creating the Derived object, Compiler addes the _vptr as a member to Derived
    because it is inherited from Base, also it goes ahead to set up the vtable for
    Derived, it will look like:
    vtable2:
    ---------------|------------------------
    function entry | actual function pointer
    ---------------|------------------------
    ~Base()    |    ~Derived()
    ---------------|------------------------
    doSomething()  |  Derived::doSomething()
    ---------------|------------------------
    Then make _vptr points to this vtable2.
    Because this _vprt is essentially the same _vptr in Base,
    so now when you try to access _vptr in Base, it now points
    to this new vtable2, not the original vtable1 above.
    Derived class creation completes.
    4. A Base type pointer p is created and assigned to points to
    the address of the created Derived object.
  */
  Base *p = new Derived();    // -> prints "Base constructed!" then "Derived constructed!"

  p->NonVirtualFunc();        // because NonVirtualFunc() is not a virtual function, and
                              // p is a Base type pointer, it only sees the NonVirtualFunc() in Base
                              // and prints "Base non virtual func called!"

  p->doSomething();           // because doSomething() is a virtual function, and p is a
                              // Base type pointer, it go follows the _vptr in Base to find the
                              // vtable it points to. As noted above, _vptr points to vtable2, and
                              // it finds that doSomething() points to Derived::doSomething()
                              // and hence prints: "Derived doing something!"

  delete p;                   // because p is a Base type pointer and delete p invokes Base destructor,
                              // but because ~Base() is a virtual function, it follows the _vptr to
                              // vtable2 and finds out that ~Base() points to ~Derived(), so ~Derived()
                              // is invoked, which destructs the Derived object:
                              // -> prints "Derived destructed!"
                              // then, after that, it also destructes the embedded Base object,
                              // which calls ~Base():
                              // -> prints "Base destructed!"

  return 0;
}
