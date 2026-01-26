#include <iostream>
#include <sqlite3.h>

static void die(sqlite3* db, const char* msg) {
    std::cerr << msg << ": " << (db ? sqlite3_errmsg(db) : "no db") << "\n";
    if (db) sqlite3_close(db);
    std::exit(1);
}

int main() {
    sqlite3* db = nullptr;

    // 1) 打开/创建数据库文件
    if (sqlite3_open("test.db", &db) != SQLITE_OK) {
        die(db, "sqlite3_open failed");
    }

    // 2) 建表
    const char* create_sql =
        "CREATE TABLE IF NOT EXISTS users ("
        "  id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "  name TEXT NOT NULL,"
        "  age INTEGER NOT NULL"
        ");";

    if (sqlite3_exec(db, create_sql, nullptr, nullptr, nullptr) != SQLITE_OK) {
        die(db, "create table failed");
    }

    // 3) 插入（用 prepared statement，别用拼字符串）
    const char* insert_sql = "INSERT INTO users(name, age) VALUES(?, ?);";
    sqlite3_stmt* ins = nullptr;

    if (sqlite3_prepare_v2(db, insert_sql, -1, &ins, nullptr) != SQLITE_OK) {
        die(db, "prepare insert failed");
    }

    auto insert_user = [&](const char* name, int age) {
        sqlite3_bind_text(ins, 1, name, -1, SQLITE_TRANSIENT);
        sqlite3_bind_int(ins, 2, age);

        int rc = sqlite3_step(ins);
        if (rc != SQLITE_DONE) {
            std::cerr << "insert step failed: " << sqlite3_errmsg(db) << "\n";
            sqlite3_finalize(ins);
            sqlite3_close(db);
            std::exit(1);
        }

        sqlite3_reset(ins);
        sqlite3_clear_bindings(ins);
    };

    insert_user("Alice", 20);
    insert_user("Bob", 22);

    sqlite3_finalize(ins);

    // 4) 查询并打印
    const char* select_sql = "SELECT id, name, age FROM users ORDER BY id;";
    sqlite3_stmt* sel = nullptr;

    if (sqlite3_prepare_v2(db, select_sql, -1, &sel, nullptr) != SQLITE_OK) {
        die(db, "prepare select failed");
    }

    std::cout << "SQLite version: " << sqlite3_libversion() << "\n";
    std::cout << "Users in DB:\n";

    while (true) {
        int rc = sqlite3_step(sel);
        if (rc == SQLITE_ROW) {
            int id = sqlite3_column_int(sel, 0);
            const unsigned char* name = sqlite3_column_text(sel, 1);
            int age = sqlite3_column_int(sel, 2);

            std::cout << "  id=" << id
                      << ", name=" << (name ? reinterpret_cast<const char*>(name) : "(null)")
                      << ", age=" << age << "\n";
        } else if (rc == SQLITE_DONE) {
            break;
        } else {
            std::cerr << "select step failed: " << sqlite3_errmsg(db) << "\n";
            sqlite3_finalize(sel);
            sqlite3_close(db);
            return 1;
        }
    }

    sqlite3_finalize(sel);
    sqlite3_close(db);

    std::cout << "Done. Created/used test.db\n";
    return 0;
}
