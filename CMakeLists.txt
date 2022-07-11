cmake_minimum_required(VERSION 3.21)
project(PasswordManager)

set(CMAKE_CXX_STANDARD 20)

add_executable(PasswordManager main.cpp Classes/password_group.cpp Classes/password_group.h Classes/password.cpp Classes/password.h Util/pswdutils.cpp Util/pswdutils.h Classes/manual.cpp Classes/manual.h Commands/CMD_pswd.cpp Commands/CMD_pswd.h Commands/CMD_group.cpp Commands/CMD_group.h Commands/CMD.cpp Commands/CMD.h Commands/CMD_exit.cpp Commands/CMD_exit.h Commands/CMD_print.cpp Commands/CMD_print.h Commands/CMD_man.cpp Commands/CMD_man.h Util/memory.cpp Util/memory.h Util/cypher.cpp Util/cypher.h Util/console.cpp Util/console.h Commands/CMD_sort.cpp Commands/CMD_sort.h Util/timestamp.cpp Util/timestamp.h Commands/CMD_help.cpp Commands/CMD_help.h Commands/CMD_find.cpp Commands/CMD_find.h)
