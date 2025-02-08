#include <iostream>

class Entity
{
public:
    float x, y;

    Entity()
    {
        x = 0;
        y = 0;
    }

    void Move(float x, float y)
    {
        this->x += x;    // this是一个隐含的指针，指向调用当前成员函数的对象
        this->y += y;
    }

    void Print()
    {
        std::cout << x << ", " << y << std::endl;
    }
};

class Player : public Entity    //继承(继承父类基础上, 进行扩展)
{
public:
    char * name;
};

int main(int argc, char const *argv[])
{
    //继承
    Player player;
    player.Move(1, 2);
    player.Print();

    return 0;
}
