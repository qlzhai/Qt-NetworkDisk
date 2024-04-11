#include "protocol.h"

PDU *mkPDU(uint uiMsgLen)
{
    uint uiPDULen = sizeof(PDU) + uiMsgLen;
    PDU *pdu = (PDU*)malloc(uiPDULen); //申请单元

    if(pdu == NULL){
        exit((EXIT_FAILURE));
    }

    memset(pdu,0,uiPDULen); //清空
    pdu->uiPDULen = uiPDULen;
    pdu->uiMsgLen = uiMsgLen;
    return pdu;
}
