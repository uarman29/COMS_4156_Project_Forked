#include "db-service.h"

#include <stdlib.h>
#include <iostream>

#include "mysql_connection.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

std::string hostname = "tcp://127.0.0.1:3306";
std::string username = "dbuser";
std::string password = "123";
std::string database = "matchmaking_api_db";

Player get_player(std::string player_email) {
    std::cout << "Connecting to MYSQL to get player with email: " + player_email << std::endl;
    Player P;

    try {
        sql::Driver *driver;
        sql::Connection *con;
        sql::PreparedStatement  *prep_stmt;
        sql::ResultSet *res;

        driver = get_driver_instance();
        con = driver->connect(hostname, username, password);

        con->setSchema(database);

        prep_stmt = con->prepareStatement("SELECT * FROM Players P WHERE P.player_email = ?;");

        prep_stmt->setString(1, player_email);

        res = prep_stmt->executeQuery();
        while (res->next()) {
            P.player_email = res->getString("player_email");
            std::cout << P.toString() << std::endl;
        }

        delete prep_stmt;
        delete res;
        delete con;

        std::cout << "Successfully retrieved player with email: " + player_email << std::endl;
        return P;

    } catch (sql::SQLException &e) {
        std::cout << "Error getting all player with email: " + player_email << std::endl;
        std::cout << "# ERR: SQLException in " << __FILE__;
        std::cout << "(" << __FUNCTION__ << ") on line "<< __LINE__ << std::endl;
        std::cout << "# ERR: " << e.what();
        std::cout << " (MySQL error code: " << e.getErrorCode();
        std::cout << ", SQLState: " << e.getSQLState() <<" )" << std::endl;
        return P;
    }
}

Developer get_developer(std::string developer_email){
    std::cout << "Connecting to MYSQL to get developer with email: " + developer_email << std::endl;
    Developer D;

    try {
        sql::Driver *driver;
        sql::Connection *con;
        sql::PreparedStatement  *prep_stmt;
        sql::ResultSet *res;

        driver = get_driver_instance();
        con = driver->connect(hostname, username, password);

        con->setSchema(database);

        prep_stmt = con->prepareStatement("SELECT * FROM Developers D WHERE D.developer_email = ?;");

        prep_stmt->setString(1, developer_email);

        res = prep_stmt->executeQuery();
        while (res->next()) {
            D.developer_email = res->getString("developer_email");
            D.developer_password = res->getString("developer_password");
            std::cout << D.toString() << std::endl;
        }

        delete prep_stmt;
        delete res;
        delete con;

        std::cout << "Successfully retrieved developer with email: " + developer_email << std::endl;
        return D;

    } catch (sql::SQLException &e) {
        std::cout << "Error getting all developer with email: " + developer_email << std::endl;
        std::cout << "# ERR: SQLException in " << __FILE__;
        std::cout << "(" << __FUNCTION__ << ") on line "<< __LINE__ << std::endl;
        std::cout << "# ERR: " << e.what();
        std::cout << " (MySQL error code: " << e.getErrorCode();
        std::cout << ", SQLState: " << e.getSQLState() <<" )" << std::endl;
        return D;
    }
}

