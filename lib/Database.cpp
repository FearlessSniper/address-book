#include "Database.hpp"
#include "DatabaseException.hpp"

namespace AddressBook {
/**
 * @brief Construct a new Database:: Database object
 *
 * @param uri The uri to the database
 */
Database::Database(const std::string& uri) {
    int status_code = sqlite3_open_v2(
        uri.c_str(), &(this->ppdb),
        SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE | SQLITE_OPEN_URI, NULL);
    if (status_code != SQLITE_OK) {
        throw DatabaseException(sqlite3_errmsg(this->ppdb));
    }
    this->CreateTableIfNotExists();
}

void Database::AddRecord(const Record& record) {
    const std::string sql("INSERT INTO contacts VALUES (?, ?, ?, ?)");
    sqlite3_stmt* statement;
    sqlite3_prepare_v2(this->ppdb, sql.c_str(), -1, &statement, NULL);
    sqlite3_bind_text(statement, 1, record.first_name.c_str(), -1,
                      SQLITE_STATIC);
    sqlite3_bind_text(statement, 2, record.last_name.c_str(), -1,
                      SQLITE_STATIC);
    sqlite3_bind_text(statement, 3, record.email.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(statement, 4, record.telephone.c_str(), -1,
                      SQLITE_STATIC);
    if (sqlite3_step(statement) != SQLITE_DONE) {
        throw DatabaseException("Failed to add the record.");
    }
    sqlite3_finalize(statement);
}

/**
 * @brief Returns the first record that matches both first name and last name
 *
 * @param first_name The first name
 * @param last_name The last name
 * @return Record A record containing first_name, last_name, email, telephone
 * An empty record if not found.
 */
Record Database::GetRecordByName(const std::string& first_name,
                                 const std::string& last_name) const {
    const std::string sql(
        "SELECT * FROM contacts WHERE first_name = ? AND last_name = ?");
    sqlite3_stmt* statement;
    sqlite3_prepare_v2(this->ppdb, sql.c_str(), -1, &statement, NULL);
    sqlite3_bind_text(statement, 1, first_name.c_str(), -1, NULL);
    sqlite3_bind_text(statement, 2, last_name.c_str(), -1, NULL);
    Record record;
    if (sqlite3_step(statement) == SQLITE_ROW) {
        record = this->GetRecordFromRow(statement);
    }
    sqlite3_finalize(statement);
    return record;
}

std::vector<Record> Database::GetAllRecords() const {
    std::vector<Record> records;
    sqlite3_exec(this->ppdb, "SELECT * FROM contacts",
                 &(Database::GetAllRecordsCallback), &records, NULL);
    return records;
}

void Database::CreateTableIfNotExists() {
    // sqlite3_stmt *statement;
    // sqlite3_prepare_v2(this->ppdb, this->table_def.c_str(), -1, &statement,
    // NULL);
    int status =
        sqlite3_exec(this->ppdb, this->table_def.c_str(), NULL, NULL, NULL);
    if (status != 0) {
        throw DatabaseException(sqlite3_errstr(status));
    }
}

/**
 * @brief Get a record fron a row in the query result.
 * The function expects a full row in the table. If the result
 * is not a full row or nothing can be retrieved from the column,
 * the result is undefined.
 * @param stmt The statement object after `step`
 * @return A record
 */
Record Database::GetRecordFromRow(sqlite3_stmt* stmt) const {
    Record record;
    record.first_name =
        reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
    record.last_name =
        reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
    record.email = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
    record.telephone =
        reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
    return record;
}

/**
 * @brief The callback function (helper) of Database::GetAllRecords
 *
 * @param arg A pointer to a vector of records
 * @param colc Number of columns, i.e. the number of strings in colv
 * @param colv The array of strings of values
 * @param col_name The name of the columns
 * @return int Always 0
 */
int Database::GetAllRecordsCallback(void* arg,
                                    int colc,
                                    char** colv,
                                    char** col_name) {
    std::vector<Record>* pvec = reinterpret_cast<std::vector<Record>*>(arg);
    Record record;
    record.first_name = colv[0];
    record.last_name = colv[1];
    record.email = colv[2];
    record.telephone = colv[3];
    pvec->push_back(record);
    return 0;
}

Database::~Database() {
    int status = sqlite3_close_v2(this->ppdb);
}

}  // namespace AddressBook
