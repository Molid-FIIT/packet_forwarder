#include "molid.h"

static pthread_mutex_t molid_lock;

void create_json(struct lgw_pkt_rx_s* p, char *buff, int type, uint64_t lgwm){
    // Log all values from structure
    // https://github.com/Lora-net/lora_gateway/blob/master/libloragw/inc/loragw_hal.h
    snprintf(
        buff, 
        MOLID_MAX_LENGTH, 
        "{\"freq_hz\": %u, \"if_chain\": \"%02x\", \"status\": \"%02x\", \"count_us\": %u, \"rf_chain\": \"%02x\", \"modulation\": \"%02x\", \"bandwidth\": \"%02x\", \"datarate\": %u, \"coderate\": \"%02x\", \"rssi\": %.4f, \"snr\": %.4f, \"snr_min\": %.4f, \"snr_max\": %.4f, \"crc\": \"%04x\", \"size\": %d, \"type\": %d, \"lgwm\": %llu, \"time\": %lu}\n",
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
        p->size,
        type,
        lgwm,
        time(NULL)
    );
}

void create_syslog(char *buff){
    pthread_mutex_lock(&molid_lock);
    // https://www.gnu.org/software/libc/manual/html_node/syslog_003b-vsyslog.html
    FILE *f = fopen("/var/log/molid.log", "a");
    fputs(buff, f);
    fclose(f);
    pthread_mutex_unlock(&molid_lock);
}


void molid_log(struct lgw_pkt_rx_s* p, uint64_t lgwm) {
    char *buff = calloc(MOLID_MAX_LENGTH, sizeof(char));
    if(buff == NULL)
        return;

    // Determine the type of packet
    int type = p->payload[0] >> 5;

    create_json(p, buff, type, lgwm);
    create_syslog(buff);

    free(buff);
    return;
}