Game_Details get_game_details(int game_id) {
    std::cout << "Connecting to MYSQL to get game with with: " + std::to_string(game_id) << std::endl;
    Game_Details GD;

    try {
        sql::Driver *driver;
        sql::Connection *con;
        sql::PreparedStatement  *prep_stmt;
        sql::ResultSet *res;

        driver = get_driver_instance();
        con = driver->connect(hostname, username, password);

        con->setSchema(database);

        prep_stmt = con->prepareStatement("SELECT * FROM Game_Details GD WHERE GD.game_id = ?;");

        prep_stmt->setInt(1, game_id);

        res = prep_stmt->executeQuery();
        while (res->next()) {
            GD.game_id = std::stoi(res->getString("game_id"));
            GD.developer_email = res->getString("developer_email");
            GD.game_name = res->getString("game_name");
            GD.game_parameter1_name = res->getString("game_parameter1_name");
            GD.game_parameter1_weight = std::stof(res->getString("game_parameter1_weight"));

            GD.game_parameter2_name = res->getString("game_parameter2_name");
            GD.game_parameter2_weight = std::stof(res->getString("game_parameter2_weight"));

            GD.game_parameter3_name = res->getString("game_parameter3_name");
            GD.game_parameter3_weight = std::stof(res->getString("game_parameter3_weight"));

            GD.game_parameter4_name = res->getString("game_parameter4_name");
            GD.game_parameter4_weight = std::stof(res->getString("game_parameter4_weight"));

            GD.category = res->getString("category");
            GD.players_per_team = std::stoi(res->getString("players_per_team"));
            GD.teams_per_match = std::stoi(res->getString("teams_per_match"));
            std::cout << GD.toString() << std::endl;
        }

        delete prep_stmt;
        delete res;
        delete con;

        std::cout << "Successfully retrieved game with game_id: " + std::to_string(game_id) << std::endl;
        return GD;

    } catch (sql::SQLException &e) {
        std::cout << "Error getting all game with game_id: " + std::to_string(game_id) << std::endl;
        std::cout << "# ERR: SQLException in " << __FILE__;
        std::cout << "(" << __FUNCTION__ << ") on line "<< __LINE__ << std::endl;
        std::cout << "# ERR: " << e.what();
        std::cout << " (MySQL error code: " << e.getErrorCode();
        std::cout << ", SQLState: " << e.getSQLState() <<" )" << std::endl;
        return GD;
    }
}

Player_Game_Ratings get_player_game_rating(std::string player_email, int game_id){
    std::cout << "Connecting to MYSQL to get rating in game with game_id: " + std::to_string(game_id) + " for player with email: " + player_email<< std::endl;
    Player_Game_Ratings PGR;

    try {
        sql::Driver *driver;
        sql::Connection *con;
        sql::PreparedStatement  *prep_stmt;
        sql::ResultSet *res;

        driver = get_driver_instance();
        con = driver->connect(hostname, username, password);

        con->setSchema(database);

        prep_stmt = con->prepareStatement("SELECT * FROM Player_Game_Ratings PGR WHERE PGR.player_email = ? AND PGR.game_id = ?;");

        prep_stmt->setString(1, player_email);
        prep_stmt->setInt(2, game_id);

        res = prep_stmt->executeQuery();
        while (res->next()) {
            PGR.player_email = res->getString("player_email");
            PGR.game_id = std::stoi(res->getString("game_id"));
            PGR.game_parameter1_value = std::stoi(res->getString("game_parameter1_value"));
            PGR.game_parameter2_value = std::stoi(res->getString("game_parameter2_value"));
            PGR.game_parameter3_value = std::stoi(res->getString("game_parameter3_value"));
            PGR.game_parameter4_value = std::stoi(res->getString("game_parameter4_value"));
            std::cout << PGR.toString() << std::endl;
        }

        delete prep_stmt;
        delete res;
        delete con;

        std::cout << "Successfully retrieved rating in game with game_id: " + std::to_string(game_id) + " for player with email: " + player_email<< std::endl;
        return PGR;

    } catch (sql::SQLException &e) {
        std::cout << "Error getting rating in game with game_id: " + std::to_string(game_id) + " for player with email: " + player_email<< std::endl;
        std::cout << "# ERR: SQLException in " << __FILE__;
        std::cout << "(" << __FUNCTION__ << ") on line "<< __LINE__ << std::endl;
        std::cout << "# ERR: " << e.what();
        std::cout << " (MySQL error code: " << e.getErrorCode();
        std::cout << ", SQLState: " << e.getSQLState() <<" )" << std::endl;
        return PGR;
    }
}

