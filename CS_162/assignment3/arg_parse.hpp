#ifndef ARG_PARSE_HPP
#define ARG_PARSE_HPP

#include <argp.h>
#include "arg_parse.hpp"

// Structure definition for application arguments
struct customArguments
{
  bool debugEnable;
};

class customArgParser
{
private:
  // Description of the program
  static const char * doc;

  // Description of accepted arguments
  static const char * args_doc;

  // Array of command line arguments
  // Terminated with a null entry
  static struct argp_option options[];

  // Parser Function
  static error_t parse_opt (int key, char *arg, struct argp_state *state);

public:

  // External interface to class
  static struct argp argp;
  static struct customArguments arguments;
  static void InitalizeArguments();
};

#endif // ARG_PARSE_HPP
