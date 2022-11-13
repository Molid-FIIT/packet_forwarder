#include "molid.h"

void create_log(struct lgw_pkt_rx_s* p, struct molid_log_s* m) {
    /* MHDR - FType */
    m.mhdr_ftype = p->payload[0] & 224;

    if(m.mhdr_ftype == molid_ftype.JOIN_REQUEST) {
        join_req_data(p, m);
    }
    else if (m.mhdr_ftype == molid_ftype.JOIN_ACCEPT) {
        join_acc_data(p, m);
    }
    else {
        fhdr_data(p, m);
    }

    // p->datarate // SF
    // p->rssi
    // p->snr
}

void fhdr_data(struct lgw_pkt_rx_s* p, struct molid_log_s* m) {
    /* FHDR - DevAddr */
    m.fhdr_devaddr  = p->payload[1];
    m.fhdr_devaddr |= p->payload[2] << 8;
    m.fhdr_devaddr |= p->payload[3] << 16;
    m.fhdr_devaddr |= p->payload[4] << 24;

    /* FHDR - fctrl */
    m.fhdr_fctrl  = p->payload[5];

    /* FHDR - fcnt */
    m.fhdr_fcnt   = p->payload[6];
    m.fhdr_fcnt  |= p->payload[7] << 8;
}

void join_req_data(struct lgw_pkt_rx_s* p, struct molid_log_s* m) {
    /* JRQ - Eui */
    m.join_eui  = p->payload[8];
    m.join_eui  = p->payload[9] << 8;
    m.join_eui  = p->payload[10] << 16;
    m.join_eui  = p->payload[11] << 24;

    /* JRQ - DevEui */
    m.join_deveui  = p->payload[4];
    m.join_deveui  = p->payload[5] << 8;
    m.join_deveui  = p->payload[6] << 16;
    m.join_deveui  = p->payload[7] << 24;

    /* JRQ - DevNonce */
    m.join_devnonce  = p->payload[17];
    m.join_devnonce |= p->payload[18] << 8;
}

void join_acc_data(struct lgw_pkt_rx_s* p, struct molid_log_s* m) {
}

void molid_log(struct lgw_pkt_rx_s* p) {
   struct molid_log_s molid_log;

   create_log(p, molid_log);
}