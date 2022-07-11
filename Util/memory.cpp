#include <iostream>
#include <fstream>
#include "memory.h"
#include "pswdutils.h"
#include "cypher.h"
#include "timestamp.h"
#include "../Classes/password.h"
#include "../Classes/password_group.h"

namespace memory{
    auto save() -> void{
        std::fstream save;
        std::string toSave;

        toSave += "<TIMESTAMPS>\n";
        for(auto const& t: timestamp::getTimestamps()){
            toSave+=t + '\n';
        }
        toSave += "</TIMESTAMPS>\n";

        for(auto group : password_group::getGroups()){
            auto gname = group.getName();
            cypher::encrypt(gname);
            toSave += "<GROUP>\n<GNAME>" + gname + "</GNAME>\n";
            for(auto password : group.getPasswords()){
                auto pname = password.getName();
                auto pswd = password.getPswd();
                auto link = password.getLink();
                auto login = password.getLogin();
                cypher::encrypt(pname);
                cypher::encrypt(pswd);
                cypher::encrypt(link);
                cypher::encrypt(login);
                toSave += "<PASSWORD>\n";
                toSave += "<PNAME>" + pname + "</PNAME>\n";
                toSave += "<PSWD>" + pswd + "</PSWD>\n";
                toSave += "<LINK>" + link + "</LINK>\n";
                toSave += "<LOGIN>" + login + "</LOGIN>\n";
                toSave += "</PASSWORD>\n";
            }
            toSave += "</GROUP>\n";

        }
        save.open(filepath::getPath(), std::ios::out | std::ios::trunc);
        save << toSave;
        save.close();
    }

    auto load() -> void{
        std::fstream load;
        load.open(filepath::getPath(), std::ios::in);
        std::string plaintext, line;
        while(std::getline(load, line)){
            plaintext+=line+'\n';
        }
        load.close();

        auto tss = pswdutils::regexMatcher(plaintext, pswdutils::div_in_load("TIMESTAMPS"));
        std::string timestamp_string;
        if(tss.size()>1) {
            timestamp_string = tss.at(1);
            auto divided_timestamps = pswdutils::regexMatcher(timestamp_string, std::regex("(.*?)\n"));
            divided_timestamps = std::vector(divided_timestamps.begin() + 1, divided_timestamps.end());
            timestamp::setTimestamps(divided_timestamps);
        }
        else{
            auto empty = std::vector<std::string>{""};
            timestamp::setTimestamps(empty);
        }

        auto groups = pswdutils::regexMatcher(plaintext, pswdutils::div_in_load("GROUP"));
        for(auto const& group : groups){
            if(group == groups.at(0)) continue;
            auto gname = pswdutils::regexMatcher(group, pswdutils::div_load_line("GNAME")).at(1);
            cypher::decrypt(gname);
            password_group::append(gname);
            auto passwords = pswdutils::regexMatcher(group, pswdutils::div_in_load("PASSWORD"));
            for(auto const& pass : passwords){
                if(pass == passwords.at(0)) continue;
                auto pname = pswdutils::regexMatcher(pass, pswdutils::div_load_line("PNAME")).at(1);
                auto pswd = pswdutils::regexMatcher(pass, pswdutils::div_load_line("PSWD")).at(1);
                auto link = pswdutils::regexMatcher(pass, pswdutils::div_load_line("LINK")).at(1);
                auto login = pswdutils::regexMatcher(pass, pswdutils::div_load_line("LOGIN")).at(1);
                cypher::decrypt(pname);
                cypher::decrypt(pswd);
                cypher::decrypt(link);
                cypher::decrypt(login);
                password loaded = password(pname, pswd, gname);
                if(!link.empty()) loaded.setLink(link);
                if(!login.empty()) loaded.setLogin(login);
                password_group::addToGroup(gname, loaded);
            }
        }
    }


}

auto filepath::getPath() -> std::string {
    return path;
}

auto filepath::setPath(std::string const& npath) -> void {
    path = npath;
}

std::string filepath::path;