/*
** EPITECH PROJECT, 2023
** GUI
** File description:
** window
*/

#ifndef WINDOW_HPP_
#define WINDOW_HPP_

    #include "content.hpp"
    #include "raylib.h"
    #include "socketTunel.hpp"
    #include <memory>
    #include "socket.hpp"

    class WindowError : public std::exception {
        private:
            std::string message_;

        public:
            WindowError(const std::string& message) : message_(message) {}

            const char* what() const noexcept override {
                return message_.c_str();
            }
    };

    class CollisionObject {
        public:
            CollisionObject () = default;
            ~CollisionObject () = default;
            Ray ray;
            RayCollision collision;
            Vector3 position;
    };

    class window {
        public:
            window (Content *content, Socket *_socket);
            ~window ();
            void run ();
        private:
            void display ();
            void eventHandler ();
            void update ();
            void updateCubePositions();
            void updatePlayerPositions();
            void moveCameraWithMouse ();
            void moveCamera ();
            void mouseClick ();
            void tabHandle ();
            void drawInfo ();
            void drawTab ();
            void drawResources();
            void drawResource(Tile &tile, Vector3 *offset, int (Resource::*getter)(), const Color &color);
            void drawPlayer();
            void drawCubes();
            void drawCubeBasedOnPosition(const Vector3& position, const Vector3& focus, const Vector3& handle);
            std::unique_ptr<SocketTunnel> _socketTunnel;
            Content *_content;
            std::map<std::string, Rectangle> buttons;
            std::map<std::string, bool> eventBool;
            std::vector<Vector3> cubePosition;
            Vector3 getCubePos(int x, int y);
            std::vector<Vector3> _playerPosition;
            std::vector<CollisionObject> _collisionObject;
            float cube_size = 2.0;
            Camera3D camera;
            Vector3 start;
            Vector3 current_focus;
            Vector3 current_handle;
            Vector3 end;
            Ray ray;
            RayCollision collisionBlock;
            RayCollision collisionBlockHandle;
            RayCollision collisionPlayer;
            bool display_info = false;
            bool display_tab = false;
            Tile *tile_current;
            std::shared_ptr<Socket> _socketId;
            bool checkMouseClickInsideButton(int buttonX, int buttonY, int buttonWidth, int buttonHeight);
    };
    bool operator==(const Vector3& lhs, const Vector3& rhs);


#endif /* !WINDOW_HPP_ */
