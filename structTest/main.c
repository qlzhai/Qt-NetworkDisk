#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

/*
 *弹性结构体 最后一个成员设置为空的int数组类型
 *分配空间->赋值->释放空间
*/
typedef struct PDU
{
    int a;
    int b;
    int c;
    int d[];
}PDU;

int main()
{
    printf("Hello World!\n");
    printf("%ld\n", sizeof(PDU));

    PDU * pdu = (PDU*)malloc(sizeof(PDU)+100*sizeof(int));

    pdu->a = 90;
    pdu->b = 89;
    pdu->c = 88;

    memcpy(pdu->d, "you jump i jump", 16);

    printf("a = %d, b = %d, c = %d, d = %s", pdu->a,pdu->b,pdu->c,(char*)pdu->d);
    free(pdu);
    pdu = NULL;
    return 0;
}
