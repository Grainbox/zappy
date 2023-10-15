/*
** EPITECH PROJECT, 2023
** GUI
** File description:
** window
*/

#include "class/window.hpp"
#include "raymath.h"

window::window (Content *content, Socket *_socket)
{
    this->_content = content;
    this->_socketTunnel = std::make_unique<SocketTunnel>(_socket, this->_content);
    InitWindow(GetScreenWidth(), GetScreenHeight(), "Zappy GUI");
    SetTargetFPS(60);
    collisionBlock = {0, 0, 0, 0, 0, 0, 0, 0};
    current_handle = {0, 0, 0};
    camera.position = (Vector3){ 10.0f, 10.0f, 10.0f };
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;
}

window::~window ()
{
}

bool operator==(const Vector3 &lhs, const Vector3 &rhs)
{
    return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
}

void window::run ()
{
    while (!WindowShouldClose()) {
        _socketTunnel->Routine();
        update ();
        eventHandler ();
        display ();
        if (IsWindowReady() && IsKeyPressed(KEY_ESCAPE))
            break;
    }
    CloseWindow();
}

Vector3 window::getCubePos(int x, int y)
{
    Vector3 pos = {(y * cube_size) - (_content->getMapSize().second * cube_size) / 2, 0, (x * cube_size) - (_content->getMapSize().first * cube_size) / 2};
    return pos;
}

void window::updateCubePositions ()
{
    cubePosition.clear();
    for (int i = 0; i < _content->getMapSize().second; i++) {
        for (int j = 0; j < _content->getMapSize().first; j++) {
            Vector3 cubePositionTmp = getCubePos(i, j);
            cubePosition.push_back(cubePositionTmp);
        }
    }
}

void window::updatePlayerPositions ()
{
    _playerPosition.clear();
    for (auto it : _content->getPlayerList()) {
        if (it.isAlive) {
            std::map<std::string, int> tmp = it.getPos()->getPosition();
            Vector3 cubePositionTmp = getCubePos(tmp["x"], tmp["y"]);
            cubePositionTmp.y = cube_size - cube_size / 3;
            _playerPosition.push_back(cubePositionTmp);
        }
    }
}

void window::update ()
{
    updateCubePositions();
    updatePlayerPositions();
}

void window::moveCameraWithMouse ()
{
    static bool isMouseButtonDown = false;
    static Vector2 lastMousePosition;

    if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {
        isMouseButtonDown = true;
        lastMousePosition = GetMousePosition();
    } else if (IsMouseButtonReleased(MOUSE_RIGHT_BUTTON)) {
        isMouseButtonDown = false;
    }
    if (isMouseButtonDown) {
        Vector2 currentMousePosition = GetMousePosition();
        float mouseMovementY = currentMousePosition.y - lastMousePosition.y;
        camera.position.y += mouseMovementY * 0.02f; // Ajustez la vitesse de déplacement de la caméra ici
        lastMousePosition = currentMousePosition;
    }
}

void window::moveCamera ()
{
    moveCameraWithMouse();

    // Obtenez la direction de la caméra en soustrayant la position de la cible de la position de la caméra
    Vector3 direction = Vector3Subtract(camera.target, camera.position);
    direction.y = 0;
    direction = Vector3Normalize(direction);
    float moveSpeed = 0.2f;
    if (IsKeyDown(KEY_W)) camera.position = Vector3Add(camera.position, Vector3Scale(direction, moveSpeed));
    if (IsKeyDown(KEY_S)) camera.position = Vector3Subtract(camera.position, Vector3Scale(direction, moveSpeed));
    if (IsKeyDown(KEY_A)) camera.position = Vector3Subtract(camera.position, Vector3Scale(Vector3CrossProduct(direction, camera.up), moveSpeed));
    if (IsKeyDown(KEY_D)) camera.position = Vector3Add(camera.position, Vector3Scale(Vector3CrossProduct(direction, camera.up), moveSpeed));
}