Joined_Player_Game_Ratings get_joined_player_game_rating(std::string player_email, int game_id) {
    std::cout << "Connecting to MYSQL to get rating in game with game_id: " + std::to_string(game_id) + " for player with email: " + player_email<< std::endl;
    Joined_Player_Game_Ratings JPGR;

    try {
        sql::Driver *driver;
        sql::Connection *con;
        sql::PreparedStatement  *prep_stmt;
        sql::ResultSet *res;

        driver = get_driver_instance();
        con = driver->connect(hostname, username, password);

        con->setSchema(database);

        prep_stmt = con->prepareStatement("SELECT PGR.*, GD.* FROM Players P JOIN Player_Game_Ratings PGR ON P.player_email = PGR.player_email JOIN Game_Details GD ON PGR.game_id = GD.game_id WHERE P.player_email = ? AND GD.game_id = ?;");

        prep_stmt->setString(1, player_email);
        prep_stmt->setInt(2, game_id);

        res = prep_stmt->executeQuery();
        while (res->next()) {
            JPGR.player_email = res->getString("player_email");
            JPGR.game_id = std::stoi(res->getString("game_id"));
            JPGR.developer_email = res->getString("developer_email");
            JPGR.game_name = res->getString("game_name");
            JPGR.game_parameter1_name = res->getString("game_parameter1_name");
            JPGR.game_parameter1_weight = std::stof(res->getString("game_parameter1_weight"));
            JPGR.game_parameter1_value = std::stoi(res->getString("game_parameter1_value"));

            JPGR.game_parameter2_name = res->getString("game_parameter2_name");
            JPGR.game_parameter2_weight = std::stof(res->getString("game_parameter2_weight"));
            JPGR.game_parameter2_value = std::stoi(res->getString("game_parameter2_value"));

            JPGR.game_parameter3_name = res->getString("game_parameter3_name");
            JPGR.game_parameter3_weight = std::stof(res->getString("game_parameter3_weight"));
            JPGR.game_parameter3_value = std::stoi(res->getString("game_parameter3_value"));

            JPGR.game_parameter4_name = res->getString("game_parameter4_name");
            JPGR.game_parameter4_weight = std::stof(res->getString("game_parameter4_weight"));
            JPGR.game_parameter4_value = std::stoi(res->getString("game_parameter4_value"));

            JPGR.category = res->getString("category");
            JPGR.players_per_team = std::stoi(res->getString("players_per_team"));
            JPGR.teams_per_match = std::stoi(res->getString("teams_per_match"));
            std::cout << JPGR.toString() << std::endl;
        }

        delete prep_stmt;
        delete res;
        delete con;

        std::cout << "Successfully retrieved rating in game with game_id: " + std::to_string(game_id) + " for player with email: " + player_email<< std::endl;
        return JPGR;

    } catch (sql::SQLException &e) {
        std::cout << "Error getting rating in game with game_id: " + std::to_string(game_id) + " for player with email: " + player_email<< std::endl;
        std::cout << "# ERR: SQLException in " << __FILE__;
        std::cout << "(" << __FUNCTION__ << ") on line "<< __LINE__ << std::endl;
        std::cout << "# ERR: " << e.what();
        std::cout << " (MySQL error code: " << e.getErrorCode();
        std::cout << ", SQLState: " << e.getSQLState() <<" )" << std::endl;
        return JPGR;
    }
}

std::vector<Player> get_all_players(){
    std::cout << "Connecting to MYSQL to get all players" << std::endl;
    std::vector<Player> players;

    try {
        sql::Driver *driver;
        sql::Connection *con;
        sql::Statement *stmt;
        sql::ResultSet *res;
        Player p;

        driver = get_driver_instance();
        con = driver->connect(hostname, username, password);

        con->setSchema(database);

        stmt = con->createStatement();
        res = stmt->executeQuery("SELECT * FROM Players");
        while (res->next()) {
            p.player_email = res->getString("player_email");
            std::cout << p.toString() << std::endl;
            players.push_back(p);
        }

        delete stmt;
        delete res;
        delete con;

        std::cout << "Successfully retrieved all players" << std::endl;
        return players;

    } catch (sql::SQLException &e) {
        std::cout << "Error getting all players" << std::endl;
        std::cout << "# ERR: SQLException in " << __FILE__;
        std::cout << "(" << __FUNCTION__ << ") on line "<< __LINE__ << std::endl;
        std::cout << "# ERR: " << e.what();
        std::cout << " (MySQL error code: " << e.getErrorCode();
        std::cout << ", SQLState: " << e.getSQLState() <<" )" << std::endl;
        return players;
    }

}

