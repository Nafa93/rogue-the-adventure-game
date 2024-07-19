#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <Windows.h>

class MessageManager {
public:
    MessageManager(int maxMessages = 5, int displayTime = 100);

    void AddMessage(const std::string& message);
    void RenderMessages();
    void Update();

private:
    std::vector<std::string> messages;
    int maxMessages;
    int displayTime; // Time in game cycles to display each message
    int currentTime;

    void ClearMessages();
};
