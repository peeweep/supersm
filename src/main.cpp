#include "common.h"
int main(int argc, char const *argv[]) {
  common common;
  common.process_options(argc, argv);
  return 0;
}