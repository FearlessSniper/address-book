#include "Record.hpp"

namespace AddressBook {
    std::ostream& operator<<(std::ostream& os, Record record) {
        os << "First name: " << record.first_name << "\n";
        os << "Last name: " << record.last_name << "\n";
        os << "Email: " << record.email << "\n";
        os << "Telephone: " << record.telephone << std::endl;
        return os;
    }
}