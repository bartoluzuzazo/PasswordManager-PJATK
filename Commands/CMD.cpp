#include <iostream>
#include "CMD.h"
#include "CMD_pswd.h"
#include "CMD_group.h"
#include "CMD_exit.h"
#include "CMD_print.h"
#include "CMD_man.h"
#include "CMD_sort.h"
#include "CMD_help.h"
#include "CMD_find.h"

const std::map <std::string,CMD*> CMD::commands{
        {"pswd", new CMD_pswd},
        {"group", new CMD_group},
        {"exit", new CMD_exit},
        {"print", new CMD_print},
        {"man", new CMD_man},
        {"sort", new CMD_sort},
        {"help", new CMD_help},
        {"find", new CMD_find}
};
