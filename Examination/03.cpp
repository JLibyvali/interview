#include <atomic>
#include <chrono>
#include <future>
#include <iostream>
#include <mutex>
#include <sys/stat.h>
#include <utility>

// 面试题2：实现Singleton模式
// 题目：设计一个类，我们只能生成该类的一个实例。

// Sol 1.
// Scott meyer's local static variable

class Single1
{
public:

    static Single1 &produce()
    {
        static Single1 instance;
        return instance;
    }

private:

    Single1()                         = default;
    ~Single1()                        = default;

    // non copy
    Single1(const Single1 &_src)      = delete;
    Single1 &operator=(Single1 &_lhs) = delete;
};

// Sol. 2
//  C++ memory model atomic require-access
class Single2
{
public:

    static Single2 *produce();

private:

    Single2()                                                    = default;
    ~Single2()                                                   = default;

    // non copy
    Single2(const Single2 &src)                                  = delete;
    Single2                      &operator=(const Single2 &_lhs) = delete;

    static std::mutex             m_mutex;
    static std::atomic<Single2 *> m_instance_ptr;
};

std::mutex             Single2::m_mutex;
std::atomic<Single2 *> Single2::m_instance_ptr;

Single2               *Single2::produce()
{
    Single2 *ins_ptr = m_instance_ptr.load(std::memory_order_acquire);

    if (!ins_ptr)
    {
        std::lock_guard<std::mutex> lock{m_mutex};
        ins_ptr = m_instance_ptr.load(std::memory_order_relaxed);

        if (!ins_ptr)
        {
            ins_ptr = new Single2();
            m_instance_ptr.store(ins_ptr, std::memory_order_release);
        }
    }

    return ins_ptr;
}

template <typename T>
std::chrono::duration<double> getTime()
{
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 10000; i++)
    {
        T::produce();
    }
    return (std::chrono::high_resolution_clock::now() - start);
}

int main()
{

    auto t1    = std::async(std::launch::async, getTime<Single1>);
    auto t2    = std::async(std::launch::async, getTime<Single1>);
    auto t3    = std::async(std::launch::async, getTime<Single1>);
    auto t4    = std::async(std::launch::async, getTime<Single1>);

    auto total = t1.get() + t2.get() + t3.get() + t4.get();
    std::cout << "Time: " << total.count() << std::endl;

    t1    = std::async(std::launch::async, getTime<Single2>);
    t2    = std::async(std::launch::async, getTime<Single2>);
    t3    = std::async(std::launch::async, getTime<Single2>);
    t4    = std::async(std::launch::async, getTime<Single2>);

    total = t1.get() + t2.get() + t3.get() + t4.get();
    std::cout << "Time: " << total.count() << std::endl;

    return 0;
}