std::vector<Developer> get_all_developers() {
    std::cout << "Connecting to MYSQL to get all developers" << std::endl;
    std::vector<Developer> developers;

    try {
        sql::Driver *driver;
        sql::Connection *con;
        sql::Statement *stmt;
        sql::ResultSet *res;
        Developer d;

        driver = get_driver_instance();
        con = driver->connect(hostname, username, password);

        con->setSchema(database);

        stmt = con->createStatement();
        res = stmt->executeQuery("SELECT * FROM Developers");
        while (res->next()) {
            d.developer_email = res->getString("developer_email");
            d.developer_password = res->getString("developer_password");
            std::cout << d.toString() << std::endl;
            developers.push_back(d);
        }

        delete stmt;
        delete res;
        delete con;

        std::cout << "Successfully retrieved all developers" << std::endl;
        return developers;

    } catch (sql::SQLException &e) {
        std::cout << "Error getting all developers" << std::endl;
        std::cout << "# ERR: SQLException in " << __FILE__;
        std::cout << "(" << __FUNCTION__ << ") on line "<< __LINE__ << std::endl;
        std::cout << "# ERR: " << e.what();
        std::cout << " (MySQL error code: " << e.getErrorCode();
        std::cout << ", SQLState: " << e.getSQLState() <<" )" << std::endl;
        return developers;
    }
}

std::vector<Game_Details> get_all_games() {
    std::cout << "Connecting to MYSQL to get all game details" << std::endl;
    std::vector<Game_Details> game_details;

    try {
        sql::Driver *driver;
        sql::Connection *con;
        sql::Statement *stmt;
        sql::ResultSet *res;
        Game_Details gd;

        driver = get_driver_instance();
        con = driver->connect(hostname, username, password);

        con->setSchema(database);

        stmt = con->createStatement();
        res = stmt->executeQuery("SELECT * FROM Game_Details");
        while (res->next()) {
            gd.game_id = std::stoi(res->getString("game_id"));
            gd.developer_email = res->getString("developer_email");
            gd.game_name = res->getString("game_name");
            gd.game_parameter1_name = res->getString("game_parameter1_name");
            gd.game_parameter1_weight = std::stof(res->getString("game_parameter1_weight"));

            gd.game_parameter2_name = res->getString("game_parameter2_name");
            gd.game_parameter2_weight = std::stof(res->getString("game_parameter2_weight"));

            gd.game_parameter3_name = res->getString("game_parameter3_name");
            gd.game_parameter3_weight = std::stof(res->getString("game_parameter3_weight"));

            gd.game_parameter4_name = res->getString("game_parameter4_name");
            gd.game_parameter4_weight = std::stof(res->getString("game_parameter4_weight"));

            gd.category = res->getString("category");
            gd.players_per_team = std::stoi(res->getString("players_per_team"));
            gd.teams_per_match = std::stoi(res->getString("teams_per_match"));
            std::cout << gd.toString() << std::endl;
            game_details.push_back(gd);
        }

        delete stmt;
        delete res;
        delete con;

        std::cout << "Successfully retrieved all game details" << std::endl;
        return game_details;

    } catch (sql::SQLException &e) {
        std::cout << "Error getting all game details" << std::endl;
        std::cout << "# ERR: SQLException in " << __FILE__;
        std::cout << "(" << __FUNCTION__ << ") on line "<< __LINE__ << std::endl;
        std::cout << "# ERR: " << e.what();
        std::cout << " (MySQL error code: " << e.getErrorCode();
        std::cout << ", SQLState: " << e.getSQLState() <<" )" << std::endl;
        return game_details;
    }
}


