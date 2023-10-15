/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Client
*/

#ifndef CLIENT_HPP_
#define CLIENT_HPP_

    #include <string>
    #include <cstring>
    #include <sstream>
    #include <iostream>
    #include <vector>
    #include <sys/socket.h>
    #include <arpa/inet.h>
    #include <unistd.h>
    #include <regex>
    #include <chrono>
    #include "Inventory.hpp"
    #include "ErrorHandling.hpp"
    #include <cmath>

    #define BUFFER_SIZE 1024

class selectError : public std::exception {
    public:
        selectError(std::string command)
            { returnStr = "send '" + command + "' error"; };
        ~selectError() = default;

        std::string returnStr;

        const char* what() const noexcept override
        {
            return returnStr.c_str();
        }
};

class justDied : public std::exception {
    public:
        justDied(std::string command)
            { returnStr = command; };
        ~justDied() = default;

        std::string returnStr;

        const char* what() const noexcept override
        {
            return returnStr.c_str();
        }
};

class invalidTeam : public std::exception {
    public:
        invalidTeam(std::string command)
            { returnStr = command; };
        ~invalidTeam() = default;

        std::string returnStr;

        const char* what() const noexcept override
        {
            return returnStr.c_str();
        }
};

struct Broadcast {
    std::string message;
    int come_from;
    std::chrono::time_point<std::chrono::system_clock> at;
};

class Client {
    public:
        Client(int ac, char **av);
        ~Client();

        enum objective {FOOD, FARM, MOVE, EGG};

        int getPort(void) const { return _port; };
        std::string getName(void) const { return _name; };
        std::string getMachine(void) const { return _machine; };
        void dispInfos(void) const;

    protected:
    private:
        fd_set read_fds;
        int _port;
        std::string _name;
        std::string _machine;
        int _socket;
        void setParams(int ac, char **av);
        void connectClient();

        int channelId;
        bool _amIBalise;

        int _closestFood;
        int _closestStone;

        int mapDimsX;
        int mapDimsY;

        void IAstart(void);
        void serverActivity(std::string buffer);

        void baliseDiscussion(std::string message);
        int startDiscussion(std::string message);
        void anwserDiscussion(int id, std::string message);

        void acceptBroadcast(std::string str);
        std::map<int, std::map<int, Broadcast>> _broadcasts;

        std::vector<std::vector<std::string>> _sight;
        void look(void);
        void parseLook(const std::string &input);
        bool isSeeingFood(void);
        bool isSeeingStone(void);
        bool isAStone(std::string input) const;

        Inventory _inventory;
        void askInventory(void);
        void setInventory(std::string str);

        void take(std::string object);
        void set(std::string object);
        void eject(void);

        bool enoughStone(std::string stone);

        void goForward(void);
        void turnRight(void);
        void turnLeft(void);
        int _turns;
        void goTile(int tile);
        void goDirection(int direction);

        int _level;
        bool isStoneNeeded(std::string stone);
        bool haveAllReqStones(void) const;
        void manageElevation(void);
        bool tileReady(void) const;
        void clearTile(void);
        void setupIncantation(void);
        void startIncantation(void);
        bool _waitIncant;
        bool _assembleOwner;
        int _waitingCanal;
        bool _waitingAssemble;
        bool _shareLocation;
        bool _goAssemble;
        bool enoughBuddies(void);
        bool AssembleIsFull(int size);

        bool my_strncmp(std::string str1, std::string str2, std::size_t n);
        std::vector<std::string> splitStringByNewline(const std::string& inputString);

        void extractPattern(const std::string& input, std::string& message, double& number1, double& number2, double& number3);

        std::string wait_recv(std::string wanted);
        std::string wait_recv(std::string wanted1, std::string wanted2);

        void broadcast(std::string text);
        void askAssemble(void);

        void layEgg(void);

        void setObjectif(void);
        objective _objective;

        void lookForFood(void);
        void lookForStone(void);

        void elevationCall(void);
        void shareLocation(void);
        void lookForCall(void);
        void joinAssemble(void);
        void readCallAnswers(void);
        void readCallGo(void);

        void arrangeTile(std::string stone, int nb);

        int _assembleDirection;
        int _assembleMsgID;

        void assembleOrient(void);
        int seePlayer(void);
};

#endif
