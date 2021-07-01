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

void print_record(std::ostream ostream, std::vector<std::string> args) {
    ostream << "Adding record:\n";
    ostream << "First name: " << args.at(0);
    ostream << "Last name: " << args.at(1);
    ostream << "Email: " << args.at(2);
    ostream << "Telephone: " << args.at(3);
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
            {"first name", "last name", "email", "telephone"},
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
                int i = 1;
                for (auto record: records) {
                    ostream << i << ":\n";
                    ostream << record;
                    i++;
                }
                ostream << records.size() << " records in total." << std::endl;
            },
            "List all records in the table."
        );
        menu->Insert(
            "get",
            [&](std::ostream &ostream, const std::string &first_name, const std::string &last_name) {
                AddressBook::Record record = db.GetRecordByName(first_name, last_name);
                ostream << record;
            },
            "Get a record by a person's first and last name."
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
