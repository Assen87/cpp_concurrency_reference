#include <cstdio>
#include <thread>
#include <vector>
#include <atomic>


// This function creates 10 threads that increment a variable 10 times each
// When all threads are completed, variable should be 100, but sometimes it isnt...
// When several threads are accessing the same variables and atleast one of them is a write
// operation, the behavior is undefined when no synchronzation is used
int increment_to_100_using_10_threads()
{
    int variable = 0;
    std::vector<std::thread> threads;
    for (int i = 0; i < 10; ++i)
    {
        threads.emplace_back([&]() {
            for (int j = 0; j < 10; ++j)
            {
                variable++;
            }
        });
    }

    for (auto& t : threads)
    {
        t.join();
    }

    return variable;
}

void demonstrate_data_race()
{
    int tries = 1;
    while (true)
    {
        int should_be_100 = increment_to_100_using_10_threads();
        if (should_be_100 != 100)
        {
            printf("Should be 100, but got %d, on try %d\n", should_be_100, tries);
            return;
        }
        tries++;
    }
}

// This function increments to 100 in the same way but the variable is declared atomic
// Atomics can be used on most primitives and acts as a synchronization for that variable
int increment_to_100_using_10_threads_atomic()
{
    std::atomic<int> variable = 0;
    std::vector<std::thread> threads;
    for (int i = 0; i < 10; ++i)
    {
        threads.emplace_back([&]() {
            for (int j = 0; j < 10; ++j)
            {
                variable++;
            }
        });
    }

    for (auto& t : threads)
    {
        t.join();
    }

    return variable;
}

void demonstrate_atomic()
{
    int tries = 0;
    while (tries < 1000)
    {
        int should_be_100 = increment_to_100_using_10_threads_atomic();
        if (should_be_100 != 100)
        {
            printf("Should be 100, but got %d\n", should_be_100);
            return;
        }
        tries++;
    }

    printf("Got 100, 1000 times in a row. It is probably synchronized correctly...\n");
}

int main()
{
    demonstrate_data_race();
    demonstrate_atomic();

    return 0;
}