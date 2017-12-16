#include <cstdlib>
#include <fstream>

#include "common/constants.h"
#include "emulator/emulator.h"
#include "util/status.h"

using common::Word;
using emulator::Accumulator;
using emulator::Emulator;
using emulator::Memory;
using std::cerr;
using std::cin;
using std::cout;
using std::endl;
using std::basic_ifstream;
using std::ios;
using util::Status;

int main(int argc, char* argv[]) {
  if (argc != 2) {
    cout << "usage: " << argv[0] << " <program_file>" << endl;
    return EXIT_FAILURE;
  }

  basic_ifstream<Word> program(argv[1], ios::binary);
  Emulator emulator(&program);
  const Status& status = emulator.Run();
  if (!status.IsOk()) {
    cerr << status << endl;
  }
  return int(status.StatusCode());
}
