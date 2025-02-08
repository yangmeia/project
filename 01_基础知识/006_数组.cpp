#include <iostream>
#include <array>
#include <vector>
#include <utility>
#include <optional>
#include <algorithm>    //std::sort
#include <tuple>        //std::tie

// std::array：大小在编译期确定，不能改变。一旦定义了数组的大小，就不能动态调整。元素是连续存储的，并且在栈上分配
// std::vector：大小可以动态调整。可以在运行时增加或减少元素的数量。元素也是连续存储的，但在堆上分配。
// std::pair：存储两个元素，可以是不同的类型。元素是连续存储的，可以在栈上分配。


//使用函数遍历数组
void printVector(const std::vector<int>& vec)   //模板类，只需要指定元素类型（和可选的分配器）。大小是动态的，可以在运行时调整。
{
    for(const auto& elem : vec)
    {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
}

template<size_t N>  //模板函数，可以处理不同大小的 std::array
void Traverse(const std::array<int, N>& arr)    //std::array 是模板类，必须指定大小。要处理不同大小的 std::array，需要使用模板函数。
{
    for(const auto& elem : arr)
    {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
}

// 返回两个值的函数
std::pair<int, double> getValues()
{
    return {42, 3.14};
}

int main(int argc, char const *argv[])
{
    //1.std::array容器
    std::array<int, 3> arr{1, 2, 3};
    int second1 = arr[1];
    int second2 = arr.at(1);     // 使用at()安全地访问第二个元素(可以防止越界)
    int first = arr.front();     // 使用front()访问第一个元素
    int last = arr.back();       // 使用back()访问最后一个元素
    size_t size = arr.size();    // 使用size()获取元素的数量

    // 遍历数组
    std::cout << "Traverse array: ";
    for(const auto& elem : arr)     //elem是循环变量，用于在每次迭代中引用数组或容器中的当前元素。
                                    //const表示elem是一个常量引用，这意味着在循环体内不能修改elem的值。
                                    //auto关键字让编译器自动推导elem的类型。
    {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    Traverse(arr);   // 调用模板函数，自动推导N=3

    
    //2.std::vector容器
    // (1)初始化
    std::vector<int> vec1;  // 创建一个空的vector容器
    std::vector<int> vec2(5,10);  // 创建一个包含5个元素的vector容器，每个元素的值都是10
    std::vector<int> vec3{1,2,3,4,5};  // 创建一个包含5个元素的vector容器，每个元素的值分别是1,2,3,4,5
    std::vector<int> vec4(vec3);       // 创建一个包含vec3中所有元素的vector容器

    // (2)操控元素(增，删）
    std::cout << "Size: " << vec4.size() << ", Capacity: " << vec4.capacity() << std::endl; // 输出vector的大小和容量
    vec4.push_back(6);  // 在vector的末尾添加一个元素
    vec4.pop_back();    // 删除vector的最后一个元素

    vec4.insert(vec4.begin() + 2, 7);  // 在vector的第三个位置插入一个元素,值为7（begin() 和 end()：返回指向首元素和尾后元素的迭代器）
    std::cout << "After insert: ";
    printVector(vec4);
    vec4.erase(vec4.end() - 1);      // 删除vector的倒数第一个元素 (vec4.end() 是尾后迭代器, -0会出现危险)
    std::cout << "After erase: ";
    printVector(vec4);

    std::sort(vec4.begin(), vec4.end());    // 对vector中的元素进行排序(升序)
    std::cout << "After sort: ";
    printVector(vec4);
    vec4.clear();       // 清空vector中的所有元素

    //改，查
    for(auto it = vec3.begin(); it != vec3.end(); ++it) //用迭代器遍历
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    for(auto it = vec3.begin(); it != vec3.end(); ++it)
    {
        *it = 2 * (*it); // 修改元素的值(所有元素*2)
    }

    for(const auto& elem : vec3)    //用引用遍历
    {
        std::cout << elem << " ";
    }
    std::cout << std::endl;


    //（3）内存管理
    /*std::vector 在内部维护一个动态数组，当需要更多空间时会自动重新分配内存。
    为了提高性能，可以使用 reserve() 预先分配足够的内存。*/
    vec1.reserve(10);  // 预先分配10个元素的内存空间
    for(int i = 0; i < 10; ++i)
    {
        vec1.push_back(i);  // 向vector中添加10个元素
    }
    std::cout << "Size: " << vec1.size() << ", Capacity: " << vec1.capacity() << std::endl; // 输出vector的大小和容量


    //3.std::pair容器
    //(1)初始化
    std::pair<int, double> p1{20, 6.28};

    //(2)访问(两个成员变量 first 和 second 来访问其存储的两个元素)
    std::cout << "p1.first: " << p1.first << ", p1.second: " << p1.second << std::endl;

    //(3)解构赋值
    auto p2 = std::make_pair(10, 3.14);
    std::cout << "p2.first: " << p2.first << ", p2.second: " << p2.second << std::endl;
    int a;
    double b;
    std::tie(a,b) = p2; // 将pair的元素解构赋值给a和b
    std::cout << "a: " << a << ", b: " << b << std::endl;

    //(4)比较
    if(p1 < p2) // 比较两个pair的大小
    {
        std::cout << "p1 < p2" << std::endl;
    }

    //(5)返回多个值
    auto values = getValues();
    std::cout << "Returned values: " << values.first << ", " << values.second << std::endl;

    //(6)算法和容器操作
    std::vector<std::pair<int, std::string>> item   //创建包含键值对的 vector
    {
        {1, "apple"},
        {2, "banana"},
        {3, "cherry"}
    };

    std::sort(item.begin(), item.end()); // 按键排序

    for(const auto& pair : item)
    {
        std::cout << "Key:" << pair.first << ", Value: " << pair.second << std::endl;
    }


    //4.std::optional容器
    // (1)初始化
    std::optional<int> opt1; // 创建一个空的optional对象
    std::optional<int> opt2(42); // 创建一个值为42的optional对象
    auto opt3 = std::make_optional(3.14); // 创建一个值为3.14的optional对象

    // (2)访问值

    return 0;
}
