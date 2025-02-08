#include <iostream>
#include <vector>

/*提供一种一致的方式来初始化各种类型的对象。它使用大括号 {} 来进行初始化，可以用于类、数组、基本类型等，
  并且在某些情况下可以避免窄化转换（narrowing conversion）。
  语法形式:Type variable {initializer}; 或者对于函数参数：Type function(Type parameter {initializer});
*/

// 注：统一初始化与初始化列表结合在构造函数中，你可以结合使用统一初始化和初始化列表来初始化成员变量：

class Person
{
  private:
    std::string name;
    int age;

  public:
    Person(std::string n, int a) : name{n}, age{a}
    {
    }
};

int main(int argc, char const *argv[])
{
    //1.基本类型
    int a {10};  //等价于int a = 10;
    double b {3.14};  //等价于double b = 3.14;
    std::string s {"Hello"};  //等价于std::string s = "Hello";
    // int i{3.14}; // 编译错误：从 double 到 int 的窄化转换

    //2.容器
    std::vector<int> v {1, 2, 3, 4, 5};  //等价于std::vector<int> v = {1, 2, 3, 4, 5};

    // 3.构造函数
    Person p {"John", 30};


    return 0;
}
