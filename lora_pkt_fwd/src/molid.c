#include "molid.h"

void molid_log(struct lgw_pkt_rx_s* p) {
    uint8_t mhdr_ftype = 0;
    int32_t fhdr_devaddr = 0;
    uint8_t fhdr_fctrl_ack = 0;
    uint16_t join_devnonce = 0;
    
    /* MHDR - FType */
    mhdr_ftype = p->payload[0] & 224;
    /* FHDR - DevAddr */
    fhdr_devaddr  = p->payload[1];
    fhdr_devaddr |= p->payload[2] << 8;
    fhdr_devaddr |= p->payload[3] << 16;
    fhdr_devaddr |= p->payload[4] << 24;
    /* FHDR - ACK */
    fhdr_fctrl_ack = p->payload[5] & 32;
    /* JRQ - DevNonce */
    // TODO: check for join-request
    join_devnonce  = p->payload[17];
    join_devnonce |= p->payload[18] << 8;
}