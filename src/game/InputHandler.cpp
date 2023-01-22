#include "game/InputHandler.hpp"

InputHandler::InputHandler() : keys() {}

void InputHandler::inputEvent(SDL_Event& ev) {
    switch (ev.type) {
        case SDL_KEYDOWN:
            keys.insert_or_assign(ev.key.keysym.sym, PRESSED);
            break;
        case SDL_KEYUP:
            keys.insert_or_assign(ev.key.keysym.sym, RELEASED);
            break;
        case SDL_MOUSEMOTION:
            this->mouseX = ev.motion.x;
            this->mouseY = ev.motion.y;
            break;
        case SDL_MOUSEBUTTONDOWN:
            this->click = PRESSED;
            break;
        case SDL_MOUSEBUTTONUP:
            this->click = RELEASED;
            break;
        default:
            break;
    }
}

void InputHandler::update() {
    for (auto& iter : keys) switch (iter.second) {
            case PRESSED:
                iter.second = DOWN;
                break;
            case RELEASED:
                iter.second = NONE;
                break;
            default:
                break;
        }
    switch (click) {
        case PRESSED:
            click = DOWN;
            break;
        case RELEASED:
            click = NONE;
            break;
        default:
            break;
    }
}

SDL_Point InputHandler::getMousePos() const {
    return SDL_Point{mouseX, mouseY};
}

KeyStatus InputHandler::getMouseState() const { return click; }

KeyStatus InputHandler::getStatus(SDL_Scancode key) const {
    if (keys.find(key) == keys.end()) return NONE;
    return keys.at(key);
}