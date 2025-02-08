#include <iostream>
#include <string>

/*动态字符串通常指的是可以在运行时动态调整大小的字符串。
  标准库提供了 std::string类来处理动态字符串，它比传统的C风格字符数组（如 char[]）更加灵活和安全。
  常用操作包含：创建、初始化、获取长度、访问字符、连接、查找、替换、插入、删除、子串提取、比较和清空等*/

int main(int argc, char const *argv[])
{
    std::string str1("Hello");  // 使用字符串字面量初始化

    std::string str2 = str1; // 复制 str1 到 str2
    // std::string str2(str1); // 使用拷贝构造函数初始化 str2

    //获取长度(length与size)
    std::cout << "str1 length: " << str1.length() << std::endl;
    std::cout << "str1 size: " << str1.size() << std::endl;

    // 访问字符(at与[])
    std::cout << "str1[0]: " << str1[0] << std::endl;
    std::cout << "str1.at(0): " << str1.at(0) << std::endl;

    //拼接字符(+= 与 append)
    str1 += " C++";
    str1.append("!"); // append 方法可以接受一个字符串或字符数组
    std::cout << "Connected str1:" << str1 << std::endl;

    // 插入字符(insert)
    str1.insert(6, "my "); // 在位置 6 插入 "my "
    std::cout << "After Inserted str1: " << str1 << std::endl;

    //查找字符(find, rfind, find_first_of, find_last_of)
    size_t found = str1.find("C++");    // find 方法查找子字符串在字符串中的第一次出现位置。(found = 6)
    if(found != std::string::npos) {
        std::cout << "Found C++ at position: " << found << std::endl;   // std::string::npos是一个常量，表示查找失败时的返回值, npos 表示找不到
    }

    //提取字符(substr)
    std::string str3 = str1.substr(0, 5); // 提取从位置 0 开始的 5 个字符
    std::cout << "str3: " << str3 << std::endl;

    //比较字符(compare)
    // compare 方法比较两个字符串，有两种方法：compare(str) 和 compare(pos1, n1, str)。
    if(str1.compare(0, 2, str3) == 0) {
        std::cout << "str1 and str3 are equal." << std::endl;
    }
    else{
        std::cout << "str1 and str3 are not equal." << std::endl;
    }

    //替换字符(replace)
    str1.replace(6, 2, "i"); // 将位置 6 开始的 2 个字符替换为 "i"(即将 "my" 替换为 "i")
    std::cout << "After replaced str1: " << str1 << std::endl;

    //删除字符(erase)
    str1.erase(6, 1); // 删除位置 6 开始的 1 个字符
    std::cout << "After erased str1: " << str1 << std::endl;


    str1.clear(); // 清空字符串
    std::cout << "After cleared str1: " << str1 << std::endl;


    return 0;
}
