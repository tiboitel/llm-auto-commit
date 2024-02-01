#include <stdio.h>
#include <string.h>
#include <curl/curl.h>
#include <json-c/json.h>

// Global variable to store content
char *extractedContent = NULL;

// Callback function to write received data
size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t realsize = size * nmemb;
    char *data = (char *)contents;

    (void)userp;

    // Parse JSON data
    json_object *jobj = json_tokener_parse(data);
    if (jobj == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return realsize;
    }

    // Extract "content" field
    json_object *contentObj;
    if (json_object_object_get_ex(jobj, "choices", &contentObj)) {
        json_object *messageObj = json_object_array_get_idx(contentObj, 0);
        if (messageObj != NULL) {
            json_object *content;
            if (json_object_object_get_ex(messageObj, "message", &content)) {
                json_object *contentContent;
                if (json_object_object_get_ex(content, "content",
                            &contentContent)) {
                    const char *contentStr = 
                        json_object_get_string(contentContent);
                    printf("%s\n", contentStr);
                }
            }
        }
    }

    json_object_put(jobj);
    return realsize;
}


void usage() {
}

int main(int argc, char **argv) {
    CURL *curl;
    CURLcode res;

    // Temporary void arguments for -Wunused
    (void)argc;
    (void)argv;
    usage();

    // Initialize libcurl
    curl_global_init(CURL_GLOBAL_DEFAULT);

    // Create a curl handle
    curl = curl_easy_init();
    if (curl) {
        // Set the URL
        curl_easy_setopt(curl, CURLOPT_URL,
                "http://127.0.0.1:5000/v1/chat/completions");

        // Set the content type
        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        // Set the POST data
        const char *postData = "{\"messages\":[{\"role\":\"user\",\"content\":\"Write a commit message. Write only the commit message. Be simple and straightforward. Use following format feat:($branch_name) $message:\\n\\n1\\nbranch_name: features/MOB-42.\\nmessage: Write JSX main.\"}],\"mode\":\"instruct\",\"instruction_template\":\"Alpaca\",\"max_tokens\":50}";
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postData);

        // Set the write callback function
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);

        // Perform the request
        res = curl_easy_perform(curl);

        // Check for errors
        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                    curl_easy_strerror(res));
        }

        // Cleanup
        curl_easy_cleanup(curl);
        curl_slist_free_all(headers);
    }

    // Cleanup libcurl
    curl_global_cleanup();

    return 0;
}

