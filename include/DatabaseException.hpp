#include <string>
#include <exception>

namespace AddressBook {
class DatabaseException : std::exception {
    public:
    DatabaseException(const std::string msg);
    const char* what() const noexcept override;
    private:
    std::string msg;
};
}  // namespace AddressBook