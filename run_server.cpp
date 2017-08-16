#include "Server.h"
#include "Config.h"
using namespace ratabase;

int main(int argc, char** argv)
{
    Server s(argc == 2 ? atoi(argv[1]) : DEFAULT_PORT);
    s.run();
}
