#include "doublyList.h"
#include "instructive.h"
#include "instructive.hpp"
#include "singleList.h"

#include <chrono>
#include <cstdlib>
#include <iostream>
#include <random>
#include <sstream>
#include <utility>
#include <vector>

void single_list_test()
{

    // Generate random num
    /**
     * @brief I. random device as random input to generate seed
     * II. Using an engine to produce
     * II. Using a Generated nums Distribution.
     * III. distribution input a engine value?
     */
    std::random_device rd_device;
    const auto         seed{
        rd_device.entropy() ? rd_device() : std::chrono::high_resolution_clock::now().time_since_epoch().count()
    };
    std::mt19937_64                    rd_engine(seed);
    std::uniform_int_distribution<int> rd_dis(1, 100);

    std::vector<slist::node *>         nodes;
    nodes.reserve(15);

    using namespace slist;
    SList single_list(13);

    for (int i = 0; i < 10; i++)
    {
        nodes.push_back(new node{rd_dis(rd_engine)});
        std::cout << "Node size: " << sizeof(node(1)) << " Bytes." << " Nodes address: " << nodes.back()
                  << " in Heap\n";
        single_list.insert(1, *nodes.back());
    }
    single_list.print();
    std::cout << "#######Test Reverse#########" << std::endl;
    single_list.reverse();
    single_list.print();

    std::cout << "####### Test Move #########" << std::endl;
    auto test_move = std::move(single_list);
    test_move.print();
}

void double_list_test()
{
    using namespace dlist;
    DoubleList         double_list{3};

    std::random_device rd_device;
    const auto         seed{
        rd_device.entropy() ? rd_device() : std::chrono::high_resolution_clock::now().time_since_epoch().count()
    };

    std::mt19937_64                 rd_engine(seed);
    std::uniform_int_distribution<> rd_dis(1, 100);

    std::vector<node *>             nodes;
    nodes.reserve(15);

    for (int i = 0; i < 10; i++)
    {
        nodes.push_back(new node(rd_dis(rd_engine)));
        double_list.insert(*nodes.back(), 1);
    }

    double_list.print();

    std::cout << "############## Test reverse ################" << std::endl;
    double_list.reverse();
    double_list.print();
    std::cout << "############## Test Delete ################" << std::endl;
    double_list.del(5);
    double_list.print();
}

void instructive_list_test()
{
    /**
     * @brief Build a List struct first.
     * Also implement a list in stack
     */
    LIST_HEAD(instructive_list);
    std::vector<data1> data1s;
    std::vector<data2> data2s;
    data1s.reserve(15);
    data2s.reserve(15);

    srand(std::chrono::high_resolution_clock::now().time_since_epoch().count());

    auto print = [&]()
    {
        list_head        *cur = nullptr;
        std::stringstream ss;
        int               idx = 0;
        LIST_for_each(cur, &instructive_list)
        {
            auto *entry = LIST_ENTRY(cur, data1, m_list);
            ss << "{ Index: " << idx++ << " | ID number: " << entry->m_id << " | Address: " << entry << " }";
            ss << "-->";

            if (idx % 3 == 0)
                ss << "\n";
        }
        std::cout << ss.str() << std::endl;
    };

    for (int i = 0; i < 10; i++)
    {
        // build linked list
        data1s.emplace_back();
        data1s.back().m_id = rand();
        data2s.emplace_back();
        data2s.back().m_id = rand();
        insert_after(&instructive_list, &data1s.back().m_list);
    }
    print();
    std::cout << "Changed " << std::endl;
    ins_init(&instructive_list);
    for (auto &ele : data2s)
    {
        insert_after(&instructive_list, &ele.m_list);
    }
    print();

    std::cout << "Test CPP style instructive list" << std::endl;
    using namespace ins_list;

    std::vector<Test> test_vec;
    test_vec.reserve(20);
    auto               head = Test();

    // random num
    std::random_device rd_device;
    auto seed{rd_device.entropy() ? rd_device() : std::chrono::high_resolution_clock::now().time_since_epoch().count()};
    std::mt19937_64                 rd_engine(seed);
    std::uniform_int_distribution<> rd_dis{1, 100};

    for (int i = 0; i < 10; i++)
    {
        test_vec.emplace_back(rd_dis(rd_engine));
        test_vec.back().insert_after(&head);
    }

    head.traverse_print();
}

int main()
{
    std::cout << "Single List \n" << std::endl;
    single_list_test();

    std::cout << "Doubly List \n" << std::endl;
    double_list_test();
    /**
     * @brief Valgrind report
     *==108527== HEAP SUMMARY:
     *==108527==   in use at exit: 0 bytes in 0 blocks
     *==108527==   total heap usage: 42 allocs, 42 frees, 84,687 bytes allocated
     *==108527==
     *==108527==    All heap blocks were freed -- no leaks are possible
     *==108527==
     *==108527== For lists of detected and suppressed errors, rerun with: -s
     *==108527== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
     */

    std::cout << " Test instructive list" << std::endl;
    instructive_list_test();

    return 0;
}