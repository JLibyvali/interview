#include "singleList.h"

#include <chrono>
#include <iostream>
#include <random>
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
    single_list.reverse();
    single_list.print();

    auto test_move = std::move(single_list);
    test_move.print();
}

void double_list_test() {}

int  main()
{
    single_list_test();

    return 0;
}