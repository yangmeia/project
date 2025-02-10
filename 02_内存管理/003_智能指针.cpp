#include <iostream>
#include <memory>
#include <vector>

class MyClass : public std::enable_shared_from_this<MyClass>   // enable_shared_from_this 是一个模板类，用于生成一个指向自身的 shared_ptr
{
private:
    int data;

public:
    MyClass(int value) : data(value){
        std::cout << "MyClass 构造函数, data = " << data << std::endl;
    }
    ~MyClass(){
        std::cout << "MyClass 析构函数, data = " << data << std::endl;
    }

    void PrintData(){
        std::cout << "data = " << data << std::endl;
    }

    std::shared_ptr<MyClass> getSharedPtr(){
        return shared_from_this();          //返回一个指向自身的 shared_ptr
    }
};

//自定义删除器
void customDeleter(MyClass* ptr)
{
    std::cout << "自定义删除器被调用" << std::endl;
    delete ptr; //删除对象
}

class MyClass2
{
private:
    int data;

public:

    MyClass2(int value) : data(value){
        std::cout << "MyClass2 构造函数, data = " << data << std::endl;
    }
    ~MyClass2(){
        std::cout << "MyClass2 析构函数, data = " << data << std::endl;
    }

    void PrintData(){
        std::cout << "data = " << data << std::endl;
    }
};



int main(int argc, char const *argv[])
{
    //1.自定义删除器
    //(1)// 使用自定义删除器的 unique_ptr
    std::unique_ptr<MyClass, void(*)(MyClass*)> uptr(new MyClass(10), customDeleter);

    //(2)// 使用自定义删除器的 shared_ptr
    std::shared_ptr<MyClass> sptr(new MyClass(20), customDeleter);


    //2.使用 std::enable_shared_from_this
    //std::enable_shared_from_this 允许一个 std::shared_ptr 从对象内部获取 std::shared_ptr，而不会创建新的引用计数
    std::shared_ptr<MyClass> sptr2 = std::make_shared<MyClass>(30);

    // 从对象内部获取 shared_ptr
    std::shared_ptr<MyClass> sptr3 = sptr2->getSharedPtr();

    //检查引用计数
    std::cout << "sptr2 引用计数: " << sptr2.use_count() << std::endl;
    std::cout << "sptr3 引用计数: " << sptr3.use_count() << std::endl;

    std::cout << "---------------------------------------------------------" << std::endl;


    // 3. 使用 std::shared_ptr 和 std::unique_ptr 的组合
    std::unique_ptr<MyClass2> uptr2 = std::make_unique<MyClass2>(40);
    std::shared_ptr<MyClass2> sptr4 = std::move(uptr2);  // 将 unique_ptr 转换为 shared_ptr

    sptr4->PrintData();  // 使用 shared_ptr 访问对象
    std::cout << "sptr4 的引用计数: " << sptr4.use_count() << std::endl;

    std::unique_ptr<int[]> uptrArray = std::make_unique<int[]>(5);  // 使用 std::make_unique 创建动态数组
    for(int i = 0; i < 5; ++i){
        uptrArray[i] = i;       //初始化数组
    }
    
    std::cout << "uptrArray: ";
    for(int i = 0; i < 5; ++i){
        std::cout << uptrArray[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "---------------------------------------------------------" << std::endl;


    //4. 使用 std::shared_ptr 和 std::weak_ptr 的容器
    /*在某些情况下，你可能需要在一个容器中存储 std::shared_ptr 和 std::weak_ptr，以管理对象的生命周期。*/
    
    // 创建一个 shared_ptr 容器
    std::vector<std::shared_ptr<MyClass2>> sharedPtrContainer;
    sharedPtrContainer.push_back(std::make_shared<MyClass2>(1));    // 创建并添加元素
    sharedPtrContainer.push_back(std::make_shared<MyClass2>(2));

    // 创建一个 weak_ptr 容器
    std::vector<std::weak_ptr<MyClass2>> weakPtrContainer;
    for(const auto& ptr : sharedPtrContainer){
        weakPtrContainer.push_back(ptr);  // 将 shared_ptr 转换为 weak_ptr 并添加到容器中
    }

    // 使用 weak_ptr 访问对象(遍历 weak_ptr 容器并使用 lock() 方法获取 shared_ptr)
    for(const auto& weakPtr : weakPtrContainer) {
        if(auto lockedPtr = weakPtr.lock()) {
            lockedPtr->PrintData();  // 使用 shared_ptr 访问对象
        } else {  // 如果 weak_ptr 已经被释放，则输出错误信息
            std::cout << "Error: weak_ptr has expired." << std::endl;
        }
    }

    //注：sharedPtrContainer 中的对象按其在容器中的顺序被释放。因此，data = 1 的对象先被释放，然后是 data = 2 的对象。




    std::cout << "---------------------------------------------------------" << std::endl;
    return 0;
}
