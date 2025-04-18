
#include <stdio.h>
#define PARSER_IMPLEMENTATION
#include "argparser.h"

int main(int argc, char *argv[]) {
  Parser parser = parser_new();
  add_flag(&parser, "argc", "argv");
  ParseResult *results = parser_parse(&parser, argc, argv);
  printf("%s\n", results->results[0]);
}