void window::mouseClick()
{
    for (Vector3 it : cubePosition) {
            ray = GetMouseRay(GetMousePosition(), camera);
            RayCollision collisionBlockTMP;
            // Check collision between ray and box
            collisionBlockTMP = GetRayCollisionBox(ray, (BoundingBox){(Vector3){ it.x - cube_size / 2, -it.y - cube_size / 2, it.z - cube_size / 2 }, (Vector3){ it.x + cube_size / 2, it.y + cube_size / 2, it.z + cube_size / 2 }});

            if (collisionBlockTMP.hit) {
                collisionBlockHandle.hit = true;
                current_handle = it;
                break;
            }
        }
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        for (Vector3 it : cubePosition) {
            ray = GetMouseRay(GetMousePosition(), camera);
            RayCollision collisionBlockTMP;
            // Check collision between ray and box
            collisionBlockTMP = GetRayCollisionBox(ray, (BoundingBox){(Vector3){ it.x - cube_size / 2, -it.y - cube_size / 2, it.z - cube_size / 2 }, (Vector3){ it.x + cube_size / 2, it.y + cube_size / 2, it.z + cube_size / 2 }});

            if (collisionBlockTMP.hit) {
                if (collisionPlayer.hit)
                    collisionPlayer.hit = false;
                if (collisionBlock.hit) {
                    collisionBlock.hit = false;
                    display_info = false;
                } else {
                    collisionBlock.hit = true;
                    display_info = true;
                    if (!(tile_current = _content->getTileByPos(it)))
                        throw WindowError("Invalid position");
                    std::cout << "Y = " << tile_current->getPos()->getY() << std::endl;
                }
                current_focus = it;
                return;
            }
        }
    }
}

void window::tabHandle ()
{
    if (IsKeyDown(KEY_TAB)) {
        display_tab = true;
        return;
    }
    display_tab = false;
}

void window::eventHandler ()
{
    moveCameraWithMouse();
    moveCamera();
    mouseClick();
    tabHandle();
}

void window::drawResource(Tile& tile, Vector3 *offset, int (Resource::*getter)(), const Color& color)
{
    int qty = 0;
    float res_size = 0.4;
    static Model model = LoadModel("asset/stones/model.obj");
    static Texture2D texture = LoadTexture("asset/stones/blue.png");
    static Material material = LoadMaterialDefault();
    material.maps[MATERIAL_MAP_DIFFUSE].texture = texture;
    model.materials[0] = material;

    if ((qty = (tile.getResource()->*getter)()) > 0) {
        Vector3 pos = getCubePos(tile.getPos()->getX(), tile.getPos()->getY());
        pos.y += 1.2;
        if ((int)offset->y % 2 == 0) {
            pos.x += offset->x;
            pos.z += offset->z;
        } else {
            pos.x -= offset->x;
            pos.z -= offset->z;
        }
        DrawModel(model, pos, res_size, color);
        offset->x = res_size;
        offset->z = res_size;
        offset->y++;
    }
}

void window::drawResources()
{
    std::vector<Tile> *tile_list = _content->getMapTile();
    int qty = 0;
    float res_size = 0.1;
    for (auto it : *tile_list) {
        Vector3 offset = {0, 0, 0};
        drawResource(it, &offset, &Resource::getFood, GREEN);
        drawResource(it, &offset, &Resource::getLinemate, DARKGRAY);
        drawResource(it, &offset, &Resource::getDeraumere, RED);
        drawResource(it, &offset, &Resource::getSibur, YELLOW);
        drawResource(it, &offset, &Resource::getMendiane, BLUE);
        drawResource(it, &offset, &Resource::getPhiras, PURPLE);
        drawResource(it, &offset, &Resource::getThystame, ORANGE);
    }
}

void window::drawInfo ()
{
    DrawRectangle(10, 10, 300, 500, GRAY);

    std::string food = "Food : " + std::to_string(tile_current->getResource()->getFood());
    std::string linemate = "Linemate : " + std::to_string(tile_current->getResource()->getLinemate());
    std::string deraumere = "Deraumere : " + std::to_string(tile_current->getResource()->getDeraumere());
    std::string sibur = "Sibur : " + std::to_string(tile_current->getResource()->getSibur());
    std::string mendiane = "Mendiane : " + std::to_string(tile_current->getResource()->getMendiane());
    std::string phiras = "Phiras : " + std::to_string(tile_current->getResource()->getPhiras());
    std::string thystame = "Thystame : " + std::to_string(tile_current->getResource()->getThystame());
    std::string player_n = "Nombre de joueur : " + std::to_string(_content->getNPlayerByTile(tile_current));

    DrawText(food.c_str(), 15, 15, 20, BLACK);
    DrawText(linemate.c_str(), 15, 40, 20, BLACK);
    DrawText(deraumere.c_str(), 15, 65, 20, BLACK);
    DrawText(sibur.c_str(), 15, 90, 20, BLACK);
    DrawText(mendiane.c_str(), 15, 115, 20, BLACK);
    DrawText(phiras.c_str(), 15, 140, 20, BLACK);
    DrawText(thystame.c_str(), 15, 165, 20, BLACK);

    DrawText(player_n.c_str(), 15, 190, 20, BLACK);
    int i = 0;

    for (auto team : _content->getTeamList()) {
        int size = 0;
        for (auto it : _content->getPlayerList()) {
            std::map<std::string, int> tmpPlayer = it.getPos()->getPosition();
            std::map<std::string, int> tmpTile = tile_current->getPos()->getPosition();
            if (tmpTile["x"] == tmpPlayer["x"] && tmpTile["y"] == tmpPlayer["y"]) {
                if (it.getTeam().getName() == team.getName()) {
                    size++;
                }
            }
        }
        DrawRectangle(13, 115 + (30 * i), 294, (25 * size), team.getColor());
        if (size)
            i++;
    }
}

