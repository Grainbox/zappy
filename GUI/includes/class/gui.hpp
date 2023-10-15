/*
** EPITECH PROJECT, 2023
** GUI
** File description:
** gui
*/

#ifndef CLASS_GUI
#define CLASS_GUI

    #include "window.hpp"
    #include "socket.hpp"
    #include "socketTunel.hpp"
    #include "content.hpp"
    #include <iostream>
    #include <memory>

    class ArgError : public std::exception {
        private:
            std::string message_;

        public:
            ArgError(const std::string& message) : message_(message) {}

            const char* what() const noexcept override {
                return message_.c_str();
            }
    };

    class arg {
        public:
            arg (int argc, char **argv);
            ~arg() {};
            int getPort() { return port; };
            std::string getName() { return name; };
        private:
            int port = 0;
            std::string name = "127.0.0.1";
    };

    class GUI {
        public:
            GUI (std::shared_ptr<arg> argv);
            ~GUI();
            void process ();
            void debug ();
        private:
            std::unique_ptr<window> _window;
            std::unique_ptr<Socket> _socket;
            std::shared_ptr<arg> _argv;
            std::unique_ptr<Content> _content;
    };

#endif /* !CLASS_GUI */
