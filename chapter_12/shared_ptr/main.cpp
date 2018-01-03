#include <iostream>
#include <vector>
#include <memory>
#include <string>

using namespace std;

int main(int argc, char* argv[])
{
    cout << "Hello world!" << endl;
    return 0;
}

//ͨ��make_shared��ʽ��������ָ��
void test_sharedptr(void)
{
    auto p3 = make_shared<int>(42);
    auto p4 = make_shared<string>(10,'9');
    auto p5 = make_shared<int>();
    auto p6 = make_shared<string>("999");
    auto p7(p6);
}
class StrBlobPtr;

//��װһ���࣬��������ʹ������ָ��
class StrBlob{
    friend class StrBlobPtr;
public:
    using size_type = std::vector<std::string>::size_type;
    //���캯��
    StrBlob(): data(make_shared<std::vector<std::string>>()){}
    StrBlob(std::initializer_list<std::string> i1): data(make_shared<std::vector<std::string>>(i1)) { }

    //��Ա����
    size_type size() const { return data->size(); }
    bool empty() const { return data->empty(); }
    // ��Ӻ�ɾ��Ԫ��
    void push_back(const std::string &t) { data->push_back(t); }
    void pop_back();

    // Ԫ�ط���
    std::string& front() const;
    std::string& back();

    StrBlobPtr begin();
    StrBlobPtr end();

private:
    std::shared_ptr<std::vector<std::string>> data;     //����һ������ָ��
    void check(size_type i, const std::string &msg) const{
        if(i >= data->size())
            throw out_of_range(msg);
    }
};

//��������ȥ���������������ĳ�Ա����
void StrBlob::pop_back()
{
    check(0, "pop_back on empty StrBlob");
    data->pop_back();
}

string& StrBlob::front() const
{
    check(0, "front on empty StrBlob");
    return data->front();
}
string& StrBlob::back()
{
    check(0, "back on empty StrBlob");
    return data->back();
}

// new ��ʼ��
void testNewInit(void)
{
    StrBlob obj;
    auto p1 = new auto(obj);
}

// new ʧ��
void newFail(void)
{
    int *p1 = new int;              // �������ʧ�� new �׳� std::bad_allow
    // ��λ new (placement new)
    int *p2 = new (nothrow) int;    // ʧ�� ���� ��ָ��
}

// shared_ptr �� new ���ʹ��
shared_ptr<int> mixShared(void)
{
//    shared_ptr<int> p1 = new int(1024); // ������ʽת��ʧ��
    shared_ptr<int> p2(new int(1024));  // ����ֱ�ӳ�ʼ��

//    return new int(1024); // ����ԭ��ͬ p1
    return shared_ptr<int>(new int(1024));
}

// ��Ҫʹ�� get ��ʼ����һ������ָ�� or  ������ָ�븳ֵ
void getFault(void)
{
    shared_ptr<int> p(new int(42));
    // ��ȷ����ʹ�� q ʱҪע�⣬��Ҫ���������ָ�뱻�ͷ�
    int *q = p.get();
    {
        // δ���壺���������� shared_ptr ָ����ͬ���ڴ�
        shared_ptr<int>(q);
    }   // ����������q �����٣���ָ����ڴ汻�ͷ�
    int foo = *p;   // p ָ����ڴ��Ѿ����ͷ���
}

// ���� shared_ptr ����
void otherSharedOp(void)
{
    shared_ptr<int> p;
    p.reset(new int(1024));

    shared_ptr<string> p2;
    if(!p2.unique())
        p2.reset(new string(*p2));  // ���ǲ���Ψһ
    // �û��������µĿ���
//    *p2 += newVal;
}

// ����ָ����쳣
void f()
{
    shared_ptr<int> sp(new int(42));
    // ��δ����׳�һ���쳣������f��δ��catch
}   // ��������ʱ shared_ptr �Զ��ͷ��ڴ�
// ʹ���Զ����ͷŲ���


