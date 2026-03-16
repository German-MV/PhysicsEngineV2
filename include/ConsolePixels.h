#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <windows.h>
#include <cstdint>

class DrawableScreen {
private:
    std::vector<std::vector<uint8_t>> pixels; // <- mejor que vector<bool>
    // Unicode blocks
    static constexpr wchar_t FULL  = L'\u2588'; // █
    static constexpr wchar_t UPPER = L'\u2580'; // ▀
    static constexpr wchar_t LOWER = L'\u2584'; // ▄
    static constexpr wchar_t SPACE = L' ';

    // Frame anterior colapsado a “caracteres consola” (alto = height/2 redondeando hacia arriba)
    std::vector<std::wstring> prevFrame;

public:
    DrawableScreen(size_t width, size_t height)
        : pixels(height, std::vector<uint8_t>(width, 0)),
          prevFrame((height + 1) / 2, std::wstring(width, SPACE)) {}

    inline size_t getWidth()  const noexcept { return pixels.empty() ? 0 : pixels[0].size(); }
    inline size_t getHeight() const noexcept { return pixels.size(); }

    inline void drawPixel(int x, int y) { setPixel(x, y, true); }
    inline void clearPixel(int x, int y) { setPixel(x, y, false); }

    void setPixel(int x, int y, bool state = true) {
        if (x >= 0 && y >= 0 && (size_t)x < getWidth() && (size_t)y < getHeight()) {
            pixels[(size_t)y][(size_t)x] = state ? 1 : 0;
        }
    }

    bool getPixel(int x, int y) const {
        if (x >= 0 && y >= 0 && (size_t)x < getWidth() && (size_t)y < getHeight()) {
            return pixels[(size_t)y][(size_t)x] != 0;
        }
        return false;
    }

    // Dibuja sin limpiar
    void render() { renderImpl(/*clearDrawn*/false); }

    // Dibuja y limpia lo que se dibujó
    void renderAndClear() { renderImpl(/*clearDrawn*/true); }

    void clear() {
        for (auto& row : pixels) std::fill(row.begin(), row.end(), 0);
    }

private:
    void renderImpl(bool clearDrawn) {
        const size_t W = getWidth();
        const size_t H = getHeight();
        if (W == 0 || H == 0) return;

        // Construye el frame actual “colapsado” (alto visual = ceil(H/2))
        const size_t visualH = (H + 1) / 2;
        std::vector<std::wstring> currFrame(visualH, std::wstring(W, SPACE));

        for (size_t y = 0; y < H; y += 2) {
            const size_t y2 = y + 1;
            for (size_t x = 0; x < W; ++x) {
                const bool upper = pixels[y][x] != 0;
                const bool lower = (y2 < H) ? (pixels[y2][x] != 0) : false;

                wchar_t c = SPACE;
                if (upper && lower) c = FULL;
                else if (upper)     c = UPPER;
                else if (lower)     c = LOWER;

                currFrame[y/2][x] = c;

                if (clearDrawn && c != SPACE) {
                    pixels[y][x] = 0;
                    if (y2 < H) pixels[y2][x] = 0; // guarda rango
                }
            }
        }

        // Salida eficiente: solo escribe líneas que cambiaron
        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

        for (size_t vy = 0; vy < visualH; ++vy) {
            if (currFrame[vy] == prevFrame[vy]) continue;

            // Posiciona y escribe la línea completa
            COORD pos{ 0, static_cast<SHORT>(vy) };
            SetConsoleCursorPosition(hOut, pos);

            // Escribimos como wide chars
            DWORD written = 0;
            WriteConsoleW(hOut, currFrame[vy].c_str(),
                          static_cast<DWORD>(currFrame[vy].size()),
                          &written, nullptr);

            prevFrame[vy] = std::move(currFrame[vy]);
        }

        // Coloca el cursor al final del área
        gotoxy(0, static_cast<int>(visualH));
    }

    static void gotoxy(int x, int y) {
        HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
        COORD dwPos{ static_cast<SHORT>(x), static_cast<SHORT>(y) };
        SetConsoleCursorPosition(hcon, dwPos);
    }
};

void writeTextAt(const std::string& text, int x, int y) {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos{ static_cast<SHORT>(x), static_cast<SHORT>(y) };
    SetConsoleCursorPosition(hOut, pos);
    DWORD written = 0;
    WriteConsoleA(hOut, text.c_str(), static_cast<DWORD>(text.size()), &written, nullptr);
}