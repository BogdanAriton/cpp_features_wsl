#include <concepts>
#include <type_traits>
#include <iostream>

/* so let's make a function that just calculates the sum on things*/
// template <typename Float, 
//           typename = std::enable_if_t<std::is_floating_point_v<Float>>>
// auto get_value(const Float v1, const Float v2) {
//     return v1 + v2;
// }

/* concepts try to solve this problem in a more elegant manner becasue we specify a new type that will try to satisfy some requirements */
template <typename T> concept FloatConcept = std::is_floating_point_v<T> || std::is_integral_v<T>;

FloatConcept auto get_value(const FloatConcept auto v1, const FloatConcept auto v2) {
    return v1 + v2;
}

int main()
{
    FloatConcept auto const value = get_value(1, 2.2093f);

    std::cout << "print int float = " << value << '\n';
    std::cout << "print " << (std::is_same_v< decltype(get_value(1.5, 2)), decltype(value)> ? "true" : "false") << '\n';
    std::cout << "print double float = " << get_value(1.3, 2.3f) << '\n';
}