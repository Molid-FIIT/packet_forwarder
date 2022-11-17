#include "molid.h"
#include <syslog.h>

#define MAX_LENGTH 2000

void create_json(struct lgw_pkt_rx_s* p, char *buff, int *size){
    *size = snprintf(
        buff, 
        MAX_LENGTH, 
        "{\"freq_hz\": %u, \"if_chain\": \"%02x\", \"status\": \"%02x\", \"count_us\": %u, \"rf_chain\": \"%02x\", \"modulation\": \"%02x\", \"bandwidth\": \"%02x\", \"datarate\": %u, \"coderate\": \"%02x\", \"rssi\": %.4f, \"snr\": %.4f, \"snr_min\": %.4f, \"snr_max\": %.4f, \"crc\": \"%04x\", \"size\": %d}\0",
        p->freq_hz,
        p->if_chain,
        p->status,
        p->count_us,
        p->rf_chain,
        p->modulation,
        p->bandwidth,
        p->datarate,
        p->coderate,
        p->rssi,
        p->snr,
        p->snr_min,
        p->snr_max,
        p->crc,
        p->size
    );
}

void create_syslog(char *buff, int size){
    //EXAMPLE FROM: https://www.gnu.org/software/libc/manual/html_node/Syslog-Example.html
    setlogmask (LOG_UPTO (LOG_NOTICE));

    openlog ("exampleprog", LOG_CONS | LOG_PID | LOG_NDELAY, LOG_LOCAL1);

    syslog (LOG_NOTICE, "Program started by User %d", getuid ());
    syslog (LOG_INFO, "A tree falls in a forest");

    closelog ();
}


void molid_log(struct lgw_pkt_rx_s* p) {
    int real_size = 0;
    char *buff = calloc(MAX_LENGTH, sizeof(char));
    if(buff == NULL)
        return; //syslog - error not enough memory;

    create_json(p, buff, &size);
    create_syslog(buff, size);

    free(buff);
}