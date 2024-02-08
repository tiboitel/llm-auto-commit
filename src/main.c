#include <stdio.h>
#include <string.h>
#include <curl/curl.h>
#include <json-c/json.h>
#include "api_request.h"
#include "json_parser.h"

#define USE_OPEN_API TRUE
#if USE_OPEN_API
# define LLM_API_URL "https://api.openai.com/v1/chat/completions"
# define OPEN_API_KEY = ""
#else
# define LLM_API_URL "http://127.0.0.1:5000/v1/chat/completions"
#endif

// Global variable to store content
char *extractedContent = NULL;

// Callback function to write received data
size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    size_t realsize = size * nmemb;

    (void)userp;

    parse_and_extract_content(contents, &extractedContent);
    printf("git commit -m \"%s\"\n", extractedContent);

    return realsize;
}

void usage()
{
    printf("Usage: llm-auto-commit [OPTION]... [MESSAGE]\n\
            Transforms MESSAGE into a formatted commit message.\n");
}

int main(int argc, char **argv)
{
    if (argc <= 1)
    {
        usage();
        return (EXIT_SUCCESS);
    }

    char *promptTemplate =
        "{\"messages\": ["
        "{\"role\": \"user\","
        "\"content\": \"Write $message as a commit message following the format below.\\n\\n"
        "Format rules:\\n\\n"
        "    - Never use quote or backquote.\\n"
        "    - Always use tense in the subject and imperative mood.\\n"
        "    - Keep the message concise.\\n"
        "    - Write only the commit message. Format: $action($scope): $message.\\n"
        "    - Chooses according to the intention of the message if $action is: feat for adding a feature, chore if it concerns the build chain or configuration, docs in case of documentation, bugfix in case of resolution of bug.\\n"
        "    - $scope is replaced by the action field of the commit.\\n\\n"
        "Example:\\n\\n"
        "USER: Added profile picture working\\n"
        "ASSISTANT: feat(user): add profile picture upload functionality\\n"
        "USER: ssh now working properly bugfix\\n"
        "ASSISTANT: bugfix(ssh): resolve the issue related to the ssh protocol.\\n\\n"
        "USER: %s \\n\\n"
	"ASSISTANT: \"}"
        "],"
        "\"mode\": \"instruct\","
	"\"temperature\": \"0.7\","
        "\"instruction_template\": \"Alpaca\","
        "\"max_tokens\": 25}";
    size_t promptSize = snprintf(NULL, 0, promptTemplate, argv[1]) + 1;
    char *prompt = (char *)malloc(sizeof(char) * promptSize);

    // Format prompt.
    snprintf(prompt, promptSize, promptTemplate, argv[1]);

    // Send request to LLM API.
    send_api_request(LLM_API_URL, prompt, &WriteCallback);

    return EXIT_SUCCESS;
}

