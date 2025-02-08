#include <iostream>

class Enpty
{
private:
    // Enpty() = delete;   //删除默认构造函数（使用他无法创建Enpty对象）

public:
    float X, Y;

    Enpty()      //构造函数, 可以用于初始化该类(里面可以省略，默认为0.0f)
    {
        X = 0.0f;
        Y = 0.0f;
    }

    Enpty(float x, float y)      //函数重载
    {
        X = x;
        Y = y;
    }

    void print()
    {
        std::cout << "X: " << X << " Y: " << Y << std::endl;
    }
};

class Enpty2
{
public:
    float a, b;

    Enpty2()      //构造函数
    {
        a = 0.0f;
        b = 0.0f;
        std::cout << "create Enpty2" << std::endl;
    }

    ~Enpty2()     // 析构函数（析构函数不能带参数，也没有返回值）
    {
        std::cout << "destroy Enpty2" << std::endl;
    }

    void print()
    {
        std::cout << "a: " << a << " b: " << b << std::endl;
    }
};

void Function()
{
    Enpty2 e2;
    e2.print();
    //注：当函数结束，e2对象被销毁，自动调用析构函数（作用域或生命周期结束了）,如果在堆上创建对象，需要手动调用delete
}

int main(int argc, char const *argv[])
{
    // (1)构造函数+函数重载(用于初始化对象)
    Enpty e;
    e.print();
    Enpty e1(1.0f, 2.0f);     //构造函数重载
    e1.print();

    //(2)析构函数(用于销毁对象)
    Function();

    std::cin.get();


    return 0;
}
