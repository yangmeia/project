#include <iostream>

/*（1)指针加/减法
    操作：将指针加上一个整数 n，表示将指针移动到下一个 n 个元素的位置。
    语法：ptr + n
    效果：如果 ptr 是 int* 类型，ptr + 1 会将指针移动到下一个 int 类型的位置，即移动 sizeof(int) 个字节。
   (2)两个指针相减
    操作：两个相同类型的指针相减，结果是一个整数，表示两个指针之间的元素个数。
    语法：ptr2 - ptr1
    效果：如果 ptr1 和 ptr2 都是 int* 类型，ptr2 - ptr1 返回 ptr2 和 ptr1 之间的 int 元素个数。
   (3) 指针比较
    操作：比较两个指针是否相等或不相等。
    语法：ptr1 == ptr2, ptr1 != ptr2
    效果：比较两个指针的内存地址是否相同。*/

int main(int argc, char const *argv[])
{
    int arr[5] = {1, 2, 3, 4, 5};

    int *ptr = arr;

    // 指针加法
    std::cout << "Pointer addition:";
    int* ptr2 = ptr + 2;  // 将指针移动到第三个元素的位置
    std::cout << *ptr2 << std::endl;  // 输出 3

    // 指针减法
    std::cout << "Pointer subtraction:";
    int* ptr3 = ptr2 - 2;  // 将指针移动到第一个元素的位置
    std::cout << *ptr3 << std::endl;  // 输出 1

    // 两个指针相减
    std::cout << "Difference between pointers:";
    int diff = ptr2 - ptr; // 计算两个指针之间的元素个数
    std::cout << "ptr2 - ptr = " << diff << std::endl; // 输出 2

    // 指针比较
    std::cout << "Pointer comparison:";
    if (ptr == ptr3) {
        std::cout << "ptr and ptr3 are equal" << std::endl; // 输出 ptr and ptr3 are equal
    }




    
    
    return 0;
}
