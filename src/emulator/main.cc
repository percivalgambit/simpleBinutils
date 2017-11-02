#include <cstdlib>
#include <fstream>
#include <iostream>

#include "emulator/accumulator.h"
#include "emulator/emulator.h"
#include "emulator/memory.h"
#include "util/status.h"

using emulator::Accumulator;
using emulator::Emulator;
using emulator::Memory;
using std::cerr;
using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::ios;
using util::Status;

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
