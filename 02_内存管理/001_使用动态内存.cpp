#include <iostream>
#include <vector>

#define ROW 3
#define COL 4

class MyClass
{
public:
    MyClass(){
        std::cout << "MyClass()" << std::endl;
    }
    ~MyClass(){
        std::cout << "~MyClass()" << std::endl;
    }

};

int main(int argc, char const *argv[])
{
    //1.new与malloc的区别
    /* new：类型安全：new 是 C++ 的运算符，它不仅分配内存，还会调用对象的构造函数来初始化对象。
            返回类型：返回的是指针类型，且该指针是经过类型检查的。
            异常处理：如果内存分配失败，new 会抛出 std::bad_alloc 异常（除非使用 nothrow 版本）。
      malloc:非类型安全：malloc 是 C 语言中的函数，仅分配内存，不会调用构造函数。
             返回类型：返回 void*，需要显式转换为所需类型。
             错误处理：如果内存分配失败，malloc 会返回 NULL，需要显式判断。*/
    //(1)malloc
    int *m_ptr = (int *)malloc(sizeof(int)); // 分配未初始化的 int 内存
    if(m_ptr == NULL){
        // 处理内存分配失败
    }
    free(m_ptr); // 仅释放内存

    // (2)new
    MyClass* n_ptr = new MyClass();     // 分配并初始化 MyClass 对象
    delete n_ptr; // 释放内存并调用析构函数

    int* n_arr = new int[10]{1,2,3,4,5,6,7,8,9,10}; // 分配并初始化 int 数组

    delete[] n_arr; // 释放数组内存



    //(3)动态分配二维数组（不要用这种）
    int** matrix = new int*[ROW]; // 分配行指针数组

    // 分配每一行的列数组
    for(int i = 0; i < ROW; i++){
        matrix[i] = new int[COL]; 
    }

    //初始化二维数组
    for(int i = 0; i < ROW; i++){
        for(int j = 0; j < COL; j++){
            matrix[i][j] = i * COL + j;
        }
    }

    //输出2维数组
    std::cout << "matrix二维数组:" << std::endl;
    for(int i = 0; i < ROW; i++){
        for(int j = 0; j < COL; j++){
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }

    // 释放每一行
    for(int i = 0; i <ROW; ++i){
        delete[] matrix[i];
    }

    // 释放行指针数组
    delete[] matrix;

    /*注：new 和 delete 必须配对使用，否则会导致内存泄漏, 从上面看出动态分配二维数组很麻烦，
      可以使用 std::vector 简化二维数组管理*/


    //(4)使用 vector 管理二维数组(推荐)
    std::vector<std::vector<int>> matrix2(ROW, std::vector<int>(COL)); // 分配并初始化 ROW 的二维数组

    //初始化二维数组
    for(int i = 0; i < ROW; ++i){
        for(int j = 0; j < COL; ++j){
            matrix2[i][j] = i * COL + j;
        }
    }

    //输出2维数组
    std::cout << "matrix2二维数组:" << std::endl;
    for(int i = 0; i < ROW; ++i){
        for(int j = 0; j < COL; ++j){
            std::cout << matrix2[i][j] << " ";
        }
        std::cout << std::endl;
    }

    // vector 会自动管理内存，无需手动释放

    return 0;
}
