#include <iostream>
#include <map>
#include "manual.h"
#include "../Util/pswdutils.h"


const std::map<std::string,std::string> manual::manualText{

    {"man",
        R"(
NAME
    man - displays detailed help for selected command

SYNOPSIS
    man [command_name]

OPTIONS
    This command does not require any additional options.
)"

    },

    {"exit",
            R"(
NAME
    exit - closes the program.

SYNOPSIS
    exit

OPTIONS
    This command does not require any additional options.
)"
    },

    {"pswd",
        R"(
NAME
    pswd - allows the user to manage saved passwords.

SYNOPSIS
    pswd [OPTION] [...]

    All fields following [OPTION] must be provided using "" quotation marks.

OPTIONS
    -a, --add "GROUP" "NAME" "PASSWORD" "LINK" "LOGIN"
        Adds a new password in a selected group.
        Link and login fields are optional.

    -g, --generate "GROUP" "NAME" "GENERATOR" "LENGTH" "LINK" "LOGIN"
        Generated a password based on the options enabled in generator.
        Available generator options:
            l - enable use of lowercase letters,
            u - enable use of uppercase letters,
            d - enable use of digits,
            s - enable use of special characters.
        Example:
            "uds" typed in a generator field will create a password using uppercase
            letters, digits and special characters, but not lowercase letters.

    -e, --edit "GROUP" "NAME" "FIELD TO CHANGE" "CHANGED VALUE"
        Changes one password field to a value given.
        Fields that can be given as an "FIELD TO CHANGE" argument:
            "name", "group", "password", "login", "link"

    -r, --remove "GROUP" "NAME"
        Removes a password from a group.
)"
    },

    {"group",
        R"(
NAME
    group - allows the user to manage password groups

SYNOPSIS
    group [OPTION] [NAME]

OPTIONS
    -a, --add [NAME]
        Adds a new password group under given name

    -r, --remove [NAME]
        Removes a selected group, along with all its passwords.
)"
    },

    {"sort",
            R"(
NAME
    sort - prints a list of passwords sorted in a selected order.

SYNOPSIS
    sort [OPTION] [...]

    Multiple options can be selected. Consecutive options have lower priority.

OPTIONS
    -g, --group
        Sorts alphabetically by group name.

    -n, --name
        Sorts alphabetically by password name.

    -p, --password
        Sorts alphabetically by password key.

    -lg, --login
        Sorts alphabetically by password's login.

    -ln, --link
        Sorts alphabetically by password's link.
)"
    },

    {"print",
            R"(
NAME
    print - displays selected data.

SYNOPSIS
    help [OPTION]

OPTIONS
    -a, --all
        Prints all groups of passwords, and their contents.

    -t, --timestamps
        Prints all the login timestamps from current file.
)"
    },

    {"help",
        R"(
NAME
    help - lists all available commands.

SYNOPSIS
    help

OPTIONS
    This command does not require any additional options.

)"
    },

    {"find",
            R"(
NAME
    find - displays only the passwords matching selected predicates.

SYNOPSIS
    find [OPTION 1] [...]

    Multiple options can be selected.

OPTIONS
    EQUAL TO:

        -ne [NAME]
            Returns only the passwords with name field equal to [NAME]

        -pe [NAME]
            Returns only the passwords with password key equal to [NAME]

        -ge [NAME]
            Returns only the passwords with group name equal to [NAME]

        -lge [NAME]
            Returns only the passwords with login field equal to [NAME]

        -lne [NAME]
            Returns only the passwords with link field equal to [NAME]

    CONTAINS:

        -cl
            Returns only the passwords with a key containing lowercase letters

        -cu
            Returns only the passwords with a key containing uppercase letters

        -cd
            Returns only the passwords with a key containing digits

        -cs
            Returns only the passwords with a key containing special characters

        -c [NAME]
            Returns only the passwords with a key containing [NAME] string
)"
    }
};
/**
 * Displays selected page from a manual
 * @param name - desired command name
 */
void manual::manPrompt(std::string const& name) {
    try {
        std::cout << manualText.at(name);
    }
    catch (std::out_of_range e){
        throw errorType::invalidCommand;
    }
}