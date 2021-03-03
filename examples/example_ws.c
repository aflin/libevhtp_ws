#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <errno.h>
#include <evhtp.h>
#include "../ws/evhtp_ws.h"

/* free the data after evbuffer is done with it */
static void refcb(const void *data, size_t datalen, void *val)
{
    if(val)
        free((void *)val);
    else
        free((void *)data);
}


void
testcb(evhtp_request_t * req, void * a) {
    void *buf = evbuffer_pullup(req->buffer_in, -1);
    evhtp_ws_data *ws_data;
    size_t outlen = 0;
    unsigned char *outbuf;
    struct evbuffer *resp;
    int disconnect=0;

    if(buf && !strncasecmp("bye", (char*)buf, 3))
        disconnect = 1;

    ws_data = evhtp_ws_data_new(buf, evbuffer_get_length(req->buffer_in));
    outbuf = evhtp_ws_data_pack(ws_data, &outlen);
    free(ws_data);
    resp    = evbuffer_new();

    evbuffer_add_reference(resp, outbuf, outlen, refcb, NULL);
    evhtp_send_reply_body(req, resp);

    evbuffer_free(resp);

    if(disconnect)
        evhtp_ws_disconnect(req);
}

int
main(int argc, char ** argv) {
    evbase_t * evbase = event_base_new();
    evhtp_t  * htp    = evhtp_new(evbase, NULL);

    evhtp_set_cb(htp, "ws:/", testcb, NULL);
#ifndef EVHTP_DISABLE_EVTHR
    evhtp_use_threads_wexit(htp, NULL, NULL, 8, NULL);
#endif
    evhtp_bind_socket(htp, "0.0.0.0", 8081, 2048);

    printf("try, e.g. wscat -c ws://localhost:8081/\nType 'bye' to exit\n");
    
    event_base_loop(evbase, 0);

    evhtp_unbind_socket(htp);
    evhtp_safe_free(htp, evhtp_free);
    evhtp_safe_free(evbase, event_base_free);

    return 0;
}
