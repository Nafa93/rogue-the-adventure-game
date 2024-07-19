#pragma once
#include <vector>
#include <iostream>
#include <Windows.h>

class ScreenBuffer {
public:
    ScreenBuffer(int width, int height);
    void Clear();
    void Draw(int x, int y, char c);
    void ResetDynamicBuffer();
    void DrawStaticBuffer(int x, int y, char c);
    void Render();
    char GetCharAt(int x, int y) const;
    std::vector<char> GetBuffer() const;
    void SetBuffer(const std::vector<char>& newBuffer);

private:
    int width, height;
    std::vector<char> dynamicBuffer;
    std::vector<char> staticBuffer;
};