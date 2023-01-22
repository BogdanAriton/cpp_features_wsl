#include <concepts>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <type_traits>

template <typename T> concept IsNumber = std::is_floating_point_v<T> || std::is_integral_v<T>;

template <IsNumber Number>
struct Aggregate
{
    std::string info{};
    Number value{};

    operator std::string() const;
};

template <IsNumber Number>
Aggregate<Number>::operator std::string() const {
    return "{" + this->info + "," + std::to_string(this->value) + "}";
};

template <IsNumber Number>
inline std::ostream& operator<<(std::ostream& out, const Aggregate<Number> & in) {
    return out << std::string(in);
};

int main()
{
    Aggregate a1{"paco", 2};

    std::cout << a1 << '\n';
}