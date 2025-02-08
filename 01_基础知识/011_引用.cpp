#include <iostream>
#include <vector>

/*引用是一个别名（alias），它绑定到一个已存在的变量，并且可以用来访问该变量的值。
  一旦引用被初始化为某个变量，就不能再绑定到其他变量。
  */

// 1.函数参数传递：避免复制大对象，提高效率
void Print(const std::string& str)  // const引用可以防止修改传入的参数
{
    std::cout << str << std::endl;
}

// 2.返回引用：返回引用可以避免复制，提高效率,特别是在返回类成员或全局变量时。
class Myclass
{
public:
    int& GetRef()
    {
        return m_value;
    }

private:
    int m_value = 10;
};

//3.参数引用：在函数参数中使用引用，可以修改传入的参数的值。
void seprateOddAndEvens(const std::vector<int>& arr, std::vector<int>& odds, std::vector<int>& evens)
{
    // 将一个整数数组中的奇数和偶数分别分离到两个不同的数组中
    for(const auto& i : arr){
        if(i % 2 != 0){
            odds.push_back(i);
        }
        else{
            evens.push_back(i);
        }
    }

}

int main(int argc, char const *argv[])
{
    //(1)
    int a = 10;           // （引用变量必须总是在创建时被初始化，引用默认是 const）
    const int &creaf = a; // cref是一个指向 const int 的引用，不能通过 cref 修改 a 的值
    // creaf = 20; // 错误，不能通过 cref 修改 a 的值

    //(2)
    std::string msg = "Hello, World!";
    Print(msg);     // 不会复制 message，也不会修改它
    //(3)
    Myclass obj;
    obj.GetRef() = 20; // 修改了 obj 的 m_value
    std::cout << obj.GetRef() << std::endl; // 输出 20

    //(4)
    std::vector<int> arr = {1, 2, 3, 4, 5};
    std::vector<int> odds, evens;
    seprateOddAndEvens(arr, odds, evens);

    std::cout << "Odds: ";
    for (const auto& i : odds) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    std::cout << "Evens: ";
    for (const auto& i : evens) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    return 0;
}
