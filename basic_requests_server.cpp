#include <evhttp.h>
#include <iostream>

//Distinguishes url requested, and form of request (put, post, delete, get)

void process_get_request(struct evhttp_request *req, void *arg)
{
	struct evbuffer *buf = evbuffer_new();
	if (buf == NULL) return;
	evbuffer_add_printf(buf, "Get Request", evhttp_request_uri(req));
	evhttp_send_reply(req, HTTP_OK, "OK", buf);
}

void process_post_request(struct evhttp_request *req, void *arg)
{
	struct evbuffer *buf = evbuffer_new();
	if (!buf == NULL)
	{
	evbuffer_add_printf(buf, "Post Request", evhttp_request_uri(req));
	evhttp_send_reply(req, HTTP_OK, "OK", buf);
	}
}

//Process a request
void process_request(struct evhttp_request *req, void *arg){
	std::cout << req->type << std::endl;
	if (req->type == 1)
	{
		process_get_request(req, arg);
	}
	else if (req->type == 2)
	{
		process_post_request(req, arg);
	}
	else if (req->type == 8)
	{
	std::cout << "Put Detected" << std::endl;
	}
	else if (req->type == 16)
	{
	std::cout << "Delete Detected" << std::endl;
	}
	
}

int main () {
    struct event_base *base = NULL;
    struct evhttp *httpd = NULL;
    base = event_init();
    if (base == NULL) return -1;
    httpd = evhttp_new(base);
    if (httpd == NULL) return -1;
    if (evhttp_bind_socket(httpd, "0.0.0.0", 12345) != 0) return -1;
    evhttp_set_gencb(httpd, process_request, NULL);
    event_base_dispatch(base);
    return 0;
}
