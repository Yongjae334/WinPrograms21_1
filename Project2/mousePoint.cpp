#include <windows.h>
#include <stdio.h>

int main() {
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);

    // ���콺 �̺�Ʈ �޵��� ����
    SetConsoleMode(hInput, ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT);

    // Ŀ�� �����
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hOutput, &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hOutput, &cursorInfo);

    int letterX = 10, letterY = 5;
    int dragging = 0;
    DWORD numRead;
    INPUT_RECORD input;

    // A ���
    COORD pos = { (SHORT)letterX, (SHORT)letterY };
    SetConsoleCursorPosition(hOutput, pos);
    printf("A");

    printf("\n\n'A'�� ���콺�� Ŭ�� �� �巡���ؼ� �̵��ϼ���. (ESC�� ����)");

    while (1) {
        ReadConsoleInput(hInput, &input, 1, &numRead);

        if (input.EventType == KEY_EVENT &&
            input.Event.KeyEvent.bKeyDown &&
            input.Event.KeyEvent.wVirtualKeyCode == VK_ESCAPE) {
            break;
        }

        if (input.EventType == MOUSE_EVENT) {
            MOUSE_EVENT_RECORD mer = input.Event.MouseEvent;
            COORD mPos = mer.dwMousePosition;

            // ���콺 ���� ��ư Ŭ��
            if (mer.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED) {
                // �巡�� ���� ����: A�� ��ġ���� Ŭ�� ����
                if (!dragging &&
                    mPos.X == letterX && mPos.Y == letterY) {
                    dragging = 1;
                }

                // �巡�� ���� �� ���콺�� ���������� A�� �̵�
                if (dragging &&
                    (mPos.X != letterX || mPos.Y != letterY)) {

                    // A �����
                    COORD oldPos = { (SHORT)letterX, (SHORT)letterY };
                    SetConsoleCursorPosition(hOutput, oldPos);
                    printf(" ");

                    // �� ��ġ ����
                    letterX = mPos.X;
                    letterY = mPos.Y;

                    // A ���
                    COORD newPos = { (SHORT)letterX, (SHORT)letterY };
                    SetConsoleCursorPosition(hOutput, newPos);
                    printf("A");
                }
            }
            else {
                dragging = 0;
            }
        }
    }

    // Ŀ�� ����
    cursorInfo.bVisible = TRUE;
    SetConsoleCursorInfo(hOutput, &cursorInfo);

    return 0;
}
