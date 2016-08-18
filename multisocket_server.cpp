#include <evhttp.h>

//Distinguishes url requested, not form of request (put, post, delete, get)

//Process a request
void process_request(struct evhttp_request *req, void *arg){
    struct evbuffer *buf = evbuffer_new();
    if (buf == NULL) return;
    evbuffer_add_printf(buf, "Requested: %s\n", evhttp_request_uri(req));
    evhttp_send_reply(req, HTTP_OK, "OK", buf);
}

int main () {
    struct event_base *base = NULL;
    struct evhttp *httpd = NULL;
	struct evhttp *httpd2 = NULL;
    base = event_init();
    if (base == NULL) return -1;
    httpd = evhttp_new(base);
    if (httpd == NULL) return -1;
	httpd2 = evhttp_new(base);
	if (httpd2 == NULL) return -1;
    if (evhttp_bind_socket(httpd, "0.0.0.0", 12345) != 0) return -1;
	if (evhttp_bind_socket(httpd2, "0.0.0.0", 12346) !=0) return -1;
    evhttp_set_gencb(httpd, process_request, NULL);
	evhttp_set_gencb(httpd2, process_request, NULL);
    event_base_dispatch(base);
    return 0;
}
