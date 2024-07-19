#include "MessageManager.h"

MessageManager::MessageManager(int maxMessages, int displayTime)
    : maxMessages(maxMessages), displayTime(displayTime), currentTime(0) {}

void MessageManager::AddMessage(const std::string& message) {
    if (messages.size() >= maxMessages) {
        messages.erase(messages.begin());
    }
    messages.push_back(message);
    currentTime = 0; // Reset the timer whenever a new message is added
}

void MessageManager::RenderMessages() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD cursorPos;

    for (int i = 0; i < maxMessages; ++i) {
        if (i >= 0 && i < messages.size()) {
            std::cout << messages[i] << std::endl;
        }
        else {
            std::cout << std::endl;
        }
        
    }
}

void MessageManager::Update() {
    if (currentTime >= displayTime) {
        ClearMessages();
        currentTime = 0;
    }
    else {
        ++currentTime;
    }
}

void MessageManager::ClearMessages() {
    messages.clear();
}