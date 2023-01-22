#include <concepts>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <type_traits>

template <typename T> concept INumbers = std::is_integral_v<T> || std::is_floating_point_v<T>;

template <INumbers Int, INumbers Float>
struct SetOfThings
{
    Int x{};
    Float y{};

    operator std::string() const;
};

template <typename T> concept LessThan = requires(T a, T b) { 
    { a < b }; 
};

void isLessThan(LessThan auto x, LessThan auto y)
{ return; };

template <INumbers Int, INumbers Float>
SetOfThings<Int, Float>::operator std::string() const {
    return "(" + std::string(std::to_string(this->x)) + "," + std::string(std::to_string(this->y)) + ")";
}

template <INumbers Int, INumbers Float>
inline bool operator <(const SetOfThings<Int, Float>& lhs, const SetOfThings<Int, Float>& rhs){
    return (lhs.x <= rhs.x) && (lhs.y <= rhs.y) ? true: false;
}

template <INumbers Int, INumbers Float>
inline bool operator >(const SetOfThings<Int, Float>& lhs, const SetOfThings<Int, Float>& rhs){
    return (lhs.x >= rhs.x) && (lhs.y >= rhs.y) ? true: false;
}

template <INumbers Int, INumbers Float>
inline std::ostream& operator<<(std::ostream& outStr, const SetOfThings<Int, Float>& rhs)
{
    return outStr << std::string(rhs);
}


int main()
{
    std::vector<SetOfThings<int, float>> array = { {3, 2.4f} ,{2,3}, {4,5}, {8,9} , {4, 6}, {4, 8} };
    std::sort(std::begin(array), std::end(array), [](LessThan auto a, LessThan auto b) { 
        std::cout << "comparing " << a << " and " << b << '\n';
        return  bool{ a < b }; 
    });
    
    for (const auto & item : array) {
        std::cout << item << '\n';
    }

    isLessThan(SetOfThings{2,3}, SetOfThings{5,6}); // this works because LessThen is being use to evaluate if a < b actually can be done
    isLessThan(SetOfThings{7,8}, SetOfThings{5,6}); // this works because LessThen is being use to evaluate if a < b actually can be done - so it doesn't matter if 7 < 5 is false - it can be done
}