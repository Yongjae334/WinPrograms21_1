#include <windows.h>
#include <stdio.h>

int main() {
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);

    // 마우스 이벤트 받도록 설정
    SetConsoleMode(hInput, ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT);

    // 커서 숨기기
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hOutput, &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hOutput, &cursorInfo);

    int letterX = 10, letterY = 5;
    int dragging = 0;
    DWORD numRead;
    INPUT_RECORD input;

    // A 출력
    COORD pos = { (SHORT)letterX, (SHORT)letterY };
    SetConsoleCursorPosition(hOutput, pos);
    printf("A");

    printf("\n\n'A'를 마우스로 클릭 후 드래그해서 이동하세요. (ESC로 종료)");

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

            // 마우스 왼쪽 버튼 클릭
            if (mer.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED) {
                // 드래그 시작 조건: A의 위치에서 클릭 시작
                if (!dragging &&
                    mPos.X == letterX && mPos.Y == letterY) {
                    dragging = 1;
                }

                // 드래그 중일 때 마우스가 움직였으면 A를 이동
                if (dragging &&
                    (mPos.X != letterX || mPos.Y != letterY)) {

                    // A 지우기
                    COORD oldPos = { (SHORT)letterX, (SHORT)letterY };
                    SetConsoleCursorPosition(hOutput, oldPos);
                    printf(" ");

                    // 새 위치 갱신
                    letterX = mPos.X;
                    letterY = mPos.Y;

                    // A 출력
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

    // 커서 복원
    cursorInfo.bVisible = TRUE;
    SetConsoleCursorInfo(hOutput, &cursorInfo);

    return 0;
}