bool window::checkMouseClickInsideButton(int buttonX, int buttonY, int buttonWidth, int buttonHeight)
{
    int mouseX = GetMouseX();
    int mouseY = GetMouseY();

    if (mouseX >= buttonX && mouseX <= buttonX + buttonWidth &&
        mouseY >= buttonY && mouseY <= buttonY + buttonHeight) {
        return true;
    }

    return false;
}


void window::drawTab ()
{
    int x = GetMonitorWidth(0);
    int y = GetMonitorHeight(0);
    _content->sortScoreBoard();
    int width = (x / 100) * 80;
    int height = (y / 100) * 80;
    int margin_left = (x / 100) * 10;
    int margin_top = (y / 100) * 5;
    int Ptop = (margin_top + (height / 100) * 5);
    int PHeight = (height / 100) * 5;
    int last = 0;

    DrawRectangle(margin_left, margin_top, width, height, Color{ 0, 0, 0, 125 });

    for (auto it : _content->getScoreboardSorted()) {
        DrawRectangle(margin_left + ((width / 100) * 2), Ptop + last, (width / 100) * 96, PHeight * it.players.size(), Color { it.team.getColor().r, it.team.getColor().g, it.team.getColor().b, it.team.getColor().a});
        int nb = 0;
        for (auto it2 : it.players) {
            std::string info = "ID : " + std::to_string(it2->getId());
            info += " | Team : " + it.team.getName();
            info += " | Level : " + std::to_string(it2->getLevel());
            DrawText(info.c_str(), margin_left + ((width / 100) * 3), (Ptop + last) + (nb * 35) + 5, 20, BLACK);
            nb++;
        }
        last += (PHeight * it.players.size()) + (Ptop / 3);
    }
}

void window::drawCubeBasedOnPosition(const Vector3& position, const Vector3& focus, const Vector3& handle)
{
    if (position == focus) {
        DrawCube(position, cube_size, cube_size, cube_size, RED);
    } else if (position == handle) {
        DrawCube(position, cube_size, cube_size, cube_size, Color{ 0, 0, 0, 255 });
    } else {
        DrawCube(position, cube_size, cube_size, cube_size, Color {30, 149, 35, 240});
    }
}

void window::drawCubes()
{
    for (auto its : cubePosition) {
        if (collisionBlock.hit) {
            drawCubeBasedOnPosition(its, current_focus, current_handle);
        } else {
            if (its == current_handle)
                DrawCube(its, cube_size, cube_size, cube_size, Color{ 0, 0, 0, 255 });
            else
                DrawCube(its, cube_size, cube_size, cube_size, Color {30, 149, 35, 240});
        }
    }
}

void window::drawPlayer()
{
    // voir pour trouver un meilleur model / different model pour chaque team
    static Model model = LoadModel("asset/player.obj");
    // static Texture2D texture = LoadTexture("asset/player/player.png");
    static Material material = LoadMaterialDefault();
    // material.maps[MATERIAL_MAP_DIFFUSE].texture = texture;
    model.materials[0] = material;

    for (auto its : _playerPosition) {
        DrawModel(model, its, 0.3, GRAY);
        DrawCube(its, cube_size / 5, cube_size / 4, cube_size / 5, RED); // old player position
    }
}

void window::display()
{
    BeginDrawing();
    ClearBackground(SKYBLUE);
    BeginMode3D(camera);

    drawCubes();
    drawPlayer();
    drawResources();

    EndMode3D();

    if (display_info)
        drawInfo();
    if (display_tab)
        drawTab();
    EndDrawing();
}
