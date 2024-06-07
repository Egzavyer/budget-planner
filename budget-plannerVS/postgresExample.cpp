/*#include <iostream>
#include <pqxx/pqxx>

int main()
{
    try
    {
        std::string connectionString = "host=localhost port=5432 dbname=budget_planner user=postgres password=OUVRTOUA";

        // Connect to the database.  You can have multiple connections open
        // at the same time, even to the same database.
        pqxx::connection c(connectionString.c_str());
        std::cout << "Connected to " << c.dbname() << '\n';

        // Start a transaction.  A connection can only have one transaction
        // open at the same time, but after you finish a transaction, you
        // can start a new one on the same connection.
        pqxx::work tx(c);

        // Query data of two columns, converting them to std::string and
        // int respectively.  Iterate the rows.
        pqxx::result r = tx.exec("SELECT * FROM users");

        for (auto row : r) {
            // Assuming you have columns: id, username, email
            std::cout << "ID: " << row["id"].c_str() << ", "
                << "Username: " << row["username"].c_str() << ", "
                << "Password: " << row["password"].c_str() << "\n";
        }

        // Commit the transaction
        tx.commit();
    }
    catch (std::exception const& e)
    {
        std::cerr << "ERROR: " << e.what() << '\n';
        return 1;
    }
    return 0;
}*/