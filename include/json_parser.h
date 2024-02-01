#ifndef JSON_PARSER_H
#define JSON_PARSER_H

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <json-c/json.h>

bool    parse_and_extract_content(const char *data, char **response);

#endif
