/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Client
*/

#include "Client.hpp"
#include "ErrorHandling.hpp"
#include <stdlib.h>
#include <cstdlib>

// Constructeur de la classe Client, gère la gestion des paramètre et de
// connexion.
Client::Client(int ac, char **av)
{
    setParams(ac, av);
    connectClient();
    _turns = 0;
    _level = 1;
    channelId = 0;
    _objective = FARM;
    _waitingAssemble = false;
    _assembleOwner = false;
    _waitIncant = false;
    _waitingCanal = -1;
    _shareLocation = false;
    _goAssemble = false;
    _amIBalise = false;
    try {
        IAstart();
    } catch (justDied &e) {
        std::cout << e.what() << std::endl;
    }
}

// Destructeur de la classe Client, ferme la socket correspondante.
Client::~Client()
{
    close(_socket);
}

// fonction de debug, affichant le contenus de l'inventaire connus par l'IA.
void Client::dispInfos(void) const
{
    std::cout << "===============dispInfos===================" << std::endl;
    printf("Inventory: \n");
    printf("Level: %d", _level);
    if (_amIBalise)
        printf("\tBALISE\n");
    else
        printf("\n");
    printf("food: %d\nlinemate: %d\tderaumere: %d\tsibur: %d\nmendiane: %d\tphiras: %d\tthystame: %d\n",
    _inventory.food, _inventory.linemate, _inventory.deraumere, _inventory.sibur, _inventory.mendiane, _inventory.phiras, _inventory.thystame);
    std::cout << "===========================================" << std::endl;
}

// cette fonction prends en arguments ceux envoyés au binaire et les range dans
// la classe Client, des paramètres par défaut y sont définis.
void Client::setParams(int ac, char **av)
{
    std::vector<std::string> args;

    _port = 4242;
    _name = "team1\n";
    _machine = "127.0.0.1";
    for (int i = 1; i < ac; i++) {
        std::string tmp = av[i];
        args.push_back(tmp);
    }
    int sig = 0;
    for (auto it : args) {
        if (it  == "-p")
            sig = 1;
        if (it  == "-n")
            sig = 2;
        if (it == "-h")
            sig = 3;
        if (it == "-p" || it == "-n" || it == "-h")
            continue;
        if (sig == 1)
            _port = std::stoi(it.c_str());
        if (sig == 2)
            _name = it + "\n";
        if (sig == 3)
            _machine = it;
        sig = 0;
    }
    // debug
    // printf("CLIENT: port:%d name: %s machine: %s\n", _port, _name.c_str(), _machine.c_str());
}

// Cette fonction fait la connection du client vers le serveur
void Client::connectClient(void)
{
    sockaddr_in server;
    char rcvBuffer[1024];

    _socket = socket(AF_INET, SOCK_STREAM, 0);
    if (_socket == -1)
        throw(SocketError());

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(_machine.c_str());
    server.sin_port = htons(_port);
    if (connect(_socket, (struct sockaddr*)&server, sizeof(server)) < 0)
        throw(ConnexionError());

    recv(_socket, rcvBuffer, 1024, 0);
    rcvBuffer[0] = '\0';
    if (send(_socket, _name.c_str(), _name.size(), 0) == -1)
        std::cout << "Send error" << std::endl;
    ssize_t byteRead = recv(_socket, rcvBuffer, 200, 0);
    rcvBuffer[byteRead] = '\0';
    std::string response = rcvBuffer;
    if (response == "ko\n")
        throw invalidTeam("Invalid Team, cannot connect");
    baliseDiscussion("Am i balise?");
}

void Client::extractPattern(const std::string& input, std::string& message, double& number1, double& number2, double& number3)
{
    // Pattern de recherche
    std::regex pattern("hel([0-9.]+)\\.([0-9.]+)\\.([0-9.]+)lo\\s(.*)");

    // Recherche du motif dans la chaîne d'entrée
    std::smatch match;
    if (std::regex_match(input, match, pattern)) {
        if (match.size() == 5) {
            // Récupération des trois nombres et du message
            number1 = std::stod(match[1]);
            number2 = std::stod(match[2]);
            number3 = std::stod(match[3]);
            message = match[4];
        }
    }
}

