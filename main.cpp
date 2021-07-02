#include <fstream>
#include <iostream>
#include <utility>
#include <cli/cli.h>
#include <cli/clifilesession.h>
#include <nlohmann/json.hpp>
#include "Database.hpp"
#include "DatabaseException.hpp"
#include "Record.hpp"

using json = nlohmann::json;
using namespace AddressBook;

void print_records(std::ostream &os, const std::vector<Record> &records) {
    int i = 1;
    for (auto record: records) {
        os << i << ":\n";
        os << record;
        os << std::string(30, '-') << '\n';
        i++;
    }
    os << records.size() << " records in total." << std::endl;
}

int main(int argc, char** argv) {
    std::ifstream config_file("config.json");
    json config;
    config_file >> config;
    std::string uri = config.at("database");
    // Load database
    std::cout << "Address Book Program\n"
                 "--------------------"
              << std::endl;
    try {
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
                ostream << record;
            },
            "Get a record by a person's first and last name."
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
            "delete",
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
        cli::Cli mycli(std::move(menu));
        cli::CliFileSession file_session(mycli);
        file_session.Start();
    } catch (DatabaseException& e) {
        std::cout << "Database error: " << e.what() << std::endl;
        return -1;
    }
    return 0;
}
