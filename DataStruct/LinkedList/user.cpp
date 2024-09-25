#include "singleList.h"

#include <ctime>
#include <exception>
#include <random>

int main()
{
    sList::SList list_1(1);

    int                                num = 100;

    std::random_device                 seeder;
    const auto                         seed{seeder.entropy() ? seeder() : time(nullptr)};
    std::mt19937                       engine(seed);
    std::uniform_int_distribution<int> dis(1, 99);

    auto                               length = list_1.getLen();

    try
    {
        while (num--)
        {
            auto tmp = new sList::node(dis(engine));
            list_1.insert(1, *tmp);
        }

        list_1.print();
    }
    catch (std::exception &ex)
    {
        ex.what();
    }

    return 0;
}