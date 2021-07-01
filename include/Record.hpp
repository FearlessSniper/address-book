#ifndef RECORD_HPP
#define RECORD_HPP

#include <iostream>
#include <string>

namespace AddressBook {
struct Record {
    std::string first_name;
    std::string last_name;
    std::string email;
    std::string telephone;
};
std::ostream& operator<<(std::ostream& os, Record record);
}  // namespace AddressBook

#endif  // RECORD_HPP
