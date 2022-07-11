#include <iostream>
#include <cstdlib>
#include <ctime>
#include "cypher.h"

namespace cypher {
    auto encrypt(std::string & text) -> void{
        std::string key = key::getKey();
        if(key.size()<6) return;
        auto salt1 = 2 + ((int)(key.at(0)))%4,
                salt2 = 2 + ((int)(key.at(1)))%6;
        auto itr = key.at(2);
        auto inLoop = std::string(key.begin()+3, key.end());
        srand(time(nullptr));
        for (auto i = 0; i < text.size(); i++){
            if(i%salt1==0) text.insert( i, 1, (char)(33+rand()%89));
        }
        for (auto i = 0; i < text.size(); i++){
            if(i%salt2==0) text.insert( i, 1, (char)(33+rand()%89));
        }
        auto next = 0;
        auto current = inLoop.at(next);
        for (auto & c : text){
            c+=(int)current;
            next+=itr;
            if(next >= inLoop.size()) next%=inLoop.size();
            current = inLoop.at(next);
        }
    }

    auto decrypt(std::string & text) -> void{
        std::string key = key::getKey();
        if(key.size()<6) return;
        auto salt1 = 2 + ((int)(key.at(0)))%4,
                salt2 = 2 + ((int)(key.at(1)))%6;
        auto itr = key.at(2);
        auto inLoop = std::string(key.begin()+3, key.end());
        auto next = 0;
        auto current = inLoop.at(next);
        for (auto & c : text){
            c-=(int)current;
            next+=itr;
            if(next >= inLoop.size()) next%=inLoop.size();
            current = inLoop.at(next);
        }
        for (auto i = 0; i < text.size(); i++){
            if(i%salt2==0) {
                text.at(i) = 0;
            }
        }
        text.erase(std::remove(text.begin(), text.end(), 0), text.end());
        for (auto i = 0; i < text.size(); i++){
            if(i%salt1==0) {
                text.at(i) = 0;
            }
        }
        text.erase(std::remove(text.begin(), text.end(), 0), text.end());
    }
}

auto key::setKey(std::string const& value) -> void {
    key::keyValue = value;
}
auto key::getKey() -> std::string {
    return keyValue;
}
std::string key::keyValue;