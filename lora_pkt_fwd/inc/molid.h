#ifndef _LORA_PKTFWD_MOLID_H
#define _LORA_PKTFWD_MOLID_H

#include "loragw_hal.h"

enum molid_ftype = { JOIN_REQUEST = 0x0, JOIN_ACCEPT = 0x1, OTHER = 0xff }; 

struct molid_log_s {
    uint8_t mhdr_ftype     = 0;
    int32_t fhdr_devaddr   = 0;
    uint8_t fhdr_fctrl_ack = 0;
    uint16_t join_devnonce = 0;
};

void create_log(struct lgw_pkt_rx_s* p, struct molid_log_s* m);
void fhdr_data(struct lgw_pkt_rx_s* p, struct molid_log_s* m);
void join_req_data(struct lgw_pkt_rx_s* p, struct molid_log_s* m);
void molid_log(struct lgw_pkt_rx_s* p);

#endif