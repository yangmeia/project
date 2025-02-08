#include <iostream>
#include <string>

class Person
{
private:
    int age;
    std::string name;

public:
    Person(int a, const std::string& n) : age(a), name(n)   //效率更高：直接初始化成员变量，避免了先调用默认构造函数再赋值的过程。

    {
        // 构造函数体可以为空或包含其他代码
    }

    void PrintInfo() const{
        std::cout << "Name: " << name << ", Age: " << age << std::endl;
    }
};


int main(int argc, char const *argv[])
{
    Person p(20, "Alice"); // 使用初始化列表初始化对象
    p.PrintInfo();
    


    return 0;
}
