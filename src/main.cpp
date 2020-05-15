#include "../include/sir_interface.h"


using namespace std;

// run the web app
int main(int argc, char **argv) {
  auto mkApp = [](const WEnvironment& env) { return make_unique<SIR_interface>(env); };
  return WRun(argc, argv, mkApp);
}
