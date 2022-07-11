#include "Util/console.h"
#include "Util/memory.h"
#include "Util/timestamp.h"

auto main() -> int {
    console::selectFile();
    console::keyInput();
    memory::load();
    timestamp::readLastTimestamp();
    timestamp::create();
    memory::save();
    console::run_cli();
    return 0;
}
