#include "emulator.h"

#include <cstdlib>
#include <fstream>
#include <iostream>

#include "accumulator.h"
#include "memory.h"
#include "status.h"

using std::cerr;
using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::ios;

int main(int argc, char* argv[]) {
  if (argc != 2) {
    cout << "usage: " << argv[0] << " <program_file>" << endl;
    return EXIT_FAILURE;
  }

  Accumulator acc;
  ifstream program(argv[1], ios::binary);
  Memory mem(&program);
  Emulator emulator(acc, mem, &cin, &cout);
  const Status& status = emulator.Run();
  if (!status.IsOk()) {
    cerr << status << endl;
  }
  return int(status.StatusCode());
}
