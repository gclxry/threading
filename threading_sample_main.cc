#include "message_loop.h"

int main(int argc, char** argv) {
  mini_app::MessageLoop loop;
  loop.DoRunLoop();
  return 0;
}