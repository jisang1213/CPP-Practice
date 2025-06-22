#include<iostream>
#include<type_traits>
#include<vector>
#include<tuple>

/*
This file shows how to use template metaprogramming to do work at compile time
*/

using namespace std;

// Recursion with tmp
template<int N>
struct Factorial{
    static constexpr int value = N * Factorial<N-1>::value;
};

// Specialization
template <>
struct Factorial<1>{
    static constexpr int value = 1;
};

// Typetraits
namespace MyTraits{
    struct true_type{
        static constexpr bool value = true;
    };

    struct false_type{
        static constexpr bool value = false;
    };

    template<typename T>
    struct is_pointer : false_type{};
    // Partial specialization 
    template<typename T>
    struct is_pointer<T*> : true_type{};

    template<typename T>
    struct strip_pointer{
        using type = T;
    };
    // Specialization for pointers
    template<typename T>
    struct strip_pointer<T*>{
        using type = T;
    };
}

template<typename T>
void print_value(T arg){
    if constexpr(std::is_pointer_v<T>) {
        cout << "The value pointed to is: " << *arg << endl;
    }
    else{
        cout << "The value is: " << arg << endl;
    }
}

template<bool condition, typename THEN, typename ELSE>
struct if_;

template<typename THEN, typename ELSE>
struct if_<true, THEN, ELSE>{
    using type = THEN;
};

template<typename THEN, typename ELSE>
struct if_<false, THEN, ELSE>{
    using type = ELSE;
};

template<typename SEARCH, typename TUPLE, size_t start_from=0>
struct contains_type : 
    if_<
        std::is_same_v<std::tuple_element_t<start_from, TUPLE>, SEARCH>,
        std::true_type,
        typename if_<
            (start_from == std::tuple_size_v<TUPLE> - 1),
            std::false_type,
            contains_type<SEARCH, TUPLE, start_from + 1>
        >::type
    >::type
{};  

template<typename SEARCH>
struct contains_type<SEARCH, std::tuple<>> : std::false_type{};

template<typename SEARCH, typename TUPLE>
inline constexpr bool contains_type_v = contains_type<SEARCH, TUPLE>::value;

// Variadic templates
void print(){
    cout << '\n';
}
template<typename Last>
void print(Last&& t){
    cout << t << '\n';
}

template<typename T0, typename... T1toN>
void print(T0&& t, T1toN&&... rest){
    cout << std::forward<T0>(t) << '\n';
    print(std::forward<T1toN>(rest)...);
}

// How do we print a tuple with arbitrary number of elements?
template<typename TUPLE, std::size_t... indices>
void print_tuple_impl(TUPLE&& t, std::index_sequence<indices...>){
    print(std::get<indices>(std::forward<TUPLE>(t))...);
}

template<typename TUPLE>
void print_tuple(TUPLE&& t){
    print_tuple_impl(std::forward<TUPLE>(t), std::make_index_sequence<std::tuple_size<std::remove_reference_t<TUPLE>>::value>{});
}

int main(){
    constexpr int N = 10;
    cout << "The factorial of " << N << " is " << Factorial<N>::value << endl;

    cout << std::boolalpha;

    cout << "Is int a pointer? " << MyTraits::is_pointer<int>::value << endl;
    cout << "Is int* a pointer? " << MyTraits::is_pointer<int*>::value << endl;

    int x = 10;
    int *p = &x;

    print_value(x);
    print_value(p);
    cout << "Is pointer? " << MyTraits::is_pointer<MyTraits::strip_pointer<int*>::type>::value << endl;

    cout << "Is same type? " << std::is_same_v<int, if_<(10>5), int, float>::type> << endl;

    std::tuple<int, float, double> tuple;
    cout << "Does tuple contain the int type? " << contains_type_v<int, decltype(tuple)> << endl;
    cout << "Does tuple contain the int type? " << contains_type_v<int, std::tuple<>> << endl;

    print(1.02, false, "hello");
    print_tuple(std::make_tuple("first", "second", "third"));
}