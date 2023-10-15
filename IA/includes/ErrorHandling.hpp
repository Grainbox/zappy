/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** ErrorHandling
*/

#ifndef ERRORHANDLING_HPP_
#define ERRORHANDLING_HPP_

    #include <exception>
    #include <vector>
    #include <string>
    #include <iostream>
    #include <filesystem>

class sendCommandError : public std::exception {
public:
    sendCommandError(std::string command)
        { returnStr = "send '" + command + "' error"; };
    ~sendCommandError() = default;

    std::string returnStr;

    const char* what() const noexcept override
    {
        return returnStr.c_str();
    }
};

class setInventoryError : public std::exception {
    public:
        setInventoryError() = default;
        ~setInventoryError() = default;

        const char* what() const noexcept override
        {
            return "set inventory error";
        }
};

class ArgNumberError : public std::exception {
    public:
        ArgNumberError() = default;
        ~ArgNumberError() = default;

        const char* what() const noexcept override
        {
            return "Wrong argument";
        }
};

class HelpDisplay : public std::exception {
    public:
        HelpDisplay() = default;
        ~HelpDisplay() = default;
    const char* what() const noexcept override
        {
            return "Displaying help";
        }
};

class ConnexionError : public std::exception {
    public:
        ConnexionError() = default;
        ~ConnexionError() = default;

        const char* what() const noexcept override
        {
            return "Connexion error";
        }
};

class SocketError : public std::exception {
    public:
        SocketError() = default;
        ~SocketError() = default;

        const char* what() const noexcept override
        {
            return "Socket creation error";
        }
};

#endif
