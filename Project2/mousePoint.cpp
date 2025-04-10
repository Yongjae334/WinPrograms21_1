#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    char letter = 'A';         // ����� ���ĺ� 'A'
    POINT mousePos;            // ���콺 ��ǥ(��ũ�� ����)
    int isDragging = 0;        // �巡�� ���� (0: �巡�� �� �ƴ�, 1: �巡�� ��)
    int letterX = 10;          // �ʱ� 'A'�� X ��ǥ (��)
    int letterY = 5;           // �ʱ� 'A'�� Y ��ǥ (��)

    HWND consoleWindow = GetConsoleWindow();
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // �⺻ �ܼ� �� ũ�� (ȯ�濡 ���� �޶��� �� ����)
    int cellWidth = 8;
    int cellHeight = 16;

    // �ܼ� �۲� ũ�⸦ �ڵ����� ������ �� ũ�⸦ ���� (�����ϸ� �⺻�� ����)
    CONSOLE_FONT_INFOEX fontInfoEx = { 0 };
    fontInfoEx.cbSize = sizeof(CONSOLE_FONT_INFOEX);
    if (GetCurrentConsoleFontEx(hConsole, FALSE, &fontInfoEx)) {
        cellWidth = fontInfoEx.dwFontSize.X;
        cellHeight = fontInfoEx.dwFontSize.Y;
    }

    // Ŀ�� ����� (������ ����)
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hConsole, &cursorInfo);

    // ���� ȭ�� Ŭ����
    system("cls");

    while (1) {
        // ȭ�� ����: ���� �ܼ� ��ü�� �����, �ȳ� ������ ���
        system("cls");
        printf("���콺�� 'A'�� Ŭ�� �� �巡���ϸ� �̵��˴ϴ�. (ESC: ����)\n");
        printf("'A'�� ���� ��ġ: (%d, %d)\n", letterX, letterY);

        // ���� ���콺 ��ġ(��ũ�� ��ǥ)�� ���ϰ�, �ܼ� Ŭ���̾�Ʈ ��ǥ�� ��ȯ
        GetCursorPos(&mousePos);
        ScreenToClient(consoleWindow, &mousePos);

        // �ܼ� �� ��ǥ�� ��ȯ
        int mouseX = mousePos.x / cellWidth;
        int mouseY = mousePos.y / cellHeight;

        // ���콺 ���� ��ư ���� ���� Ȯ��
        if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
            // �巡�� ���� ����: ���콺 Ŭ�� ��ġ�� 'A'�� ��ġ ��ó(���� 1�� ��)�� ���� ��
            if (!isDragging && (abs(mouseX - letterX) <= 1 && abs(mouseY - letterY) <= 0)) {
                isDragging = 1;
            }
            // �巡�� ���̸� 'A'�� ��ǥ�� ���콺 �� ��ǥ�� ������Ʈ
            if (isDragging) {
                letterX = mouseX;
                letterY = mouseY;
            }
        }
        else {
            // ���콺 ��ư�� ������ �巡�� ����
            isDragging = 0;
        }

        // 'A' ��� (MSVC���� ����ü ���ͷ� �ʱ�ȭ ������ ������ ���� ó��)
        COORD pos;
        pos.X = (SHORT)letterX;
        pos.Y = (SHORT)letterY;
        SetConsoleCursorPosition(hConsole, pos);
        printf("%c", letter);

        // ���� ����: ESC Ű �Է� �� ����
        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
            break;
        }

        Sleep(10); // CPU ��뷮 �ּ�ȭ�� ���� ��� ���
    }

    // ���� �� Ŀ�� �ٽ� ���̵��� ����
    cursorInfo.bVisible = TRUE;
    SetConsoleCursorInfo(hConsole, &cursorInfo);

    return 0;
}
