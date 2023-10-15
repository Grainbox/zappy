/*
** EPITECH PROJECT, 2023
** GUI
** File description:
** Content
*/

#include "../../includes/class/content.hpp"
#include <sstream>
#include <string>

bool isDigit(const std::string &str) {
    std::istringstream iss(str);
    double nb;
    return (iss >> nb) && (iss.eof());
}

Content::Content ()
{
    this->mapSizeX = 0;
    this->mapSizeY = 0;
    // Tile _tile;
    // mapTile.push_back(_tile);
}

void Tile::init ()
{
    Resource r;
    Position p;

    pos = p;
    resource = r;
    _incantation.is_running = false;
    _incantation.level = 0;
    _incantation.result = -1;
}

void Content::setMapSize (std::vector<std::string> _vector)
{
    if (_vector.size() < 3)
        throw FactoryError("Error Factory: mapSize argument must be \"msz X Y\\n\"");
    if (!isDigit(_vector.at(1)))
        throw FactoryError("Error Factory: mapSize argument X must be number");
    if (!isDigit(_vector.at(2)))
        throw FactoryError("Error Factory: mapSize argument Y must be number");
    this->mapSizeX = std::stoi(_vector.at(1));
    this->mapSizeY = std::stoi(_vector.at(2));
}

std::pair<int, int> Content::getMapSize ()
{
    std::pair<int, int> myPair(this->mapSizeX, this->mapSizeY);
    return myPair;
}

void Content::bct (std::vector<std::string> _vector)
{
    if (_vector.size() != 10)
        return;
    for (int i = 1; i < (int) _vector.size(); i++)
        if (!isDigit(_vector.at(i)))
            throw FactoryError("Error Factory: argument is not digit");
    if (_vector.at(1).empty() || _vector.at(2).empty())
        throw FactoryError("Error Factory: [bct] Invalid Position");
    int x = std::stoi(_vector.at(1));
    int y = std::stoi(_vector.at(2));

    if (_vector.at(3).empty() || _vector.at(4).empty() || _vector.at(5).empty() ||
        _vector.at(6).empty() || _vector.at(7).empty() || _vector.at(8).empty() ||
        _vector.at(9).empty())
        throw FactoryError("Error Factory: [bct] Invalid Vector");
    for (auto &it : mapTile) {
        if (it.getPos()->getX() == x && it.getPos()->getY() == y) {
            it.getResource()->setFood(std::stoi(_vector.at(3)));
            it.getResource()->setLinemate(std::stoi(_vector.at(4)));
            it.getResource()->setDeraumere(std::stoi(_vector.at(5)));
            it.getResource()->setSibur(std::stoi(_vector.at(6)));
            it.getResource()->setMendiane(std::stoi(_vector.at(7)));
            it.getResource()->setPhiras(std::stoi(_vector.at(8)));
            it.getResource()->setThystame(std::stoi(_vector.at(9)));
            return;
        }
    }
    Tile tileTmp;
    tileTmp.getPos()->setX(x);
    tileTmp.getPos()->setY(y);
    tileTmp.getResource()->setFood(std::stoi(_vector.at(3)));
    tileTmp.getResource()->setLinemate(std::stoi(_vector.at(4)));
    tileTmp.getResource()->setDeraumere(std::stoi(_vector.at(5)));
    tileTmp.getResource()->setSibur(std::stoi(_vector.at(6)));
    tileTmp.getResource()->setMendiane(std::stoi(_vector.at(7)));
    tileTmp.getResource()->setPhiras(std::stoi(_vector.at(8)));
    tileTmp.getResource()->setThystame(std::stoi(_vector.at(9)));
    mapTile.push_back(tileTmp);
}

Tile *Content::getTileByPos(Vector3 _pos)
{
    int i = 0;
    float cube_size = 2.0;
    for (auto it : mapTile) {
        Vector3 tileTmp = { (it.getPos()->getX() * cube_size) - (getMapSize().first * cube_size) / 2, cube_size * 0, (it.getPos()->getY() * cube_size) - (getMapSize().second * cube_size) / 2};
        if (tileTmp.x == _pos.x && tileTmp.y == _pos.y && tileTmp.z == _pos.z)
            return &mapTile.at(i);
        i++;
    }
    return nullptr;
}

int Content::getNPlayerByTile (Tile *_tile)
{
    int i = 0;

    for (auto it: getPlayerList()) {
        if (it.getPos()->getX() == _tile->getPos()->getX() && it.getPos()->getY() == _tile->getPos()->getY()) {
            i++;
        }
    }
    return i;
}

