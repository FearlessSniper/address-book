#include <fstream>
#include <iostream>
#include <algorithm>
#include <utility>
#include <cli/cli.h>
#include <cli/clifilesession.h>
#include <nlohmann/json.hpp>
#include "Database.hpp"
#include "DatabaseException.hpp"
#include "Record.hpp"

using json = nlohmann::json;
using namespace AddressBook;

/**
 * @brief Prints a list of records to the ostream
 * @param os The ostream to print to
 * @param records A list of records to be printed
*/
void print_records(std::ostream &os, const std::vector<Record> &records) {
    for (auto record: records) {
        os << record;
        os << std::string(30, '-') << '\n';
    }
    os << records.size() << " records in total." << std::endl;
}

/**
 * @brief Tries to retrieve the URI of the database through the command line
 * arguments and JSON file
 * 
 * @param argc argc of main
 * @param argv argv of main
 * @param fname Filename of the JSON file
 * @return The URI string
 * @throws json::parse_error If the JSON is invalid
 * @throws json::out_of_range If `database` key is not found
*/
std::string getUri(int argc, char** argv, const std::string& fname = "config.json") {
    std::ifstream json_file(fname);
    if (argc >= 2) {
        return argv[1];
    }
    else if (json_file.is_open()) {
        // Attempts to open the JSON file
        json config;
        json_file >> config;
        return config.at("database");
    }
    else {
        return "";
    }
}

int main(int argc, char** argv) {
    try {
        std::string uri = getUri(argc, argv);
        if (uri == "") {
            std::cerr << 
                "The URI to the database file is not found. "
                "Provide the URI as an argument when running"
                " the program or specify it with config.json.";
            return -1;
        }
        // Load database
        std::cout << "Address Book Program\n"
                     "--------------------\n"
                     "Using database at \""
                  << uri
                  << "\""
                  << std::endl;
        Database db(uri);
        auto menu = std::make_unique<cli::Menu>("db_menu");
        menu->Insert(
            "add",
            {"first_name", "last_name", "email", "telephone"},
            [&](std::ostream &ostream, const std::string &first_name, const std::string &last_name, const std::string &email, const std::string &telephone) {
                AddressBook::Record myrecord;
                myrecord.first_name = first_name;
                myrecord.last_name = last_name;
                myrecord.email = email;
                myrecord.telephone = telephone;
                db.AddRecord(myrecord);
            },
            "Add a set of record in first_name, last_name, email, telephone "
            "order."
            );
        menu->Insert(
            "list",
            [&](std::ostream &ostream) {
                auto records = db.GetAllRecords();
                print_records(ostream, records);
            },
            "List all records in the table."
        );
        menu->Insert(
            "get",
            {"first_name", "last_name"},
            [&](std::ostream &ostream, const std::string &first_name, const std::string &last_name) {
                AddressBook::Record record = db.GetRecordByName(first_name, last_name);
                if (record.id == -1) {
                    ostream << "The person \"" << first_name
                        << ' ' << last_name << "\" does not exist." << std::endl;
                }
                else {
                    ostream << record;
                }
            },
            "Get a record by a person's first and last name."
            );
        menu->Insert(
            "delete",
            { "id" },
            [&](std::ostream& os, int id) {
                int rows_affected = db.DeleteRecord(id);
                if (rows_affected == 0) {
                    os << "Record #" << id << " does not exist." << '\n';
                }
                os << rows_affected << " rows affected." << std::endl;
            },
            "Deletes a record by its id."
        );
        menu->Insert(
            "delete_by_name",
            {"first_name", "last_name"},
            [&](std::ostream &ostream, const std::string &first_name, const std::string &last_name) {
                int rows_affected = db.DeleteRecord(first_name, last_name);
                if (rows_affected == 0) {
                    ostream << first_name << " " << last_name << " does not exist. Nothing done." << '\n';
                }
                ostream << rows_affected << " rows affected." << std::endl;
            },
            "Delete records by a person's first and last name."
        );
        menu->Insert(
            "delete_by_details",
            [&](std::ostream &ostream, const std::vector<std::string> &params) {
                AddressBook::Record record(params);
                int rows_affected = db.DeleteRecord(record);
                if (rows_affected == 0) {
                    ostream << "No records with the specified details exist. Nothing done." << '\n';
                }
                ostream << rows_affected << " rows affected." << std::endl;
            },
            "Delete records by the details of the record."
        );
        menu->Insert(
            "update",
            {"id", "first-name", "last-name", "email", "telephone"},
            [&](std::ostream& ostream, int rowid,
                const std::string& first_name,
                const std::string& last_name,
                const std::string& email,
                const std::string& telephone) {
                    Record record;
                    record.first_name = first_name;
                    record.last_name = last_name;
                    record.email = email;
                    record.telephone = telephone;
                    int rows_affected = db.UpdateRecord(rowid, record);
                    if (rows_affected == 0) {
                        ostream << "Record #" << rowid
                            << " does not exist. Nothing done." << '\n';
                    }
                    ostream << rows_affected << " rows affected." << std::endl;
            },
            "Update the record by its id."
        );
        menu->Insert(
            "clear",
            {"confirmation"},
            [&](std::ostream& os, const std::string &confirmation) {
                std::string up_string(confirmation);
                std::transform(
                    up_string.begin(),
                    up_string.end(),
                    up_string.begin(),
                    ::toupper
                );
                if (up_string == "YES") {
                    db.ClearRecords();
                    os << "All data cleared." << std::endl;
                }
                else {
                    os << "Type \"yes\" to confirm removing all data in the database." << std::endl;
                }
            },
            "Deletes all records the database. Use \"yes\" to confirm the change."
        );
        cli::Cli mycli(std::move(menu));
        cli::CliFileSession file_session(mycli);
        file_session.Start();
    } catch (DatabaseException& e) {
        std::cout << "Database error: " << e.what() << std::endl;
        return -1;
    }
    catch (json::exception& e) {
        std::cerr << "JSON error: " << e.what() << std::endl;
    }
    return 0;
}