// unique_ptr
// ��֧����ͨ�Ŀ��� or ��ֵ
void uniqueOp()
{
//    unique_ptr<T, D> u(d);
    // d ��� delete������Ϊ D
//    u.release();  //  ��������Ȩ������ָ��
    // ���ÿ� u��
    // ������ ��Դû�б� delete����Ҫ�û� delete

    // p1 ת�Ƹ� p2, p1 �ÿ�
    unique_ptr<string> p1(new string("abc"));
    unique_ptr<string> p2(p1.release());
//    auto p3(p2.release());
    p1.reset(p2.release());
}
// ��ֹ����������
unique_ptr<int> clone(int p)
{
    // ���� or ��ֵһ����Ҫ�����ٵ� unique_ptr
    return unique_ptr<int>(new int(p));
    // �ֲ���������
    // ����һ������� "����"
}

// weak_ptr ������
// weak_ptr<T> w(sp)    sp ���� shared_ptr
// w = p    p ������shared_ptr or weak_ptr
// w.expired()  return w.use_count() == 0
// w.lock()
void weakLock()
{
    auto p = make_shared<int>(42);
    weak_ptr<int> wp(p);
    if (shared_ptr<int> np = wp.lock()) {
        // �� if �У�np �� p �������
    }
}
// ����ָ����
class StrBlobPtr {
public:
    StrBlobPtr() : curr(0) { }
    StrBlobPtr(StrBlob &a, size_t sz = 0):
        wptr(a.data), curr(sz) { }
    std::string& deref() const {
        auto p = check(curr, "dereference past end");
        return (*p)[curr];  //  (*p)�Ƕ�����ָ���vector
    }
    StrBlobPtr& incr() { // ǰ׺����
        check(curr, "increment pas end of StrBlobPtr");
        ++curr; //  �ƽ���ǰλ��
        return *this;
    }

private:
    std::shared_ptr<std::vector<std::string>>
        check(std::size_t i, const std::string &msg) const {
        auto ret = wptr.lock(); //  vector ����������
        if (!ret)
            throw std::runtime_error("unboud StrBlobPtr");
        if (i >= ret->size())
            throw std::out_of_range(msg);
        return ret; //  ���򣬷���ָ��vecotr��shared_ptr
    }
    std::weak_ptr<std::vector<std::string>> wptr;
    std::size_t curr;
};

StrBlobPtr StrBlob::begin()
{
    return StrBlobPtr(*this);
}
StrBlobPtr StrBlob::end()
{
    return StrBlobPtr(*this, data->size());
}

// 12.2 ��̬���� new
// delete[] obj ����������

// ����ָ�� �� ��̬����
void SmartPtrAndNew()
{
    unique_ptr<int[]> up(new int[10]);
//    up.release();   //  �Զ��� delete[] ������ָ��
    // P425 ���� ? release �����ٹ���?
    for (size_t i = 0; i < 10; ++i)
        up[i] = i;  //  Ϊÿ��Ԫ�ظ���һ����ֵ

    // shared_ptr ��֧��ֱ�ӹ���̬����
    // if want �����ṩ�Լ������ɾ����
    auto deleter = [](int *p) { delete[] p; };
    shared_ptr<int> sp(new int[10], deleter);
//    sp.reset();
    // Ĭ�� delete�������� delete[]

    // shared_ptr δ�����±�����������Ҳ�֧��ָ�����������
    for (size_t i = 0; i < 10; ++i)
        *(sp.get() + i) = i;
}

// allocator ��  ������memory��
//allocator<string> alloc;          //  ���Է��� string �� allocator ����
//auto const p = alloc.allocate(n); // ���� n ��δ��ʼ���� string��ֻ�������ڴ�
void startAllocator()
{
    allocator<string> a;
    auto const p = a.allocate(4);
    auto q = p;
    // construct �������
    a.construct(q++);           //  *q Ϊ���ַ���
    a.construct(q++, 10, 'c');
    a.construct(q++, "hi");

    // �û�������� destroy ��������
    while (q != p)
        a.destroy(--q);

    // �ͷ��ڴ�
    a.deallocate(p, 10);

    // �����㷨��������δ��ʼ���ڴ��д�������
    vector<int> vi{0, 1, 2, 3};
    allocator<int> b;
    auto p9 = b.allocate(vi.size() * 2);
    // ���� vi �е�Ԫ�ع���ǰ vi.size() ��Ԫ��
    auto q9 = uninitialized_copy(vi.begin(), vi.end(), p9);
    // ��ʣ��Ԫ�س�ʼ��Ϊ 42
    uninitialized_fill_n(q9, vi.size(), 42);
}

