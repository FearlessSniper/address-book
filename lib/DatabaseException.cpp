#include "DatabaseException.hpp"

namespace AddressBook {
    DatabaseException::DatabaseException(const std::string msg) {
        this->msg = msg;
    }
    const char *DatabaseException::what() const noexcept {
        return this->msg.c_str();
    }
}
