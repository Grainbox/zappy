/*
** EPITECH PROJECT, 2023
** GUI
** File description:
** CONTENT_HPP_
*/

#ifndef CONTENT_HPP_
#define CONTENT_HPP_

    #include <iostream>
    #include <vector>
    #include <map>
    #include <algorithm>
    #include <utility>
    #include <memory>
    #include <exception>
    #include "raylib.h"
    #include <random>

    class FactoryError : public std::exception {
        private:
            std::string message_;

        public:
            FactoryError(const std::string& message) : message_(message) {}

            const char* what() const noexcept override {
                return message_.c_str();
            }
    };

    class Position {
        public:
            Position(int x = 0, int y = 0, int o = 0) : x(x), y(y), o(o) {};
            int getX () { return x; };
            int getY () { return y; };
            void setX (int _x) {
                x = _x;
            };
            void setY (int _y) {
                y = _y;
            };
            std::map<std::string, int> getPosition () {
                std::map<std::string, int> myMap;
                myMap["x"] = x;
                myMap["y"] = y;
                return myMap;
            };
            ~Position() {};
            int getOrientation () { return o; };
            void setOrientation (int _o) { o = _o; };
        private:
            int x;
            int y;
            int o;
    };

    class Team {
        public:
            Team (std::string name) : teamName(name) {};
            ~Team () {};
            std::string getName () { return teamName; };
            void setEnabled (bool _enabled) { enabled = _enabled; };
            bool getEnabled () { return enabled; };
            Color getColor () { return teamColor; };
            Color genColor () {
                    std::random_device rd;
                    std::mt19937 gen(rd());
                    std::uniform_int_distribution<> dis(140, 255);
                    unsigned char r = static_cast<unsigned char>(dis(gen));
                    unsigned char g = static_cast<unsigned char>(dis(gen));
                    unsigned char b = static_cast<unsigned char>(dis(gen));
                    Color back = { r, g, b, 255 };
                    return back;
            }
            void setColor (int r, int g, int b, int a) {
                teamColor.r = r;
                teamColor.g = g;
                teamColor.b = b;
                teamColor.a = a;
            };
        private:
            std::string teamName;
            bool enabled = true;
            Color teamColor = {0, 0, 0, 255};
    };

    class Egg {
        public:
            Egg(Position pos, int id) : pos(pos), id(id) {
                isAlive = true;
            };
            ~Egg() = default;

            Position getPos() { return this->pos; };
            void setPos(Position pos) { this->pos = pos; };
            int getId() { return this->id; };
            void setId(int id) { this->id = id; };
            bool isAlive;
        private:
            Position pos;
            int id;
    };

    class Resource {
        public:
            Resource (int _food = 0, int _linemate = 0, int _deraumere = 0, int _sibur = 0, int _mendiane = 0, int _phiras = 0, int _thystame = 0) \
            : food(_food), linemate(_linemate), deraumere(_deraumere), sibur(_sibur), mendiane(_mendiane), phiras(_phiras), thystame(_thystame) {};
            ~Resource () {};
            int getFood() { return food; };
            int getLinemate() { return linemate; };
            int getDeraumere() { return deraumere; };
            int getSibur() { return sibur; };
            int getMendiane() { return mendiane; };
            int getPhiras() { return phiras; };
            int getThystame() { return thystame; };

            void setFood(int _food) { food = _food; };
            void setLinemate(int _linemate) { linemate = _linemate; };
            void setDeraumere(int _deraumere) { deraumere = _deraumere; };
            void setSibur(int _sibur) { sibur = _sibur; };
            void setMendiane(int _mendiane) { mendiane = _mendiane; };
            void setPhiras(int _phiras) { phiras = _phiras; };
            void setThystame(int _thystame) { thystame = _thystame; };
        private:
            int food; // q0
            int linemate; // q1
            int deraumere; // q2
            int sibur; // q3
            int mendiane; // q4
            int phiras; // q5
            int thystame; // q6
    };

    class Player {
        public:
            Player (Position _pos, int _id, Team new_team) : pos(_pos), team(new_team), id(_id) {
                Resource _inventory;
                inventory = _inventory;
                isAlive = true;
            };
            ~Player () {};

            Team getTeam() { return team; };
            void setTeam(Team _team) { team = _team; };

            void setPos (Position _pos) { pos = _pos; };
            Position *getPos() { return &pos; };
            int getId () { return id; };
            int getLevel () { return level; };
            void setLevel (int _level = 0) { level = _level; };
            Resource getInventory () { return inventory; };
            void setInventory (Resource _inventory) { inventory = _inventory; };
            bool getVisible () { return visible; };
            void kill () { visible = false; };
            Position pos;
            bool isLayingEgg; // reset auto
            bool isDroppingResource; // !reset auto
            bool isCollectingResource; // !reset auto
            int nbDroppedResources;
            int nbCollectingResources;
            bool isSelected = false;
            bool isAlive;
        private:
            Team team;
            int id;
            int level = 0;
            Resource inventory;
            bool visible = true;
    };

    struct playerTeam {
        Team team;
        std::vector<Player*> players;
    };

    struct incantation {
        bool is_running;
        int level;
        int result;
        std::vector<Player> players;
    };

    class Tile {
        public:
            Tile () { init(); };
            ~Tile () {};
            Position *getPos () { return &pos; };
            Resource *getResource () { return &resource; };
            incantation getIncantation() { return _incantation; };
            void setIncantation(incantation incantation) { this->_incantation = incantation; };
            void init();
            bool isSelected = false;
            bool isNull = false;
        private:
            Position pos;
            Resource resource;
            incantation _incantation;
    };

    class Content {
        public:
            Content ();
            ~Content () {};
            std::pair<int, int> getMapSize ();
            std::vector<Tile> *getMapTile () { return &mapTile; };
            std::vector<Player> getPlayerList () { return playerList; };
            std::vector<Team> getTeamList () { return TeamList; };
            std::vector<Egg> getEggList() {
                std::vector<Egg> eggs;
                eggs.reserve(eggList.size());  // Reserve space for efficiency

                for (const auto& eggPtr : eggList)
                    eggs.push_back(std::move(*eggPtr));
                return eggs;
            };
            std::vector<std::string> getMessageList() { return messageList; };

            std::string getBroadcastString () { return broadcastString; };
            Tile *getTileByPos(Vector3 _pos);

            void setBroadcastString (std::string _broadcastString) { broadcastString = _broadcastString; };
            bool getBcShow () { return broadcastStringShow; };
            void setBcShow (bool _broadcastShow) { broadcastStringShow = _broadcastShow; };

            int getTimeUnit() { return this->time_unit; };

            void sortScoreBoard ();
            std::vector<playerTeam> getScoreboardSorted () { return _scoreBoard; };
            static bool comparePlayers(Player* player1, Player* player2);
            static bool compareTeams(playerTeam& team1, playerTeam& team2);

            void removePlayer(int id);
            void removeEgg(int id);

            void setMapSize (std::vector<std::string> _vector);
            void bct (std::vector<std::string> _vector);
            void tna (std::vector<std::string> _vector);
            void pnw (std::vector<std::string> _vector);
            void ppo (std::vector<std::string> _vector);
            void plv (std::vector<std::string> _vector);
            void pin (std::vector<std::string> _vector);
            void pex (std::vector<std::string> _vector);
            void pbc (std::vector<std::string> _vector);
            void pic (std::vector<std::string> _vector);
            void pie (std::vector<std::string> _vector);
            void pfk (std::vector<std::string> _vector);
            void pdr (std::vector<std::string> _vector);
            void pgt (std::vector<std::string> _vector);
            void pdi (std::vector<std::string> _vector);
            void enw (std::vector<std::string> _vector);
            void ebo (std::vector<std::string> _vector);
            void edi (std::vector<std::string> _vector);
            void sgt (std::vector<std::string> _vector);
            void sst (std::vector<std::string> _vector);
            void seg (std::vector<std::string> _vector);
            void smg (std::vector<std::string> _vector);
            void suc (std::vector<std::string> _vector);
            void sbp (std::vector<std::string> _vector);

            int getNPlayerByTile (Tile *_tile);

        private:
            int mapSizeX = 0;
            int mapSizeY = 0;
            std::vector<Tile> mapTile;
            std::vector<Player> playerList;
            std::vector<Team> TeamList;
            std::vector<playerTeam> _scoreBoard;
            std::vector<std::unique_ptr<Egg>> eggList;
            std::vector<std::string> messageList;

            std::string broadcastString;
            bool broadcastStringShow = false;
            int time_unit;
    };

#endif /* !EVENT_HPP_ */
