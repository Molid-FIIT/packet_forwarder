#include "molid.h"

void create_log(struct lgw_pkt_rx_s* p, struct molid_log_s* m) {
    /* MHDR - FType */
    m.mhdr_ftype = p->payload[0] & 224;

    if(m.mhdr_ftype == molid_ftype.JOIN_REQUEST) {
        join_req_data(p, m);
    }
    else if(m.mhdr_ftype != molid_ftype.JOIN_ACCEPT) {
        fhdr_data(p, m);
    }
}

void fhdr_data(struct lgw_pkt_rx_s* p, struct molid_log_s* m) {
    /* FHDR - DevAddr */
    m.fhdr_devaddr  = p->payload[1];
    m.fhdr_devaddr |= p->payload[2] << 8;
    m.fhdr_devaddr |= p->payload[3] << 16;
    m.fhdr_devaddr |= p->payload[4] << 24;
    /* FHDR - ACK */
    m.fhdr_fctrl_ack = p->payload[5] & 32;
}

void join_req_data(struct lgw_pkt_rx_s* p, struct molid_log_s* m) {
    /* JRQ - DevNonce */
    m.join_devnonce  = p->payload[17];
    m.join_devnonce |= p->payload[18] << 8;
}

void molid_log(struct lgw_pkt_rx_s* p) {
   struct molid_log_s molid_log;

   create_log(p, molid_log);
}