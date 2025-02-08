#include <iostream>
#include <stdexcept>

/*合法使用场景：const_cast 的合法使用场景之一是当你有一个函数需要一个非 const 参数，
  但你有一个 const对象，并且你知道这个对象实际上是可以被修改的。*/

/*异常处理是C++中用于处理程序运行时错误的一种机制。它允许程序在遇到错误时，以一种受控的方式进行处理，而不是简单地崩溃或终止。
  C++提供了 try、catch 和 throw 关键字来实现异常处理*/

/* 注：尽量少用异常：异常处理有性能开销，应仅用于处理真正异常的情况，而不应用于控制流。
    使用标准库异常类：尽量使用标准库提供的异常类（如 std::runtime_error、std::logic_error 等），除非有特殊需求。
    提供有意义的错误信息：在抛出异常时，提供详细的错误信息，有助于调试和理解问题。
    避免捕获所有异常：尽量避免使用 catch (...)
    捕获所有异常，除非你确实需要处理所有类型的异常。通常应该捕获具体的异常类型。*/

// 当执行 throw 行时，函数将立刻结束而不会返回值，并且控制权将转移到与 throw 语句匹配的最近的 catch 块。
void functionThatMightThrow(int type)
{
    if (type == 1)
    {
        throw std::runtime_error("Runtime error");	// throw expression: expression 是要抛出的异常对象，可以是任何类型（通常是类对象或内置类型）
    }
    else if (type == 2)
    {
        throw std::logic_error("Logic error");
    }
}

class MyException : public std::exception
{
public:
	const char* what() const noexcept override{
		return "MyException";
	}
};

void throwError()
{
	throw MyException();	
}

int main(int argc, char const *argv[])
{
	//1.const_cast 常用于函数参数的转换
    //(1)删除const属性
    const int a = 10;
    int *p = const_cast<int*>(&a); // 去掉const属性
    // 注意：通过 p 修改 a 的值会导致未定义行为
    // *p = 20;  // 不推荐，可能导致未定义行为

    //(2)
    const volatile int cv = 40;
    int *cvp = const_cast<int *>(&cv); // 同时移除 const 和 volatile 限定符

    //(3)添加const属性
    int b = 20;
    const int *cp = const_cast<const int *>(&b);


	//2.异常处理
    try
    {
        functionThatMightThrow(1);	// 可能抛出异常的代码
        functionThatMightThrow(3);
    }
    catch (const std::runtime_error &e)
    {
        std::cout << "Caught a runtime_error: " << e.what() << std::endl;	// 处理 ExceptionType 类型的异常
    }
    catch (const std::logic_error &e)
    {
        std::cout << "Caught a logic_error: " << e.what() << std::endl;
    }
    catch (...)
    {
        std::cout << "Caught an unknown exception" << std::endl;
    }

	try{
		throwError();
	}
    catch(const MyException& e){
        std::cout << "Caught my custom exception: " << e.what() << std::endl;
    }
    catch(...){
		std::cout << "Caught an unknown exception" << std::endl;
	}







    return 0;
}
