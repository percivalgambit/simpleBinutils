#include <cstdlib>
#include <fstream>

#include "emulator/emulator.h"
#include "util/status.h"

using emulator::Emulator;
using util::Status;

int main(int argc, char* argv[]) {
  if (argc != 2) {
    std::cout << "usage: " << argv[0] << " <program_file>" << std::endl;
    return EXIT_FAILURE;
  }

  std::ifstream program(argv[1], std::ios::binary);
  Emulator emulator(&program);
  const Status& status = emulator.Run();
  if (!status.IsOk()) {
    std::cerr << status << std::endl;
  }
  return static_cast<int>(status.StatusCode());
}