void Content::tna (std::vector<std::string> _vector)
{
    if (_vector.size() != 2)
        throw FactoryError("Error Factory: tna out of range");
    for (auto &it : TeamList) {
        if (it.getName() == _vector.at(1))
            return;
    }
    Team tmp(_vector.at(1));
    std::cout << _vector.at(1) << std::endl;
    Color colortmp = tmp.genColor();
    tmp.setColor(colortmp.r, colortmp.g, colortmp.b, colortmp.a);
    TeamList.push_back(tmp);
}

void Content::pnw (std::vector<std::string> _vector)
{
    if (_vector.size() != 7)
        throw FactoryError("Error Factory: pnw out of range");
    for (int i = 1; i < (int) _vector.size() - 1; i++)
        if (!isDigit(_vector.at(i)))
            throw FactoryError("Error Factory: argument is not digit");
    int counter = 0;
    for (auto &it : getTeamList()) {
        if (it.getName() == _vector.back()) {
            int n = std::stoi(_vector.at(1));
            int x = std::stoi(_vector.at(2));
            int y = std::stoi(_vector.at(3));
            int o = std::stoi(_vector.at(4));
            Position _pos (x, y, o);
            Player p (_pos, n, it);
            playerList.push_back(p);
            std::cout << "New Player " << n << " at pos : " << playerList.back().getPos()->getX() << " " << playerList.back().getPos()->getY() << std::endl;
        }
        counter++;
    }
}

bool Content::comparePlayers(Player* player1, Player* player2)
{
    if (player2 == nullptr)
        return false;
    return player1->getLevel() > player2->getLevel();
}

bool Content::compareTeams(playerTeam& team1, playerTeam& team2)
{
    if (team1.players.empty() && team2.players.empty()) {
        return false; // Les deux vecteurs sont vides, donc les équipes sont considérées comme égales.
    } else if (team1.players.empty()) {
        return false; // L'équipe 1 est considérée comme inférieure car son vecteur de joueurs est vide.
    } else if (team2.players.empty()) {
        return true; // L'équipe 2 est considérée comme inférieure car son vecteur de joueurs est vide.
    } else {
        return team1.players.front()->getLevel() > team2.players.front()->getLevel();
    }
}

void Content::sortScoreBoard()
{
    std::vector<playerTeam> playerTeams;
    for (auto& team : getTeamList()) {
        std::vector<Player*> playertmp;
        for (auto& player : getPlayerList()) {
            if (player.getTeam().getName() == team.getName()) {
                playertmp.push_back(&player);
            }
        }
        std::sort(playertmp.begin(), playertmp.end(), comparePlayers);
        playerTeams.push_back({team, playertmp});
    }

    std::sort(playerTeams.begin(), playerTeams.end(), compareTeams);

    _scoreBoard = playerTeams;
}


void Content::ppo (std::vector<std::string> _vector)
{
    if (_vector.size() != 5)
        throw FactoryError("Error Factory: ppo out of range");
    for (int i = 1; i < (int) _vector.size(); i++)
        if (!isDigit(_vector.at(i)))
            throw FactoryError("Error Factory: argument is not digit");
    int n = std::stoi(_vector.at(1));
    int x = std::stoi(_vector.at(2));
    int y = std::stoi(_vector.at(3));
    int o = std::stoi(_vector.at(4));

    for (auto &it : playerList)
        if (it.getId() == n && ((int) x != (int) it.getPos()->getX() || (int) y != (int) it.getPos()->getY())) {
            it.getPos()->setOrientation(o);
            it.getPos()->setX(x);
            it.getPos()->setY(y);
            break;
        }
}

void Content::plv (std::vector<std::string> _vector)
{
    if (_vector.size() != 3)
        throw FactoryError("Error Factory: plv out of range");
    for (int i = 1; i < (int) _vector.size(); i++)
        if (!isDigit(_vector.at(i)))
            throw FactoryError("Error Factory: argument is not digit");
    int n = std::stoi(_vector.at(1));
    int L = std::stoi(_vector.at(2));

    for (auto &it : playerList)
        if (it.getId() == n)
            it.setLevel(L);
}

