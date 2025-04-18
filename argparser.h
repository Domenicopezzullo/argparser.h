#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef PARSER_IMPLEMENTATION


#define MAXIMUM_FLAGS 10
#define MAXIMUM_OPTIONS 10



typedef struct {
  char *results[1024];
} ParseResult;

typedef struct {
  char *name;
  char *usage;
} Flag;

typedef struct {
  char *name;
  char *usage;
} Option;

typedef struct {
  Flag flags[MAXIMUM_FLAGS];
  Option options[MAXIMUM_OPTIONS];
  int flag_count;
  int option_count;
} Parser;

ParseResult *parser_parse(Parser *parser, int argc, char *argv[]) {
  ParseResult *results = calloc(1, sizeof(ParseResult));
  for (int i = 0; i < argc; ++i) {
    for (int j = 0; j < parser->flag_count; ++j) {
      if (strcmp(argv[i], parser->flags[j].name) == 0) {
        results->results[j] = "true";
      }
    }
    for (int j = 0; j < parser->option_count; ++j) {
      if (strcmp(argv[i], parser->options[j].name) == 0) {
        if (i + 1 < argc) {
          results->results[j + parser->flag_count] = argv[i + 1];
          i++;
        } else {
          fprintf(stderr, "Error: Option %s requires a value\n",
                  parser->options[j].name);
          exit(1);
        }
      }
    }
  }
  return results;
}

void add_flag(Parser *parser, char *name, char *usage) {
  parser->flags[parser->flag_count] = (Flag){.name = name, .usage = usage};
  parser->flag_count++;
}

void add_option(Parser *parser, char *name, char *usage) {
  parser->options[parser->option_count] =
      (Option){.name = name, .usage = usage};
  parser->option_count++;
}

Parser parser_new() {
  Parser parser = {0};
  return parser;
};

#endif