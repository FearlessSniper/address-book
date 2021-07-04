#include "Record.hpp"

namespace AddressBook {
    /**
     * @brief Prints the record to the output stream
     * 
     * @param os Output stream
     * @param record The record to be printed
     * @return std::ostream& The output stream
     */
    std::ostream& operator<<(std::ostream& os, Record record) {
        os << "#" << record.id << ":\n";
        os << "First name: " << record.first_name << "\n";
        os << "Last name: " << record.last_name << "\n";
        os << "Email: " << record.email << "\n";
        os << "Telephone: " << record.telephone << std::endl;
        return os;
    }

    /**
     * @brief Construct a new Record:: Record object
     * Unpacks the list of strings in order as in the definition
     * 
     * @param params The list of arguments
     */
    Record::Record(const std::vector<std::string> &params) {
        this->first_name = params.at(0);
        this->last_name = params.at(1);
        this->email = params.at(2);
        this->telephone = params.at(3);
    }
}