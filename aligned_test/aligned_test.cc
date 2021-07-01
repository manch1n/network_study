#include <unistd.h>
#include <iostream>

using namespace std;

class unpacked
{
public:
    int a;
    char b;
    double c;
};

class PackedByAttrribute
{
public:
    int a;
    char b;
    double c;
} __attribute__((packed));

#pragma pack(2)
class PackedByPragma
{
public:
    int a;
    char b;
    double c;
};
#pragma pack()

class Mix
{
public:
    unpacked a;
    PackedByAttrribute b;
    PackedByPragma c;
    int d;
    char e;
    double f;
    char g;
};
//or:

int main(int argc, char **argv)
{
    unpacked A;
    PackedByAttrribute B;
    PackedByPragma C;
    Mix D;
    printf("unpacked: %d a:%p,b:%p,c:%p\n", sizeof(A), &A.a, &A.b, &A.c);
    printf("packed by attribute: %d a:%p,b:%p,c:%p\n", sizeof(B), &B.a, &B.b, &B.c);
    printf("packed by pragma pack: %d a:%p,b:%p,c:%p\n", sizeof(C), &C.a, &C.b, &C.c);
    printf("Mix: %d a:%p,b:%p,c:%p,d:%p,e:%p,f:%p,g:%p\n", sizeof(D), &D.a, &D.b, &D.c, &D.d, &D.e, &D.f, &D.g);
    return 0;
}
