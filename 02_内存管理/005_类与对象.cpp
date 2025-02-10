#include <iostream>
#include <memory>
#include <vector>

/*类：定义了一种新的数据类型，封装了数据和方法。
  对象：类的实例，可以通过对象访问类的成员变量和成员函数。
  构造函数和析构函数：分别用于初始化和清理对象。
  继承：允许一个类继承另一个类的属性和方法。
  虚函数和多态：允许派生类重写基类的函数，实现多态。
  静态成员：属于类而不是对象的成员，在所有对象之间共享。
  友元函数和友元类：可以访问类的私有和受保护成员。
  运算符重载：允许定义或重新定义运算符的行为。*/

//1.类定义
class Person
{
private:
    std::string name;   //成员变量是类的数据成员，用于存储对象的状态。
    int age;    

public:
    //构造函数:用于初始化对象的状态,它在对象创建时自动调用。
    Person() : name("Unknown"), age(0) { std::cout << "构造函数被调用" << std::endl; }  //默认构造函数
    Person(const std::string& n, int a) : name(n), age(a) { std::cout << "构造函数被调用" << std::endl; }

    //析构函数:用于释放对象占用的资源,它在对象销毁时自动调用。
    ~Person() { std::cout << "析构函数被调用" << std::endl; }

    //成员函数:是类的方法, 用于操作对象的状态,可以访问对象的私有成员。
    void setName(const std::string& n) { name = n; }
    std::string getName() const { return name; }
    void setAge(int a) { age = a; }
    int getAge() const { return age; }

    virtual void printInfo() const  //虚函数:用于实现多态性,可以在派生类中重写。
    {
        std::cout << "Name: " << name << ", Age: " << age << std::endl;
    }
};

//2.类的继承:类的继承允许一个类继承另一个类的属性和方法。继承的类称为派生类，被继承的类称为基类。
/*注：public关键字用于指定继承的访问控制级别。(默认是private)
      当你使用private关键字来继承一个类时，基类的公有成员和保护成员在派生类中变为私有成员，基类的私有成员仍然是私有的。
      当你使用public关键字来继承一个类时，基类的公有成员和保护成员在派生类中仍然是公有的和保护成员，基类的私有成员仍然是私有的。
      当你使用protected关键字来继承一个类时，基类的公有成员和保护成员在派生类中变为保护成员，基类的私有成员仍然是私有的。
*/
//(1)单继承
class Student : public Person
{
private:
    std::string stu_major;

public:
    //构造函数
    Student(const std::string& n, int a, const std::string& m) : Person(n, a), stu_major(m) {}

    //成员函数
    void setMajor(const std::string& m) { stu_major = m; }
    std::string geyMajor() const { return stu_major; }

    //重写基类的成员函数
    void printInfo() const override{
        Person::printInfo();      //调用基类的成员函数(这种做法通常用于在派生类中扩展基类的功能，而不是完全重写基类的功能。)
        std::cout << "Major: " << stu_major << std::endl;
    }

};

class Teacher : public Person
{
private:
    std::string teacher_subject;

public:
    //构造函数
    Teacher(const std::string& n, int a, const std::string& s) : Person(n, a), teacher_subject(s) {}

    //成员函数
    void setSubject(const std::string& s) { teacher_subject = s; }
    std::string getSubject() const { return teacher_subject; }

    //重写基类的成员函数
    void printInfo() const override{
        Person::printInfo();
        std::cout << "Subject: " << teacher_subject << std::endl;
    }
};

//(2)多继承
class Professor  : public Teacher, public Student
{
private:
    int experience;

public:
    //构造函数
    Professor (const std::string& n, int a, const std::string& s, const std::string& m, int e)
    : Teacher(n, a, s), Student(n, a, m), experience(e) {}

    //成员函数
    void setExperience(int e) { experience = e; }
    int getExperience() const { return experience; }

    //重写基类的成员函数
    void printInfo() const override{
        Teacher::printInfo();
        Student::printInfo();
        std::cout << "Experience: " << experience << " years" << std::endl;
    }

};

//2.抽象类(包含纯虚函数的类称为抽象类，不能直接实例化)
class Animal
{
public:
    virtual void makeSound() const = 0; //纯虚函数
    virtual ~Animal() {}
};
class Dog : public Animal
{
public:
    void makeSound() const override {
        std::cout << "Woof! Woof!" << std::endl;
    }
};
class Cat : public Animal
{
public:
    void makeSound() const override{
        std::cout << "Meow! Meow!" << std::endl;
    }
};

//3.静态成员与函数
class Counter
{
private:
    static int count; //静态成员变量（静态成员属于类，而不是类的某个对象）

public:
    Counter() { ++count; }    //构造函数
    ~Counter() { --count; }   //析构函数

