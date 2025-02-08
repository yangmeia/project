#include <iostream>
#include <vector>
#include <typeinfo>

/*auto 关键字允许编译器根据初始化表达式自动推断变量的类型。它简化了代码编写，尤其是在处理复杂类型或模板时非常有用。
  使用 auto 声明的变量必须在声明时进行初始化，否则编译器无法推断其类型。*/

/*decltype 关键字用于从表达式中推断类型，而不进行求值。它特别适用于需要知道表达式类型的场景，例如模板编程
  不需要初始化*/

int main(int argc, char const *argv[])
{
    //1.auto 类型推断
    //简单类型
    auto a = 42;  //int
    auto b = 3.14; //double
    auto c = 'A'; //const char*
    
    // 引用和指针：auto 可以推断出引用和指针类型
    int d = 10;
    auto& ref = d;  // int&
    auto* ptr = &d; // int*

    // 复杂类型
    auto vec = std::vector<int>{1, 2, 3};  // vec 的类型被推断为 std::vector<int>
    auto iter = vec.begin();  // iter 的类型被推断为 std::vector<int>::iterator

    // 输出类型
    std::cout << "vec is of type " << typeid(vec).name() << std::endl;
    std::cout << "iter is of type " << typeid(iter).name() << std::endl;


    //2.decltype 类型推断(关键字 decltype 把表达式作为实参，计算出该表达式的类型)
    //简单类型
    int x = 10;
    decltype(x) y = 20; // y 的类型被推断为 int

    // 复杂类型
    std::vector<int> v1 = {1, 2, 3};
    decltype(v1) v2 = {4, 5, 6}; // v2 的类型被推断为 std::vector<int>

    // 推断返回类型
    auto lambda = [](int x) ->decltype(x){
        return x + 1;
    }; // lambda 的返回类型被推断为 int

    // 输出类型
    std::cout << "y is of type" << typeid(y).name() << std::endl;
    std::cout << "v2 is of type" << typeid(v2).name() << std::endl;
    std::cout << "lambda returns type " << typeid(lambda(0)).name() << std::endl;

    return 0;
}
