#include <iostream>
#include <memory> // 包含智能指针的头文件

/*智能指针本身是分配在栈区（stack）的，而不是堆区（heap）。它们用于管理动态分配的内存，但它们本身并不在堆上分配内存。
  当你使用智能指针（如std::unique_ptr、std::shared_ptr等）时，你仍然需要使用new操作符在堆上分配内存。
  智能指针只是封装了这些动态分配的内存，并提供了一种自动释放内存的机制。*/

class MyClass
{
private:
    int data;

public:
    MyClass(int value) : data(value){
        std::cout << "MyClass 构造函数,data = " << data << std::endl;
    }
    ~MyClass(){
        std::cout << "MyClass 析构函数,data = " << data << std::endl;
    }

    void printData(){
        std::cout << "data = " << data << std::endl;
    }
};

class Node
{
// private:

public:
    Node(int value) : data(value) {}
    ~Node() {std::cout << "Node 析构函数,data = " << data << std::endl; }

    std::shared_ptr<Node> next;

    int data;
};

int main(int argc, char const *argv[])
{
    // 1.动态内存分配(使用 new 和 new[] 关键字可以在堆上分配内存)
    int* pInt = new int{10};                 // 分配一个 int 类型的内存，并初始化为 10
    int* pArray = new int[4]{1, 2, 3, 4};    // 分配一个包含 4 个 int 类型的内存，并初始化为 1, 2, 3, 4

    // 2.释放动态内存(使用 delete 和 delete[] 关键字释放动态分配的内存)
    delete pInt;
    delete[] pArray;

    //3.空指针常量（nullptr 是NULL的char* 版本）
    int* p = new int(10);
    delete p;    // 不要再使用 p, 否则会引发未定义行为(仍然指向一个已经被释放的地址)
    p = nullptr;
    if (p != nullptr)
    {
        std::cout << "p is not nullptr:" << *p << std::endl;
    }
    else
    {
        std::cout << "p is nullptr" << std::endl;
    }


    //4.智能指针
    // 4.1 unique_ptr (C++11)
    // unique_ptr 是独占所有权的智能指针，它确保同一时间只有一个 unique_ptr 指向一个给定的对象，当 unique_ptr 被销毁时，它所指向的对象也会被自动删除。
    // unique_ptr 的构造函数是删除的，不能通过拷贝构造函数或赋值操作符创建 unique_ptr 的副本, 但可以通过 std::move 进行移动。
    std::unique_ptr<int> uptr(new int(10));

    // 或者使用 make_unique (推荐)
    std::unique_ptr<int> uptr2 = std::make_unique<int>(10); // 减少内存分配的次数，提高效率
    std::cout << "uptr2:" << *uptr2 << std::endl;

    std::unique_ptr<int> uptr3 = std::move(uptr2); // 移动语义
    if(uptr2 == nullptr)
    {
        std::cout << "uptr2 is nullptr" << std::endl;
    }
    std::cout << "uptr3:" << *uptr3 << std::endl;

    // 4.2 shared_ptr (C++11)
    // shared_ptr 是共享所有权的智能指针，它允许多个 shared_ptr 共享同一个对象，当最后一个 shared_ptr 被销毁时，它所指向的对象也会被自动删除。
    // shared_ptr 的构造函数是删除的，不能通过拷贝构造函数或赋值操作符创建 shared_ptr 的副本。
    std::shared_ptr<MyClass> sptr1 = std::make_shared<MyClass>(10);
    std::shared_ptr<MyClass> sptr2 = sptr1; // 共享所有权
    std::shared_ptr<MyClass> sptr3 = sptr1;

    if(sptr1.use_count() > 1){
        std::cout << "sptr1 and sptr2 share the same object" << std::endl;
    }

    // 检查引用计数（跟踪有多少个 shared_ptr 实例共享同一个对象）
    std::cout << "sptr1 的引用计数: " << sptr1.use_count() << std::endl;
    std::cout << "sptr2 的引用计数: " << sptr2.use_count() << std::endl;
    std::cout << "sptr3 的引用计数: " << sptr3.use_count() << std::endl;

    // 使用其中一个 shared_ptr 调用成员函数
    sptr1->printData();

    // 重置 sptr1，引用计数减1， reset() 方法的作用: 提前释放资源
    /*有时你可能希望在对象生命周期结束之前就释放它所管理的资源。通过调用 reset()，你可以立即解除当前 shared_ptr
      对对象的引用，从而减少引用计数。如果这是最后一个 shared_ptr，那么对象会立即被销毁并释放内存*/
    sptr1.reset();
    std::cout << "After resetting sptr1:" << std::endl;
    std::cout << "sptr2 的引用计数: " << sptr2.use_count() << std::endl;
    std::cout << "sptr3 的引用计数: " << sptr3.use_count() << std::endl;

    // 重置 sptr2 和 sptr3，引用计数变为0，对象被释放
    sptr2.reset();
    sptr3.reset();

    //注：reset可以显示的释放资源，也可以不显示的释放资源，当引用计数为0时，对象会被释放，在这里即是mian 函数结束，对象被释放
    //如果在在这里显示释放，会在这里打印weakPtr 锁定成功,data = 10（析构函数）；否则在最后（main函数结束之后）

    //4.3 weak_ptr (C++11)
    /* (1)weak_ptr 是一种不控制对象生命周期的智能指针，它指向一个由 shared_ptr 管理的对象。weak_ptr 不参与引用计数，因此不会影响对象的生命周期。
       (2)weak_ptr 可以通过 lock() 方法获取一个 shared_ptr，从而访问对象。如果对象已经被销毁，lock() 将返回一个空的 shared_ptr。
       (3)weak_ptr 的主要用途是避免循环引用问题，即两个或多个 shared_ptr 彼此引用对方，导致引用计数无法归零，从而无法释放内存。
       (4)weak_ptr 的另一个用途是作为缓存，它可以在需要时获取对象的 shared_ptr，而不影响对象的生命周期。
       (5)std::weak_ptr 不能直接创建，必须从一个 std::shared_ptr 构造而来。
    */

    // 创建两个节点并形成循环引用（当多个 std::shared_ptr 彼此持有对方时，可能会形成循环引用（circular reference），导致引用计数永远不会降为零，从而无法释放内存，造成内存泄漏。）
    std::shared_ptr<Node> node1 = std::make_shared<Node>(5);
    std::shared_ptr<Node> node2 = std::make_shared<Node>(10);
    node1->next = node2;
    node2->next = node1;

    // 使用 weak_ptr 打破循环引用 (当 node1 和 node2 被销毁时，循环引用不会导致内存泄漏)（std::weak_ptr 不增加引用计数，因此不会阻止对象被销毁。）
    std::weak_ptr<Node> weakPtr = node1;

    // 检查weak_ptr是否有效(使用 lock() 方法可以将 std::weak_ptr 转换为 std::shared_ptr)
    if(auto lockedPttr = weakPtr.lock()){
        std::cout << "weakPtr 锁定成功,data = " << lockedPttr->data << std::endl;
    }
    else{
        std::cout << "weakPtr 锁定失败" << std::endl;
    }

    return 0;
}
