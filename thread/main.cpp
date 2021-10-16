#include <cstdio>
#include <thread>
#include <functional>

// This file demonstrates how threads are created and joined
// Threads require some kind of callable when created. The callable can be of many forms that are
// demonstrated below

// Helper class with a function call operator () and a normal method
class MyClass
{
public:
    MyClass(int value) : value_(value) {}

    void operator()(int a) {printf("MyClass function call operator %d\n", a + value_);}
    void method(int a) {printf("MyClass method %d\n", a - value_);}

private:
    int value_;
};

// Free function doing some kind of work
void do_work(int value)
{
    printf("do_work function %d\n", value);
}


int main()
{
    printf("From main thread - Starting all other threads\n");

    // Creating a thread with a lambda
    // The lambda may take arguments and can capture variables
    int lambda_argument = 1;
    int lambda_capture = 2;
    int lambda_result;
    std::thread lambda_thread([=, &lambda_result](int value) {
        lambda_result = value + lambda_capture;
        printf("Thread started with a lambda, %d\n", lambda_result);
    }, lambda_argument);

    // Creating a thread with an object with a function call operator
    MyClass object(3);
    std::thread function_call_operator_thread(object, 4);

    // Creating a thread using any method of an object as the callable
    std::thread object_method_thread(&MyClass::method, &object, 5);

    // Creating a thread using a free function
    std::thread function_reference_thread(do_work, 6);

    printf("From main thread - All threads started\n");

    // Calling join on a thread will block until that thread has completed
    lambda_thread.join();
    function_call_operator_thread.join();
    object_method_thread.join();
    function_reference_thread.join();

    printf("From main thread - All threads joined\n");
    printf("lambda_result: %d\n", lambda_result);

    return 0;
}