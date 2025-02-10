#include <iostream>
#include <cstring>
#include <string_view>

/*std::string_view 是一个轻量级的类，它只包含一个指向字符数据的指针和长度信息，而不拥有或管理这些数据。
  因此，使用std::string_view 作为函数参数可以避免不必要的字符串复制，特别是在处理大字符串时，性能提升显著。

  它不管理字符串的生命周期，也不复制字符串内容，因此其内存占用非常小。具体来说，std::string_view 通常只包含两个成员：
  指向字符数据的指针 (const char*) 与 字符数据的长度 (size_t)  */


void print_string_view(std::string_view str_view)
{
    std::cout << "String view: " << str_view << std::endl;
    std::cout << "Length: " << str_view.length() << std::endl;
    std::cout << "Data pointer: " << str_view.data() << std::endl;  //返回指向字符串数据的指针()
}

int main(int argc, char const *argv[])
{
    //1.c_str()
    /*返回类型：const char*
      功能：返回一个以空字符（\0）终止的C风格字符串（即字符数组），该数组是 std::string 内容的副本。
      特点：保证返回的字符串是以空字符终止的，因此可以直接用于C库函数或其他需要以空字符终止的字符串的地方。
      适用场景：需要以空字符终止的字符串（如C库函数）*/
    std::string str1 = "hello world";
    const char* cstr = str1.c_str();
    std::cout << "C_style string: " << cstr << std::endl;
    std::cout << "Length (including null terminator): " << strlen(cstr) + 1 << std::endl;


    //2.data()
    /*返回类型：const char*或char*（取决于是否为常量）
      功能：返回一个指向字符数据的指针，该指针指向 std::string 内容的内部缓冲区。该缓冲区不保证以空字符终止。
      特点：返回的指针指向 std::string 内部缓冲区，因此可以直接访问和修改字符串的内容。但是，该缓冲区不保证以空字符终止，因此不能直接用于C库函数或其他需要以空字符终止的字符串的地方。
      适用场景：需要访问原始字符数据，不要求以空字符终止*/
    std::string str2 = "hello world";
    const char* dataPtr = str2.data();
    std::cout << "Raw data: " << dataPtr << std::endl;
    std::cout << "Length (excluding null terminator): " << strlen(dataPtr) << std::endl;
    

    //3.std::string_view类
    /*string_view 基本上就是 const string& 的简单替代品，但不会产生开销。缺少 c_str() 接口，但 data() 是可以用的。
      (1)性能优化：std::string_view 可以显著减少字符串复制的开销，特别是在函数参数传递中。
      (2)接口设计：使用 std::string_view 作为函数参数类型，可以接受多种类型的字符串输入（如 std::string、const char* 等），同时保持接口简洁。
      (3)字符串处理：在需要频繁处理字符串片段的场景中，std::string_view 提供了高效的子串提取和操作能力。*/

    // 从 std::string 构造 std::string_view
    /*创建一个 std::string_view，指向 str 的内容,如果 std::string_view 所引用的字符串数据被释放或失效，std::string_view 将变得无效，使用它可能会导致未定义行为*/
    std::string str = "Hello, World!";
    std::string_view sv1(str);		
    print_string_view(sv1);

    // 从 C风格字符串构造 std::string_view
    const char* cstr2 = "C-style string";
    std::string_view sv2(cstr2);
    print_string_view(sv2);

    //提取子串
    std::string_view sv3 = sv1.substr(0, 5);
    print_string_view(sv3);

    //查找子串
    size_t pos = sv1.find("World");
    if(pos != std::string_view::npos) {   //std::string_view::npos 是一个常量，表示一个无效的位置
        std::cout << "Found 'World' at position " << pos << std::endl;
    }








    return 0;
}
