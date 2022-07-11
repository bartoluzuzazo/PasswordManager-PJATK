#include <iostream>
#include <vector>
#include <fstream>
#include <filesystem>

#include "../Commands/CMD.h"
#include "../Commands/CMD_help.h"
#include "pswdutils.h"
#include "memory.h"
#include "console.h"
#include "cypher.h"

namespace console{

    auto run_cli() -> void {

        std::string console_input;
        std::vector<std::string> command = {"",""};

        auto* help = new CMD_help;
        help->execute(command);
        delete help;

        while (command.at(1) != "exit") {
            try {
                std::getline(std::cin, console_input);
                if(console_input.empty()) continue;
                command = pswdutils::split(console_input);

                if(!CMD::commands.contains(command.at(1))) throw errorType::invalidCommand;
                CMD& current = *CMD::commands.at(command.at(1));
                current.execute(command);
            }
            catch (errorType e){
                std::cout << pswdutils::errorPrompt(command, e);
            }
            catch (std::out_of_range e){
                std::cout << pswdutils::errorPrompt(command, errorType::notEnoughArguments);
            }
            catch (std::exception const& e) {
                std::cout << e.what();
            }
        }
    }

    auto selectFile() -> void{
        auto path = std::string();
        while(!std::filesystem::exists(path)) {
            std::cout << "Please provide the path to the password file or select one of the default files:\n";
            for(auto const& i: std::filesystem::directory_iterator("../Data")){
                std::cout << i.path() << '\n';
            }
            std::getline(std::cin, path);
            std::string a;

            if (!std::filesystem::exists(path)){
                std::cout << "A file with a name given does not exist.\nDo you want to create a new file? [Y/N]\n";
                std::string choice;
                while(choice!="Y" && choice!="N" && choice!="y" && choice!="n"){
                    std::getline(std::cin, choice);
                    if(choice=="Y" || choice=="y"){
                        auto file = std::fstream(path, std::ios::out);
                        file << "";
                        file.close();
                        if(std::filesystem::exists(path)) {
                            std::cout << "New file created successfully!\n";
                            filepath::setPath(path);
                            return;
                        }
                        else{
                            std::cout << "File with a path given could not be created.\n";
                            break;
                        }
                    }
                }
            }
            else{
                filepath::setPath(path);
            }
        }
    }

    auto keyInput() -> void{
        std::cout<<"Password:\n";
        std::string key;
        std::getline(std::cin, key);
        while(key.size()<6){
            std::cout << "Password must be at least 6 characters long.\n";
            std::getline(std::cin, key);
        }
        key::setKey(key);
        std::cout << "File loaded successfully.\n\n";
    }

}