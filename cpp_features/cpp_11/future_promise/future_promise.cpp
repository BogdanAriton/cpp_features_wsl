#include <unordered_set>
#include <algorithm>
#include <iostream>
#include <random>
#include <future>

using promiseSet = std::unordered_set<int>;

void make_sorted_random(const size_t num_elems, std::promise<promiseSet>&& retvalue) noexcept {
    std::unordered_set<int> retval;
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<int> dis(0, num_elems-1);

    std::generate_n(std::inserter(retval, retval.end()), num_elems, [&]() { 
        return dis(gen);});

    retvalue.set_value(retval);
};

promiseSet make_sorted_random_future(const size_t num_elems) noexcept {
    promiseSet retval;
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<int> dis(0, num_elems-1);

    std::generate_n(std::inserter(retval, retval.end()), num_elems, [&]() { 
        return dis(gen);});

    return retval;
};




int main() 
{
    std::promise<promiseSet> myPromiseSet;
    std::future<promiseSet> futureSet = myPromiseSet.get_future();

    // starting a sparate thread and also running async
    std::thread myThread(make_sorted_random, 23100023, std::move(myPromiseSet));
    auto ret1 = std::async(std::launch::async, make_sorted_random_future, 21000000);
    auto ret2 = std::async(std::launch::async, make_sorted_random_future, 12500000);

    std::cout << "Waiting for my promise set" << '\n';
    std::cout << "Printing Future Set size.." << futureSet.get().size() << '\n';

    // auto ret3 = std::async(std::launch::async, make_sorted_random_future, 23000000);
    // auto ret4 = std::async(std::launch::async, make_sorted_random_future, 14500000);
    // auto ret5 = std::async(std::launch::deferred, make_sorted_random_future, 24000000);
    // auto ret6 = std::async(std::launch::deferred, make_sorted_random_future, 13500000);

    std::cout \
    << "From async 1" << ret1.get().size() \
    << " vs " \
    << "From async 2" << ret2.get().size() \
    << '\n';

    myThread.join();
}