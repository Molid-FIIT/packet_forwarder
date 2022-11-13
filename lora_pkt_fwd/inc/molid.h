#ifndef _LORA_PKTFWD_MOLID_H
#define _LORA_PKTFWD_MOLID_H

#include "loragw_hal.h"

enum molid_ftype = { JOIN_REQUEST = 0x0, JOIN_ACCEPT = 0x1, OTHER = 0xff }; 

struct molid_log_s {
    /* MHDR */
    uint8_t  mhdr_ftype     = 0; // is everywhere

    /* FHDR */
    uint32_t fhdr_devaddr   = 0;
    uint8_t  fhdr_fctrl     = 0;
    uint16_t fhdr_fcnt      = 0;

    /* JOIN-REQ */
    uint64_t join_eui       = 0;
    uint64_t join_deveui    = 0;
    uint16_t join_devnonce  = 0;

    /* JOIN-ACCEPT */
    uint32_t join_netid     = 0;

    /* InfoDesc=0,1 or 2 */
    uint32_t lat            = 0;
    uint32_t lng            = 0;

    /* InfoDesc=3 */
    uint32_t join_netid     = 0;
    uint32_t join_gwid      = 0;

    /* somewhere over the rainbow */
    uint32_t frequency      = 0;

    /* Link ADR Commands */
    uint8_t  data_rate      = 0;

    uint32_t mic            = 0; // is everywhere
};

void create_log(struct lgw_pkt_rx_s* p, struct molid_log_s* m);
void fhdr_data(struct lgw_pkt_rx_s* p, struct molid_log_s* m);
void join_req_data(struct lgw_pkt_rx_s* p, struct molid_log_s* m);
void join_acc_data(struct lgw_pkt_rx_s* p, struct molid_log_s* m);
void molid_log(struct lgw_pkt_rx_s* p);

#endif