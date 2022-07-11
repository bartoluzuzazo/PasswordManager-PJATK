#include "CMD.h"

/**
 * Command used to close the application.
 */
class CMD_exit : public CMD {
public:
    void execute(const std::vector<std::string> &command) override;

};
