/*
** EPITECH PROJECT, 2023
** GUI
** File description:
** socketTunel
*/

#ifndef SOCKETTUNEL_HPP_
#define SOCKETTUNEL_HPP_

    #include "socket.hpp"
    #include "content.hpp"
    #include <sstream>
    #include <string>
    #include <vector>
    #include <memory>

    class SocketTunnel {
        public:
            SocketTunnel(Socket *_socketId, Content *_content);
            ~SocketTunnel();
            void Routine();
            std::vector<std::string> Parse (std::string str);
            std::vector<std::string> Parse_lign (std::string str);
            void tunelFactory(std::vector<std::string> vectorParsed);
            void restart();
        private:
            Socket *_socketId;
            std::vector<std::string> _line;
            Content *_content;
    };

#endif /* !SOCKETTUNEL_HPP_ */