std::vector<Joined_Player_Game_Ratings> get_all_player_game_ratings_for_game(int game_id) {
    std::cout << "Connecting to MYSQL to get all player ratings for a game" << std::endl;
    std::vector<Joined_Player_Game_Ratings> JPGR;

    try {
        sql::Driver *driver;
        sql::Connection *con;
        sql::PreparedStatement  *prep_stmt;
        sql::ResultSet *res;
        Joined_Player_Game_Ratings jpgr;

        driver = get_driver_instance();
        con = driver->connect(hostname, username, password);

        con->setSchema(database);

        prep_stmt = con->prepareStatement("SELECT PGR.*, GD.* FROM Players P JOIN Player_Game_Ratings PGR ON P.player_email = PGR.player_email JOIN Game_Details GD ON PGR.game_id = GD.game_id WHERE GD.game_id = ?;");

        prep_stmt->setInt(1, game_id);

        res = prep_stmt->executeQuery();
        while (res->next()) {
            jpgr.player_email = res->getString("player_email");
            jpgr.game_id = std::stoi(res->getString("game_id"));
            jpgr.developer_email = res->getString("developer_email");
            jpgr.game_name = res->getString("game_name");
            jpgr.game_parameter1_name = res->getString("game_parameter1_name");
            jpgr.game_parameter1_weight = std::stof(res->getString("game_parameter1_weight"));
            jpgr.game_parameter1_value = std::stoi(res->getString("game_parameter1_value"));

            jpgr.game_parameter2_name = res->getString("game_parameter2_name");
            jpgr.game_parameter2_weight = std::stof(res->getString("game_parameter2_weight"));
            jpgr.game_parameter2_value = std::stoi(res->getString("game_parameter2_value"));

            jpgr.game_parameter3_name = res->getString("game_parameter3_name");
            jpgr.game_parameter3_weight = std::stof(res->getString("game_parameter3_weight"));
            jpgr.game_parameter3_value = std::stoi(res->getString("game_parameter3_value"));

            jpgr.game_parameter4_name = res->getString("game_parameter4_name");
            jpgr.game_parameter4_weight = std::stof(res->getString("game_parameter4_weight"));
            jpgr.game_parameter4_value = std::stoi(res->getString("game_parameter4_value"));

            jpgr.category = res->getString("category");
            jpgr.players_per_team = std::stoi(res->getString("players_per_team"));
            jpgr.teams_per_match = std::stoi(res->getString("teams_per_match"));
            std::cout << jpgr.toString() << std::endl;
            JPGR.push_back(jpgr);
        }

        delete prep_stmt;
        delete res;
        delete con;

        std::cout << "Successfully retrieved all player game ratings" << std::endl;
        return JPGR;

    } catch (sql::SQLException &e) {
        std::cout << "Error getting all player game ratings" << std::endl;
        std::cout << "# ERR: SQLException in " << __FILE__;
        std::cout << "(" << __FUNCTION__ << ") on line "<< __LINE__ << std::endl;
        std::cout << "# ERR: " << e.what();
        std::cout << " (MySQL error code: " << e.getErrorCode();
        std::cout << ", SQLState: " << e.getSQLState() <<" )" << std::endl;
        return JPGR;
    }
}


Developer add_developer(Developer D);
Player add_player(Player P);
Game_Details add_game_details(Game_Details GD);
Player_Game_Ratings add_player_rating(Player_Game_Ratings PGR);

Developer remove_developer(std::string developer_email);
Player remove_player(std::string player_email);
Game_Details remove_game_details(int game_id);
Player_Game_Ratings remove_player_rating(std::string player_email, int game_id);

Developer update_developer(Developer D);
Player update_player(Player P);
Game_Details update_game_details(Game_Details GD);
Player_Game_Ratings update_player_rating(Player_Game_Ratings PGR);

std::vector<Game_Details> get_all_games_for_developer(std::string developer_email);
