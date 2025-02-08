#include <iostream>
#include <unistd.h>

int global_var = 0;

void Increment(int& b)
{
    b++;
}

class Log
{
public:
    // const int log_warning = 0;
    // const int log_error = 1;
    // const int log_info = 2;

    enum Log_Level:unsigned char    //可以不加 :unsigned char (枚举本质是整型)
    {
        log_warning = 0,
        log_error,
        log_info
    };

private:
    Log_Level m_log_level;

public:
    void Log_Level(Log_Level log_level)
    {
        m_log_level = log_level;
    }
    void Log_Warning(const char* message)
    {
        if(m_log_level >= log_warning)
            std::cout << "[WARNING] " << message << std::endl;
    }

    void Log_Error(const char* message)
    {
        if(m_log_level >= log_error)
            std::cout << "[ERROR] " << message << std::endl;
    }

    void Log_Info(const char* message)
    {
        if(m_log_level >= log_info)
            std::cout << "[INFO] " << message << std::endl;
    }

};

class Singlet
{
public:
    static Singlet& Get()
    {
        static Singlet
            instance;       // 它的初始化是在第一次调用Get函数时进行的，这被称为延迟初始化。这种初始化方式确保了单例实例在真正需要时才会被创建，从而提高了性能。
        return instance;    // 返回了instance的引用，而不是副本。这样可以确保调用者获取的是同一个实例，而不是一个新的实例。
    }

    void Hello()
    {
        std::cout << "Hello World!" << std::endl;
    }
};

int main()
{
    // (1)
    std::cout << "Hello World!" << std::endl;
    std::cout << "C++ standard version: " << __cplusplus << std::endl;      // C++ standard version: 201703L

    // (2)引用（引用变量必须总是在创建时被初始化，引用默认是 const）
    int a = 0;
    Increment(a);
    std::cout << a << std::endl;
    ::global_var = 10;  //global variable

    // (3)枚举+类
    Log log;
    log.Log_Level(Log::log_error);
    log.Log_Warning("This is a warning message");
    log.Log_Error("This is an error message");
    log.Log_Info("This is an info message");

    // (4)静态成员函数
    Singlet::Get().Hello();


    return 0;
}