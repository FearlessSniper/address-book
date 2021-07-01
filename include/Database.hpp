#include <string>
#include <vector>
#include <sqlite3.h>
#include "Record.hpp"

namespace AddressBook {
class Database {
   public:
    Database(const std::string &uri);
    void AddRecord(const Record &record);
    Record GetRecordByName(const std::string &first_name, const std::string &last_name) const;
    std::vector<Record> GetAllRecords() const;
    ~Database();

   private:
    void CreateTableIfNotExists();
    Record GetRecordFromRow(sqlite3_stmt *stmt) const;
    static int GetAllRecordsCallback(void *arg, int colc, char **colv, char **col_name);
    sqlite3* ppdb;  // Sqlite db handler
    const std::string table_def =
        "CREATE TABLE IF NOT EXISTS contacts ("
        "    first_name TEXT,"
        "    last_name TEXT,"
        "    email TEXT,"
        "    telephone TEXT"
        ")";
};
}  // namespace AddressBook
