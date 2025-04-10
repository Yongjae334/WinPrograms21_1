// ��������!! (������)
#include <windows.h>     // Windows API ����� ���� ���
#include <stdio.h>       // ǥ�� ����� �Լ� ���

// Ŀ���� (x, y) ��ġ�� �̵���Ű�� �Լ� ����
void gotoxy(int x, int y) {
    COORD pos = { x, y };  // �̵��� ��ǥ�� ����ü�� ����
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos); // �ܼ� Ŀ�� �̵�
}

int main() {
    char letter = 'A';             // ����� ���ĺ� ����
    COORD letterPos = { 10, 5 };   // 'A'�� �ʱ� ��ġ (x=10, y=5)
    int dragging = 0;              // �巡�� ������ ���θ� ���� (0: �ƴ�, 1: �巡�� ��)

    // �ܼ� �Է��� �ٷ�� ���� �ڵ� ��������
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);

    DWORD prevMode;                // ���� �ܼ� �Է� ��带 ������ ����
    GetConsoleMode(hInput, &prevMode); // ���� �ܼ� ��� �б�

    // ���콺 �Է� Ȱ��ȭ �� Ȯ�� �÷��� ����
    SetConsoleMode(hInput, ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);

    // �ܼ� ȭ�� �ʱ�ȭ (��ü �����)
    system("cls");

    // �ʱ� ��ġ�� Ŀ���� �̵��ϰ� 'A' ���
    gotoxy(letterPos.X, letterPos.Y);
    printf("%c", letter);

    DWORD events;                  // �̺�Ʈ ���� ����� ����
    INPUT_RECORD input;            // �Է� �̺�Ʈ ����ü

    while (1) {                    // ���� ����
        // ESC Ű�� ���ȴٸ� ���� ����
        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
            break;
        }

        // �ܼ� �Է� �̺�Ʈ 1�� �б�
        ReadConsoleInput(hInput, &input, 1, &events);

        // �Է��� ���콺 �̺�Ʈ�� ��� ó��
        if (input.EventType == MOUSE_EVENT) {
            MOUSE_EVENT_RECORD mer = input.Event.MouseEvent; // ���콺 �̺�Ʈ ���� ����

            // ���콺 ���� ��ư�� ������ ��
            if (mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
                // Ŭ���� ��ǥ�� ���� 'A'�� ��ġ�� ���ٸ�
                if (mer.dwMousePosition.X == letterPos.X && mer.dwMousePosition.Y == letterPos.Y) {
                    dragging = 1; // �巡�� ����
                }
            }
            // ���콺 ��ư�� ������ �����̸鼭 �巡�� ���̾��ٸ�
            else if (mer.dwButtonState == 0 && dragging) {
                dragging = 0; // �巡�� ����

                letterPos = mer.dwMousePosition; // ���� ���콺 ��ġ�� 'A'�� �� ��ġ�� ����

                system("cls"); // �ܼ� ȭ�� �ٽ� �����

                // �ȳ� ���� ���
                gotoxy(0, 0);
                printf("���ĺ� '%c'�� ���콺�� Ŭ�� �� �巡���Ͽ� �̵��ϼ���. (ESC�� ����)\n", letter);

                // ���ο� ��ġ�� 'A' ���
                gotoxy(letterPos.X, letterPos.Y);
                printf("%c", letter);
            }
        }
    }

    // ���α׷� ���� �� �ܼ� �Է� ��带 ������� �ǵ���
    SetConsoleMode(hInput, prevMode);

    // ���� �޽��� ���
    printf("\n���α׷� ����\n");

    return 0; // ���α׷� ���� ����
}
