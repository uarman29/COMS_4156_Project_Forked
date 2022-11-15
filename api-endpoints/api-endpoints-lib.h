// Copyright [2022] RaisingCanesFanClub

#ifndef API_ENDPOINTS_API_ENDPOINTS_LIB_H_
#define API_ENDPOINTS_API_ENDPOINTS_LIB_H_

#include <glog/logging.h>
#include <jsoncpp/json/json.h>  // JsonCpp header file
#include <cmath>
#include <cstdlib>              // EXIT_FAILURE
#include <string>
#include <iostream>
#include <sstream>              // std::stringstream
#include <tuple>
#include <vector>
#include <fstream>
#include <utility>              // std::pair, std::make_pair
#include "crow/crow_all.h"
#include "main/db-service.h"

// cpplint --linelength=100 ./main/* ./testing/*

class APIEndPoints {
 private:
DBService* DB;  // a DB service to use for api calls
bool onHeap;    // whether the DB service object is allocated on heap
// Checks whether supplied username and password are valid
// helper for all API calls that require authentication before proceeding
std::pair<int, std::string> authenticateBadly(const crow::request& req);

// Checks whether supplied token is valid for client
// helper for all API calls (other than login)
// that require authentication of a token before proceeding
std::pair<int, std::string> authenticateToken(const crow::request& req);

std::tuple<
std::vector<std::vector<std::vector<std::string> > >,
std::vector<std::string> > matchmakingBackend(int game_id, std::vector<std::string> player_emails);

 public:
APIEndPoints() : DB(new DBService()), onHeap(true) {}  // default constructor
APIEndPoints(DBService* db, bool dbOnHeap = false) : DB(db), onHeap(dbOnHeap) {}
~APIEndPoints() {if (onHeap) { delete DB; }}

// All API Endpoints
// Take in a crow request and return a pair of (int, string)
// Crow routes initialized in our main function wrap calls to these methods
// Input: takes in a crow request
// On success, returns a pair of (200, reponseBody),
//    where responseBody = JSON string
// On failure, returns a pair of (400 or 401, failResponseBody)
//    where failResponseBody = empty string "" or error message

// Gets all client's games
// Response Body Details:
// Games [Array<Game>]
// Where a Game object looks as such
// game.id [String]
// game.name [String]
// game.category [String]
// game.parameters [Array<String>]
// game.weights [Array<Float>]
// game.teamsPerMatch [Integer]
// game.minPlayersPerTeam [Integer]
// game.maxPlayersPerTeam [Integer]
std::pair <int, std::string> getGames(const crow::request& req);

// Adds a list of games to client's account
// Request Parameters:
// Games [Array<Game>]
// Where a Game object looks as such
// Name [String] REQUIRED
// Parameters [Array<String>] REQUIRED
// Parameter-weights [Array<Integer>] REQUIRED
// Min-players-per-team [Integer] REQUIRED
// Max-players-per-team [Integer] REQUIRED
// Category [String] OPTIONAL
std::pair <int, std::string> postGame(const crow::request& req);

crow::response postSignUp(const crow::request& req);
crow::response postLogin(const crow::request& req, DBService* DB);
crow::response deleteLogin(const crow::request& req, DBService* DB);
crow::response matchmake(const crow::request& req, DBService DB);
};
#endif  // API_ENDPOINTS_API_ENDPOINTS_LIB_H_
