#include <iostream>
#include <sqlite3.h>

int print_row(void*, int argc, char** argv, char** col_name) {
    for (int i = 0; i < argc; ++i) {
        const char* value = argv[i] ? argv[i] : "NULL";
        std::cout << col_name[i] << ": " << value;
        if (i + 1 < argc) {
            std::cout << " | ";
        }
    }
    std::cout << '\n';
    return 0;
}

int main() {
    sqlite3* db = nullptr;
    int rc = sqlite3_open("demo.db", &db);
    if (rc != SQLITE_OK) {
        std::cerr << "sqlite3_open failed: " << sqlite3_errmsg(db) << '\n';
        if (db) {
            sqlite3_close(db);
        }
        return 1;
    }

    char* err_msg = nullptr;

    const char* create_sql =
        "CREATE TABLE IF NOT EXISTS users ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "name TEXT NOT NULL"
        ");";
    rc = sqlite3_exec(db, create_sql, nullptr, nullptr, &err_msg);
    if (rc != SQLITE_OK) {
        std::cerr << "CREATE TABLE failed: " << err_msg << '\n';
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return 2;
    }

    const char* insert_sql = "INSERT INTO users(name) VALUES('Alice');";
    rc = sqlite3_exec(db, insert_sql, nullptr, nullptr, &err_msg);
    if (rc != SQLITE_OK) {
        std::cerr << "INSERT failed: " << err_msg << '\n';
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return 3;
    }

    std::cout << "Current rows in users:\n";
    const char* query_sql = "SELECT id, name FROM users ORDER BY id DESC LIMIT 5;";
    rc = sqlite3_exec(db, query_sql, print_row, nullptr, &err_msg);
    if (rc != SQLITE_OK) {
        std::cerr << "SELECT failed: " << err_msg << '\n';
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return 4;
    }

    std::cout << "SQLite version: " << sqlite3_libversion() << '\n';
    sqlite3_close(db);
    return 0;
}
