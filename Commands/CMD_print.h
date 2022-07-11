#include "CMD.h"

/**
 * Command used to print selected passwords for the user.
 */
class CMD_print : public CMD{
public:
    void execute(const std::vector<std::string> &command) override;
};
