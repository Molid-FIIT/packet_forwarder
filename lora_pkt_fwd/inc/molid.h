#ifndef _LORA_PKTFWD_MOLID_H
#define _LORA_PKTFWD_MOLID_H

#include "loragw_hal.h"
#include <stdlib.h>
#include <stddef.h>
#include <syslog.h>
#include <time.h>
#include <stdio.h>
#include <pthread.h>
//#include 

#define MOLID_SYSLOG_NAME "molid"
#define MOLID_MAX_LENGTH 2000

pthread_mutex_t lock;

// enum molid_ftype = { JOIN_REQUEST = 0x0, JOIN_ACCEPT = 0x1, OTHER = 0xff }; 

/*
struct molid_log_s {
    // MHDR - DONE 
    uint8_t  mhdr_ftype     = 0; // is everywhere

    // FHDR - DONE 
    uint32_t fhdr_devaddr   = 0;
    uint8_t  fhdr_fctrl     = 0;
    uint16_t fhdr_fcnt      = 0;

    // JOIN-REQ - DONE 
    uint64_t join_eui       = 0;
    uint64_t join_deveui    = 0;
    uint16_t join_devnonce  = 0;

    // JOIN-ACCEPT - WONT BE DONE
    uint32_t join_netid     = 0;

    // InfoDesc=0,1 or 2 - WONT BE DONE 
    //uint32_t lat            = 0;
    //uint32_t lng            = 0;

    // InfoDesc=3 - WONT BE DONE
    //uint32_t join_netid     = 0;
    //uint32_t join_gwid      = 0;

    // somewhere over the rainbow - WONT BE DONE
    //uint32_t frequency      = 0;

    // Link ADR Commands - WONT BE DONE 
    //uint8_t  data_rate      = 0;

    uint32_t mic            = 0; // is everywhere
};
*/
void molid_log(struct lgw_pkt_rx_s* p, uint64_t lgwm);
void create_json(struct lgw_pkt_rx_s* p, char *buff, int type, uint64_t lgwm);
void create_syslog(char *buff);

#endif