    static int getCount() { return count; } //静态成员函数

};

int Counter::count = 0; //静态成员变量初始化

//4.友元函数和友元类(友元函数和友元类可以访问类的私有和受保护成员。)
class Mycalss
{
private:
    int data;

public:
    Mycalss(int d) : data(d) {}

    //声明友元函数
    friend void displayData(const Mycalss& obj); //友元函数

    //声明友元类
    friend class FriendClass;
};

//(1)定义友元函数
void displayData(const Mycalss& obj)
{
    std::cout << "Data: " << obj.data << std::endl;
}

//(2)定义友元类
class FriendClass
{
public:
    void f_displayData(const Mycalss& obj)
    {
        std::cout << "Data: " << obj.data << std::endl;
    }
};


//5.运算符重载
class Complex
{
private:
    double real;   //实部
    double imag;   //虚部

public:
  // 默认参数为 r = 0 和 i = 0，即如果没有提供参数，默认创建一个实部和虚部都为 0 的复数对象。
  Complex(double r = 0, double i = 0) : real(r), imag(i) {}

    //重载加法运算符(成员函数方式重载加法运算符)
    Complex operator+(const Complex& other) const{
        return Complex(real + other.real, imag + other.imag);
    }

    //重载输出运算符(友元函数方式重载输出流运算符)
    /*参数 std::ostream& os 表示输出流对象，const Complex& c 表示要输出的复数对象。
      将复数的实部和虚部格式化后输出到流中。*/
    friend std::ostream& operator<<(std::ostream& os, const Complex& c){
        os << c.real << " + " << c.imag << "i";
        return os;
    }

};

//6.嵌套类
class Outer
{
private:
    int outdata;

public:
    class Inner
    {
    private:
        int innerData;

    public:
        void setInnerData(int d)
        {
            innerData = d;
        }

        int getInnerData()
        {
            return innerData;
        }
    };

    void setOutData(int d)
    {
        outdata = d;
    }

    inline int getOutData()    //内联函数(可以提高性能)
    {
        return outdata;
    }

};




int main(int argc, char const *argv[])
{
    Person p1("Tom", 20);   
    p1.printInfo(); //访问成员:可以通过对象访问类的公共成员变量和成员函数。
    std::cout << "-----------------------------------------------------------" << std::endl;

    //单继承
    Student s1("Jerry", 21, "Computer Science");    
    s1.printInfo();
    std::cout << "-----------------------------------------------------------" << std::endl;

    //多继承
    Professor pro1("John", 30, "Mathematics", "Physics", 10);
    pro1.printInfo();
    std::cout << "-----------------------------------------------------------" << std::endl;

    //多态
    std::vector<std::shared_ptr<Person>> shapes;
    shapes.push_back(std::make_shared<Student>("Alice", 22, "mathematics"));
    shapes.push_back(std::make_shared<Teacher>("Bob", 35, "physics"));

    for(const auto& shape : shapes){
        shape->printInfo();   //多态
    }
    std::cout << "-----------------------------------------------------------" << std::endl;

    /* 注：直接创建对象：适用于简单的、局部的对象管理，性能更好，代码更简洁。
           使用 std::vector 和 std::shared_ptr：适用于需要动态内存管理、共享对象或复杂内存管理策略的场景，可以避免手动管理内存，减少内存泄漏的风险。
           多个 std::shared_ptr 可以共享同一个对象，适合需要共享对象的场景。*/

    //用智能指针管理抽象类
    std::vector<std::shared_ptr<Animal>> animals;
    animals.push_back(std::make_shared<Dog>());
    animals.push_back(std::make_shared<Cat>());

    for(const auto& animal : animals){
        animal->makeSound();    //多态
    }
    std::cout << "-----------------------------------------------------------" << std::endl;


    //类的static
    Counter c1;
    Counter c2;     //static成员变量是类共享的，所有对象访问同一个变量(Counter::count会变为2）
    std::cout << "Count: " << Counter::getCount() << std::endl;     //静态函数可以通过类名访问（Counter::getCount()）
    std::cout << "-----------------------------------------------------------" << std::endl;


    //友元函数与友元类
    Mycalss obj(42);
    displayData(obj);
    FriendClass fc;
    fc.f_displayData(obj);
    std::cout << "-----------------------------------------------------------" << std::endl;


    //重载运算符
    Complex re1(3.0, 4.0);
    Complex re2(1.0, 2.0);
    Complex re3 = re1 + re2;    //使用重载的 + 运算符
    std::cout << re3 << std::endl;           //使用重载的 << 运算符
    std::cout << "-----------------------------------------------------------" << std::endl;

    return 0;
}