void Client::acceptBroadcast(std::string str)
{
    std::string message;
    double number1, number2, number3;

    size_t numberStartPos = str.find("message") + 8;
    size_t commaPos = str.find(",", numberStartPos);

    std::string numberString = str.substr(numberStartPos, commaPos - numberStartPos);

    int number = std::stoi(numberString);

    size_t textStartPos = commaPos + 2;

    size_t newlinePos = str.find("\n", textStartPos);
    std::string text = str.substr(textStartPos, newlinePos - textStartPos);

    if (text == "hel0lo Am i balise?") {
        std::cout << "Received Am i Balise?" << std::endl;
        std::size_t id = _broadcasts[0].size();
        _broadcasts[0][(int)id] = {"Am i balise?", number, std::chrono::system_clock::now()};
        if (_amIBalise)
            anwserDiscussion(0, "Got this");
        return;
    }

    extractPattern(text, message, number1, number2, number3);

    if (message.empty()) {
        std::cerr << "Not adding this message" << std::endl;
        return;
    }

    if (message == "Got this") {
        std::size_t id = _broadcasts[0].size();
        _broadcasts[0][(int)id] = {"Got this", number, std::chrono::system_clock::now()};
        return;
    }

    auto it1 = _broadcasts.find(number1);
    if (it1 != _broadcasts.end()) {
        auto it2 = it1->second.find(number2);
        if (it2 != it1->second.end()) {
            std::cerr << "Ajouts multiples de broadcasts" << std::endl;
            std::cerr << "on: " << number1 << ":" << number2 << " -> " << message << std::endl;
            return;
        } else {
            std::cout << "Broadcast on " << number1 << ":" << number2 << " -> " << message << std::endl;
            _broadcasts[number1][number2] = {message, number, std::chrono::system_clock::now()};
        }
    } else if (number2 != 0) {
        std::cerr << "Ajout de broadcast interdit" << std::endl;
        return;
    } else {
        std::cout << "Broadcast on " << number1 << ":" << number2 << " -> " << message << std::endl;
        _broadcasts[number1][number2] = {message, number, std::chrono::system_clock::now()};
    }
    if (number3 != channelId)
        channelId = number3;
}

void Client::serverActivity(std::string buffer)
{
    if (buffer == "dead") {
        throw justDied("IA just died");
    } else if (my_strncmp(buffer, "message ", 8)) {
        acceptBroadcast(buffer);
    }
}

// //- test pour passer lvl 2
// if (it == "linemate" && _level == 1) {
//     // printf("LINEMATE ON TILE\n");
//     startIncantation();
//     break;
// }
// //-
//- test IA grouping to elevate
// if (_level > 1 && haveAllReqStones()) {
//     broadcast("Need lvl 2 here.");
//     // printf("recv OK ---------------------------\n");
//     // dispInfos();
//     while (1)
//         ;
// }

std::vector<std::string> Client::splitStringByNewline(const std::string& inputString)
{
    std::vector<std::string> result;
    std::size_t startPos = 0;
    std::size_t foundPos = inputString.find('\n');

    while (foundPos != std::string::npos) {
        std::string line = inputString.substr(startPos, foundPos - startPos);
        result.push_back(line);

        startPos = foundPos + 1;
        foundPos = inputString.find('\n', startPos);
    }

    if (startPos < inputString.length()) {
        std::string lastLine = inputString.substr(startPos);
        result.push_back(lastLine);
    }

    return result;
}

bool Client::my_strncmp(std::string str1, std::string str2, std::size_t n)
{
    if (str1.length() < n || str2.length() < n) {
        return false;
    }

    return str1.compare(0, n, str2, 0, n) == 0;
}

std::string Client::wait_recv(std::string wanted)
{
    char rcvBuffer[BUFFER_SIZE];
    std::string rcv;
    bool wanted_found = false;
    std::string returnStr;

    while (!wanted_found) {
        rcvBuffer[0] = '\0';
        recv(_socket, rcvBuffer, BUFFER_SIZE, 0);
        rcv = rcvBuffer;
        std::vector<std::string> strings = splitStringByNewline(rcv);
        for (auto it : strings) {
            if (it.compare(0, wanted.size(), wanted) == 0) {
                wanted_found = true;
                returnStr = it;
            } else
                serverActivity(it);
        }
    }
    return returnStr;
}

std::string Client::wait_recv(std::string wanted1, std::string wanted2)
{
    char rcvBuffer[BUFFER_SIZE];
    std::string rcv;
    bool wanted_found = false;
    std::string returnStr;

    while (!wanted_found) {
        rcvBuffer[0] = '\0';
        recv(_socket, rcvBuffer, BUFFER_SIZE, 0);
        rcv = rcvBuffer;
        std::vector<std::string> strings = splitStringByNewline(rcv);
        for (auto it : strings) {
            if (it.compare(0, wanted1.size(), wanted1) == 0 ||
                it.compare(0, wanted2.size(), wanted2) == 0) {
                wanted_found = true;
                returnStr = it;
            } else
                serverActivity(it);
        }
    }
    return returnStr;
}
