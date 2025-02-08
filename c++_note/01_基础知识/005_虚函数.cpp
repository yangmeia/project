#include <iostream>

class Entity
{
public:
    virtual std::string GetName()
    {
        return "Entity";
    }
};

class Player : public Entity
{
private:
    std::string Myname;

public:
  Player(const std::string& name) : Myname(name) // 接受一个字符串参数，用于初始化Myname成员变量。
  {}

    std::string GetName() override 
    {
        return Myname;
    }

};


/*PrintName 函数接受一个 Entity* 类型的指针，并调用 e->GetName()。如果 GetName 不是虚函数，那么即使 e 指向的是 Player
 * 对象，调用的仍然是 Entity 类中的 GetName 函数，而不是 Player 类中的 GetName 函数。*/
void PrintName(Entity* e)
{
    std::cout << e->GetName() << std::endl;
}


int main(int argc, char const *argv[])
{
    //1.虚函数
    Entity *e = new Entity(); // 使用new关键字动态分配内存，需要手动释放内存以避免内存泄漏。
    PrintName(e); // 输出Entity

    Player* p = new Player("Player");   //输出是Entity，而不是Player(这时要要使用虚函数)
    PrintName(p); // 输出Entity

    return 0;
}