void Content::pin (std::vector<std::string> _vector)
{
    if (_vector.size() != 11)
        throw FactoryError("Error Factory: pin out of range");
    for (int i = 1; i < (int) _vector.size(); i++)
        if (!isDigit(_vector.at(i)))
            throw FactoryError("Error Factory: argument is not digit");
    int n = std::stoi(_vector.at(1));
    // int x = std::stoi(_vector.at(2));
    // int y = std::stoi(_vector.at(3)); On les utilise pas
    int q0 = std::stoi(_vector.at(4));
    int q1 = std::stoi(_vector.at(5));
    int q2 = std::stoi(_vector.at(6));
    int q3 = std::stoi(_vector.at(7));
    int q4 = std::stoi(_vector.at(8));
    int q5 = std::stoi(_vector.at(9));
    int q6 = std::stoi(_vector.at(10));
    Resource _inventory (q0, q1, q2, q3, q4, q5, q6);

    for (auto &it : playerList)
        if (it.getId() == n)
            it.setInventory(_inventory);
}

void Content::pex (std::vector<std::string> _vector)
{
    if (_vector.size() != 2)
        throw FactoryError("Error Factory: pex out of range");
    for (int i = 1; i < (int) _vector.size(); i++)
        if (!isDigit(_vector.at(i)))
            throw FactoryError("Error Factory: argument is not digit");
    int n = std::stoi(_vector.at(1));
    for (auto &it : playerList)
        if (it.getId() == n)
            it.kill();
}

void Content::pbc (std::vector<std::string> _vector)
{
    std::string message = "";

    for (std::size_t i = 2; i < _vector.size(); i++) {
        message += _vector.at(i);
        message += " ";
    }
    if (!isDigit(_vector.at(1)))
            throw FactoryError("Error Factory: argument is not digit");
    int n = std::stoi(_vector.at(1));
    for (auto &it : playerList) {
        if (it.getId() == n) {
                std::string tmp = _vector.at(1) + " " + message;
                setBroadcastString(tmp);
                setBcShow(true);
        }
    }
}

void Content::seg (std::vector<std::string> _vector)
{
    if (_vector.size() != 2)
        throw FactoryError("Error Factory: seg out of range");
    for (auto &it : getTeamList())
        if (it.getName() == _vector.at(1))
                it.setEnabled(false);
}

void Content::pic (std::vector<std::string> _vector)
{
    if (_vector.size() < 5)
        throw FactoryError("Error Factory: pic out of range");

    int x = std::stoi(_vector.at(1));
    int y = std::stoi(_vector.at(2));
    int level = std::stoi(_vector.at(3));
    std::vector<Player> players;

    for (size_t i = 4; i < _vector.size(); i++) {
        int id = std::stoi(_vector.at(i));
        for (auto &it : playerList)
            if (it.getId() == id)
                players.push_back(it);
    }
    incantation incantation = {true, level, -1, players};

    bool found = false;

    for (auto &it : this->mapTile) {
        if (it.getPos()->getX() == x && it.getPos()->getY() == y) {
            it.setIncantation(incantation);
            found = true;
        }
    }

    if (!found)
        throw FactoryError("Factory Error: Cannot find the position on the map");
}

void Content::pie (std::vector<std::string> _vector)
{
    if (_vector.size() != 4)
        throw FactoryError("Error Factory: pie out of range");
    int x = std::stoi(_vector.at(1));
    int y = std::stoi(_vector.at(2));
    int result = std::stoi(_vector.at(3));

    bool found = false;

    for (auto &it : this->mapTile) {
        if (it.getPos()->getX() == x && it.getPos()->getY() == y) {
            incantation incantation = it.getIncantation();
            incantation.is_running = false;
            incantation.result = result;
            found = true;
        }
    }

    if (!found)
        throw FactoryError("Factory Error: Cannot find the position on the map");
}

void Content::pfk (std::vector<std::string> _vector)
{
    if (_vector.size() != 2)
        throw FactoryError("Error Factory: pfk out of range");

    bool found = false;
    int id = std::stoi(_vector.at(1));

    for (auto &it : playerList)
        if (it.getId() == id) {
            it.isLayingEgg = true;
            found = true;
        }

    if (!found)
        throw FactoryError("Factory Error: Player was not found");
}

void Content::pdr (std::vector<std::string> _vector)
{
    if (_vector.size() != 3)
        throw FactoryError("Error Factory: pdr out of range");

    int id = std::stoi(_vector.at(1));
    int resource_nb = std::stoi(_vector.at(2));
    bool found = false;

    for (auto &it : playerList)
        if (it.getId() == id) {
            it.isDroppingResource = true;
            it.nbDroppedResources = resource_nb;
            found = true;
        }

    if (!found)
        throw FactoryError("Factory Error: Player was not found");
}

