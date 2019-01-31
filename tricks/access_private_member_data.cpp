/*
 * @Author: liuyanan 
 * @Date: 2019-01-31 17:33:30 
 * @Last Modified by: liuyanan
 * @Last Modified time: 2019-01-31 18:42:29
 */


/*
    给定的一个类，在不改变原有类的定义的情况下，如何根据其对象的指针访问它的私有成员
    1. 如果基类有virtual function，那么子类中一定要有virtual function，数据布局才能一致
        1.1 只要保证基类和子类同时有，或同时没哟就行
        1.2 不用管子类是不是overwrite基类的方法，因为对于对象而言
            只是多一个指针的问题
    2. replica中数据成员的顺序必须要和基类中的一直
*/

#include <iostream>
#include <string>

using namespace std;


class Base
{
public:
    Base():_topSecretValue(42) {}

    bool publicBoolValue;
    int publicIntValue;
    string publicStringValue;

private:
    int _topSecretValue;
};

class BaseVirtual
{
public:
    BaseVirtual():_topSecretValue(33) {}

    virtual int VitualFunc() {return 1;}

    bool publicBoolValue;
    int publicIntValue;
    string publicStringValue;

private:
    int _topSecretValue;
};

/*
通过复制一个新类，给这个类添加新方法来获取
NOTE:
    这个纯粹是一个 dirty trick，实际的项目中肯定是不能这么用
*/
class BaseReplica{
public:
    // 没有构造函数
    // SomethingReplica():_topSecretValue(42) {}
    int getTopSecretValue() {return _topSecretValue;}

    virtual int VitualIt() {return 1;}

    bool publicBoolValue;
    int publicIntValue;
    string publicStringValue;

private:
    int _topSecretValue;
};


// 这个更简单，直接把class替换成struct，然后把所有数据成员拷贝过来就行了
struct BaseReplicaST
{
    bool publicBoolValue;
    int publicIntValue;
    string publicStringValue;

    int _topSecretValue;
};

struct BaseVirtualReplicaST
{
    virtual int ReplicaVitualIt() {return 1;}

    bool publicBoolValue;
    int publicIntValue;
    string publicStringValue;

    int _topSecretValue;
};



int main(int argc, char const *argv[])
{
    Base* thing = new Base();

    BaseReplica* replica = reinterpret_cast<BaseReplica*>(thing);
    cout << "access private data by new-class is: " << replica->getTopSecretValue() << endl;

    BaseReplicaST* replica_struct = reinterpret_cast<BaseReplicaST*>(thing);
    cout << "access private data by new-struct is: " << replica_struct->_topSecretValue << endl;
    
    BaseVirtualReplicaST* replica_struct_with_virutal = reinterpret_cast<BaseVirtualReplicaST*>(thing);
    cout << "access private data by new-struct with new virtual function is: " << replica_struct_with_virutal->_topSecretValue << endl;
    



    BaseVirtual* virtualthing = new BaseVirtual();

    BaseReplica* replica2 = reinterpret_cast<BaseReplica*>(virtualthing);
    cout << "(base virtual) access private data by new-class is: " << replica2->getTopSecretValue() << endl;

    BaseReplicaST* replica_struct2 = reinterpret_cast<BaseReplicaST*>(virtualthing);
    cout << "(base virtual) access private data by new-struct is: " << replica_struct2->_topSecretValue << endl;
    
    BaseVirtualReplicaST* replica_struct_with_virutal2 = reinterpret_cast<BaseVirtualReplicaST*>(virtualthing);
    cout << "(base virtual) access private data by new-struct with new virtual function is: " << replica_struct_with_virutal2->_topSecretValue << endl;

    /* 
        NOTE: 基类有virtual，子类应该下移一个指针的长度才行
        这个指针的长度在64位机器上是8字节，然而int在64位机器上是4字节
    */
    
#if 1
    int* p = reinterpret_cast<int*>(replica_struct2);
    static_assert(sizeof(int) == 4);
    p+=2;
#else
    long* p = reinterpret_cast<long*>(replica_struct2);
    static_assert(sizeof(long) == 8);
    p+=1;
#endif
    replica_struct2 = reinterpret_cast<BaseReplicaST*>(p);
    cout << "(base virtual with fix) access private data by new-struct with new virtual function is: " << replica_struct2->_topSecretValue << endl;

    return 0;
}
