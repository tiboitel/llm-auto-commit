#include <stdio.h>
#include <string.h>
#include <curl/curl.h>
#include <json-c/json.h>
#include "http_request.h"
#include "json_parser.h"

#define LLM_API_URL "http://127.0.0.1:5000/v1/chat/completions"

// Global variable to store content
char    *extractedContent = NULL;

// Callback function to write received data
size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t realsize = size * nmemb;

    (void)userp;

    parse_and_extract_content(contents, &extractedContent);
    printf("git commit -m \"%s\"\n", extractedContent);

    return realsize;
}


void usage() {
    printf("Usage: llm-auto-commit [OPTION]... [MESSAGE]\n\
            Transforms MESSAGE into a formatted commit message.\n");
}

int main(int argc, char **argv) {
    (void)argv;

    if (argc <= 1)
    {
        usage();
        return (EXIT_SUCCESS);
    }

    char *promptTemplate = 
        "{\"messages\": [" 
        "{\"role\": \"user\","
        "\"content\": \"Rewrite message: %s as a commit message following the format below. Never use quote or backquote. Use tense in the subject and imperative mood. Keep the message concise. Write only the commit message. Format:\\nfeat($scope): $message.\\n\"}" 
        "],"
        "\"mode\": \"instruct\","
        "\"instruction_template\": \"Alpaca\","
        "\"max_tokens\": 25}";
    size_t  promptSize = snprintf(NULL, 0, promptTemplate, argv[1]) + 1;
    char    *prompt = (char *)malloc(sizeof(char) * promptSize);

    // Format prompt. 
    snprintf(prompt, promptSize, promptTemplate, argv[1]);

    // Send request to LLM API.
    send_http_request(LLM_API_URL, prompt, &WriteCallback);

    return EXIT_SUCCESS;
}

