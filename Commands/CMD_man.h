#include "CMD.h"

/**
 * Command used to print selected manual pages.
 */
class CMD_man : public CMD {
public:
    void execute(std::vector<std::string> const& command) override;
};
