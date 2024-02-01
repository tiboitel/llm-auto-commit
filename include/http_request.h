#ifndef HTTP_REQUEST_H
#define HTTP_REQUEST_H

#include <curl/curl.h>

CURLcode send_http_request(const char *url, const char *postData,
        size_t (*writeCallback)(void *, size_t, size_t, void *));

#endif
