#include <iostream>
#include <utility> // std::pair
#include <tuple>   // std::tuple
#include <array>

/*结构化绑定是 C++17 引入的一项特性，它允许你将一个复合对象（如std::pair、std::tuple、结构体等）的成员直接解构为多个变量。
 这使得代码更加简洁和易读，尤其是在处理多个返回值或复杂数据结构时。
 1. 基本语法:auto [var1, var2, ...] = compound_object; 其中 compound_object 是一个包含多个元素的对象，var1, var2, ... 是用于存储这些元素的新变量。
 2. 使用场景:std::pair 和 std::tuple, 结构体和类, 数组, STL容器中的元素
 */

/* 注:结构化绑定：使用 auto [var1, var2, ...] = compound_object; 语法，直接将复合对象的成员解构为多个变量。
   std::tie：需要显式地创建一个 std::tuple 来绑定多个引用，并将其赋值给另一个复合对象。*/

std::pair<int, double> getValues()
{
    return {42, 3.14};
 }
 
 struct Point
 {
    int x;
    int y;
 };

int main(int argc, char const *argv[])
{
    // std::pair 的结构化绑定
    std::pair<int, double> p(1, 2.3);
    auto [a, b] = p; // 结构化绑定
    std::cout <<"a: "<< a <<" b: "<< b <<std::endl;

    // std::tuple 的结构化绑定
    std::tuple<int, double, std::string> t(1, 2.3, "hello");
    auto [c, d, e] = t; // 结构化绑定
    // int c;
    // double d;
    // std::string e;
    // std::tie(c, d, e) = t; // tie 函数
    std::cout <<"c: "<< c <<" d: "<< d <<" e: "<< e <<std::endl;

    // 结构体的结构化绑定
    Point point{1, 2};
    auto [x, y] = point; // 结构化绑定
    std::cout <<"x: "<< x <<" y: "<< y <<std::endl;

    // 数组的结构化绑定
    int arr[] = {1, 2, 3};
    auto [a1, a2, a3] = arr; // 结构化绑定
    std::cout <<"a1: "<< a1 <<" a2: "<< a2 <<" a3: "<< a3 <<std::endl;

    // 函数返回多个值
    auto [v1, v2] = getValues();
    std::cout <<"v1: "<< v1 <<" v2: "<< v2 <<std::endl;

    //引用绑定
    auto &[ref1, ref2] = p;
    ref1 = 5;
    ref2 = 6.7;
    std::cout <<"ref1: "<< ref1 <<" ref2: "<< ref2 <<std::endl;

    return 0;
}
