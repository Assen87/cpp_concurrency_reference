#include <cstdio>
#include <thread>
#include <mutex>
#include <vector>
#include <numeric>

// A mutex is a synchronization primitive that locks and unlocks code that is used from several
// threads at the same time. The mutex guarantees that only 1 thread may execute code if that
// thread has the lock on the mutex.

// This function creates 100 threads that pushes a number into a vector
// When all threads are finished, the sum should be 4950, but sometimes it isnt...
void demonstrate_without_mutex()
{
    std::vector<int> numbers;
    std::vector<std::thread> threads;
    for (int i = 0; i < 100; ++i)
    {
        threads.emplace_back([=, &numbers]() {
            numbers.push_back(i);
        });
    }

    for (auto& t : threads) {t.join();}

    int sum = std::accumulate(numbers.begin(), numbers.end(), 0);
    printf("sum is %d but should be %d\n", sum, 4950);
}

// This function does the same but protects access to numbers with a mutex
// Only 1 thread may execute code within mutex.lock() and mutex.unlock() when it owns the mutex
void demonstrate_with_mutex()
{
    std::vector<int> numbers;
    std::mutex mutex;
    std::vector<std::thread> threads;
    for (int i = 0; i < 100; ++i)
    {
        threads.emplace_back(std::thread([=, &numbers, &mutex]() {
            mutex.lock();
            numbers.push_back(i);
            mutex.unlock();
        }));
    }

    for (auto& t : threads) {t.join();}

    auto sum = std::accumulate(numbers.begin(), numbers.end(), static_cast<int>(0));
    printf("sum is %d and should be %d\n", sum, 4950);
}

int main()
{
    demonstrate_without_mutex();
    demonstrate_with_mutex();

    return 0;
}