#ifndef RECORD_HPP
#define RECORD_HPP

#include <iostream>
#include <string>
#include <vector>

namespace AddressBook {
struct Record {
    int id = -1;
    std::string first_name;
    std::string last_name;
    std::string email;
    std::string telephone;
    Record() = default;
    Record(const std::vector<std::string> &params);
};
std::ostream& operator<<(std::ostream& os, Record record);
}  // namespace AddressBook

#endif  // RECORD_HPP
