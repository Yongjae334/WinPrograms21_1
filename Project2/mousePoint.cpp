#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    char letter = 'A';         // 출력할 알파벳 'A'
    POINT mousePos;            // 마우스 좌표(스크린 기준)
    int isDragging = 0;        // 드래그 상태 (0: 드래그 중 아님, 1: 드래그 중)
    int letterX = 10;          // 초기 'A'의 X 좌표 (열)
    int letterY = 5;           // 초기 'A'의 Y 좌표 (행)

    HWND consoleWindow = GetConsoleWindow();
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // 기본 콘솔 셀 크기 (환경에 따라 달라질 수 있음)
    int cellWidth = 8;
    int cellHeight = 16;

    // 콘솔 글꼴 크기를 자동으로 가져와 셀 크기를 보정 (실패하면 기본값 유지)
    CONSOLE_FONT_INFOEX fontInfoEx = { 0 };
    fontInfoEx.cbSize = sizeof(CONSOLE_FONT_INFOEX);
    if (GetCurrentConsoleFontEx(hConsole, FALSE, &fontInfoEx)) {
        cellWidth = fontInfoEx.dwFontSize.X;
        cellHeight = fontInfoEx.dwFontSize.Y;
    }

    // 커서 숨기기 (깜빡임 방지)
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hConsole, &cursorInfo);

    // 최초 화면 클리어
    system("cls");

    while (1) {
        // 화면 갱신: 기존 콘솔 전체를 지우고, 안내 문구를 출력
        system("cls");
        printf("마우스로 'A'를 클릭 후 드래그하면 이동됩니다. (ESC: 종료)\n");
        printf("'A'의 현재 위치: (%d, %d)\n", letterX, letterY);

        // 현재 마우스 위치(스크린 좌표)를 구하고, 콘솔 클라이언트 좌표로 변환
        GetCursorPos(&mousePos);
        ScreenToClient(consoleWindow, &mousePos);

        // 콘솔 셀 좌표로 변환
        int mouseX = mousePos.x / cellWidth;
        int mouseY = mousePos.y / cellHeight;

        // 마우스 왼쪽 버튼 눌림 여부 확인
        if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
            // 드래그 시작 조건: 마우스 클릭 위치가 'A'의 위치 근처(여유 1셀 내)에 있을 때
            if (!isDragging && (abs(mouseX - letterX) <= 1 && abs(mouseY - letterY) <= 0)) {
                isDragging = 1;
            }
            // 드래그 중이면 'A'의 좌표를 마우스 셀 좌표로 업데이트
            if (isDragging) {
                letterX = mouseX;
                letterY = mouseY;
            }
        }
        else {
            // 마우스 버튼을 놓으면 드래그 종료
            isDragging = 0;
        }

        // 'A' 출력 (MSVC에서 구조체 리터럴 초기화 에러가 없도록 별도 처리)
        COORD pos;
        pos.X = (SHORT)letterX;
        pos.Y = (SHORT)letterY;
        SetConsoleCursorPosition(hConsole, pos);
        printf("%c", letter);

        // 종료 조건: ESC 키 입력 시 종료
        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
            break;
        }

        Sleep(10); // CPU 사용량 최소화를 위한 잠시 대기
    }

    // 종료 전 커서 다시 보이도록 설정
    cursorInfo.bVisible = TRUE;
    SetConsoleCursorInfo(hConsole, &cursorInfo);

    return 0;
}
