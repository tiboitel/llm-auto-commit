#include "json_parser.h"

bool    parse_and_extract_content(const char *data, char **response)
{
    // Parse JSON data
    json_object *jobj = json_tokener_parse(data);
    if (jobj == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return false;
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
                    *response = strdup(json_object_get_string(contentContent));
                    if (response == NULL) {
                        fprintf(stderr, "Error parsing content field\n");
                        return false;
                    }
                }
            }
        }
    }

   json_object_put(jobj);

    return true;
}
