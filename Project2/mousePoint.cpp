// 연습문제!! (과제물)
#include <windows.h>     // Windows API 사용을 위한 헤더
#include <stdio.h>       // 표준 입출력 함수 사용

// 커서를 (x, y) 위치로 이동시키는 함수 정의
void gotoxy(int x, int y) {
    COORD pos = { x, y };  // 이동할 좌표를 구조체로 지정
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos); // 콘솔 커서 이동
}

int main() {
    char letter = 'A';             // 출력할 알파벳 문자
    COORD letterPos = { 10, 5 };   // 'A'의 초기 위치 (x=10, y=5)
    int dragging = 0;              // 드래그 중인지 여부를 저장 (0: 아님, 1: 드래그 중)

    // 콘솔 입력을 다루기 위한 핸들 가져오기
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);

    DWORD prevMode;                // 기존 콘솔 입력 모드를 저장할 변수
    GetConsoleMode(hInput, &prevMode); // 현재 콘솔 모드 읽기

    // 마우스 입력 활성화 및 확장 플래그 설정
    SetConsoleMode(hInput, ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);

    // 콘솔 화면 초기화 (전체 지우기)
    system("cls");

    // 초기 위치에 커서를 이동하고 'A' 출력
    gotoxy(letterPos.X, letterPos.Y);
    printf("%c", letter);

    DWORD events;                  // 이벤트 개수 저장용 변수
    INPUT_RECORD input;            // 입력 이벤트 구조체

    while (1) {                    // 무한 루프
        // ESC 키가 눌렸다면 루프 종료
        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
            break;
        }

        // 콘솔 입력 이벤트 1개 읽기
        ReadConsoleInput(hInput, &input, 1, &events);

        // 입력이 마우스 이벤트일 경우 처리
        if (input.EventType == MOUSE_EVENT) {
            MOUSE_EVENT_RECORD mer = input.Event.MouseEvent; // 마우스 이벤트 정보 저장

            // 마우스 왼쪽 버튼이 눌렸을 때
            if (mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
                // 클릭한 좌표가 현재 'A'의 위치와 같다면
                if (mer.dwMousePosition.X == letterPos.X && mer.dwMousePosition.Y == letterPos.Y) {
                    dragging = 1; // 드래그 시작
                }
            }
            // 마우스 버튼이 떼어진 상태이면서 드래그 중이었다면
            else if (mer.dwButtonState == 0 && dragging) {
                dragging = 0; // 드래그 종료

                letterPos = mer.dwMousePosition; // 현재 마우스 위치를 'A'의 새 위치로 저장

                system("cls"); // 콘솔 화면 다시 지우고

                // 안내 문구 출력
                gotoxy(0, 0);
                printf("알파벳 '%c'을 마우스로 클릭 후 드래그하여 이동하세요. (ESC로 종료)\n", letter);

                // 새로운 위치에 'A' 출력
                gotoxy(letterPos.X, letterPos.Y);
                printf("%c", letter);
            }
        }
    }

    // 프로그램 종료 전 콘솔 입력 모드를 원래대로 되돌림
    SetConsoleMode(hInput, prevMode);

    // 종료 메시지 출력
    printf("\n프로그램 종료\n");

    return 0; // 프로그램 정상 종료
}
