#include <string>
#include <vector>
#include <sqlite3.h>
#include "Record.hpp"

namespace AddressBook {
class Database {
   public:
    Database(const std::string &uri);
    void AddRecord(const Record &record);
    std::vector<Record> GetRecords(const Record &record) const;
    Record GetRecordByName(const std::string &first_name, const std::string &last_name) const;
    std::vector<Record> GetAllRecords() const;
    int DeleteRecord(const std::string &first_name, const std::string &last_name);
    int DeleteRecord(const Record &record);
    int DeleteRecord(int rowid);
    int UpdateRecord(int rowid, const Record& record) const;
    void ClearRecords();
    ~Database();

   private:
    void CreateTableIfNotExists();
    Record GetRecordFromRow(sqlite3_stmt *stmt) const;
    static int GetAllRecordsCallback(void *arg, int colc, char **colv, char **col_name);
    static sqlite3_stmt *BindStatement(const Record &record, sqlite3_stmt *stmt);
    static sqlite3_stmt *BindStatementText(sqlite3_stmt *stmt, std::initializer_list<std::string> params);
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