void Content::pgt (std::vector<std::string> _vector)
{
    if (_vector.size() != 3)
        throw FactoryError("Error Factory: pgt out of range");

    int id = std::stoi(_vector.at(1));
    int resource_nb = std::stoi(_vector.at(2));
    bool found = false;

    for (auto &it : playerList)
        if (it.getId() == id) {
            it.isCollectingResource = true;
            it.nbCollectingResources = resource_nb;
            found = true;
        }

    if (!found)
        throw FactoryError("Factory Error: Player was not found");
}

void Content::pdi (std::vector<std::string> _vector)
{
    if (_vector.size() != 2)
        throw FactoryError("Error Factory: pdi out of range");

    int id = std::stoi(_vector.at(1));
    bool found = false;

    for (auto &it : playerList)
        if (it.getId() == id) {
            it.isAlive = false;
            found = true;
        }

    if (!found)
        throw FactoryError("Factory Error: Player was not found");
}

void Content::enw (std::vector<std::string> _vector)
{
    if (_vector.size() != 5)
        throw FactoryError("Error Factory: enw out of range");

    int egg_id = std::stoi(_vector.at(1));
    int player_id = std::stoi(_vector.at(2));
    int x = std::stoi(_vector.at(3));
    int y = std::stoi(_vector.at(4));
    bool found = false;

    for (auto &it : playerList)
        if (it.getId() == player_id) {
            it.isLayingEgg = false;
            found = true;
        }

    if (!found)
        throw FactoryError("Factory Error: Player was not found");

    Position pos(x, y, -1);

    std::unique_ptr<Egg> egg = std::make_unique<Egg>(pos, egg_id);
    eggList.push_back(std::move(egg));
}

void Content::ebo (std::vector<std::string> _vector)
{
    if (_vector.size() != 2)
        throw FactoryError("Error Factory: ebo out of range");

    int id = std::stoi(_vector.at(1));
    bool found = false;

    for (auto iter = eggList.begin(); iter != eggList.end(); ) {
        const auto& eggPtr = *iter;
        if (eggPtr->getId() == id) {
            std::unique_ptr<Egg> tempPtr = std::move(const_cast<std::unique_ptr<Egg>&>(*iter));
            iter = eggList.erase(iter);
            found = true;
        } else {
            ++iter;
        }
    }

    if (!found)
        throw FactoryError("Error Factory: Egg was not found");
}

void Content::edi (std::vector<std::string> _vector)
{
    if (_vector.size() != 2)
        throw FactoryError("Error Factory: edi out of range");

    int id = std::stoi(_vector.at(1));
    bool found = false;

    for (auto iter = eggList.begin(); iter != eggList.end(); ) {
        const auto& eggPtr = *iter;
        if (eggPtr->getId() == id) {
            eggPtr->isAlive = false;
            found = true;
        } else {
            ++iter;
        }
    }

    if (!found)
        throw FactoryError("Error Factory: Egg was not found");
}

void Content::sgt (std::vector<std::string> _vector)
{
    if (_vector.size() != 2)
        throw FactoryError("Error Factory: sgt out of range");

    this->time_unit = std::stoi(_vector.at(1));
}

void Content::sst (std::vector<std::string> _vector)
{
    this->sgt(_vector);
}

void Content::smg (std::vector<std::string> _vector)
{
    if (_vector.size() != 2)
        throw FactoryError("Error Factory: smg out of range");

    messageList.push_back(_vector.at(1));
}

void Content::suc (std::vector<std::string> _vector)
{
    (void)_vector;
    std::cerr << "Unknown Command" << std::endl;
}

void Content::sbp (std::vector<std::string> _vector)
{
    std::string msg = "Incorrect Parameter ";
    for (auto i : _vector)
        msg += i;
    std::cerr << msg << std::endl;
}

void Content::removePlayer(int id)
{
    auto it = playerList.begin();
    while (it != playerList.end()) {
        if (it->getId() == id) {
            it = playerList.erase(it);
        } else {
            ++it;
        }
    }
}

void Content::removeEgg(int id)
{
    for (auto iter = eggList.begin(); iter != eggList.end(); ) {
        const auto& eggPtr = *iter;
        if (eggPtr->getId() == id) {
            std::unique_ptr<Egg> tempPtr = std::move(const_cast<std::unique_ptr<Egg>&>(*iter));
            iter = eggList.erase(iter);
        } else {
            ++iter;
        }
    }
}
