#include "ScreenBuffer.h"

#include "ScreenBuffer.h"

ScreenBuffer::ScreenBuffer(int width, int height) : width(width), height(height), dynamicBuffer(width * height, ' '), staticBuffer(width * height, ' ') {}

void ScreenBuffer::Clear() {
    std::fill(dynamicBuffer.begin(), dynamicBuffer.end(), ' ');
}

void ScreenBuffer::Draw(int x, int y, char c) {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        dynamicBuffer[y * width + x] = c;
    }
}

void ScreenBuffer::ResetDynamicBuffer() {
    SetBuffer(staticBuffer);
}

void ScreenBuffer::DrawStaticBuffer(int x, int y, char c) {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        staticBuffer[y * width + x] = c;
    }
}

void ScreenBuffer::Render() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD cursorPos = { 0, 0 };
    SetConsoleCursorPosition(hConsole, cursorPos);

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            std::cout << dynamicBuffer[y * width + x];
        }
        std::cout << '\n';
    }
}

char ScreenBuffer::GetCharAt(int x, int y) const {
    return dynamicBuffer[y * width + x];
}

std::vector<char> ScreenBuffer::GetBuffer() const {
    return dynamicBuffer;
}

void ScreenBuffer::SetBuffer(const std::vector<char>& newBuffer) {
    dynamicBuffer = newBuffer;
}