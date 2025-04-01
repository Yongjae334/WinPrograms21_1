#include <stdio.h>
#include <windows.h>

// Ŀ�� ��ġ ���� �Լ��� �Է¹���
void gotoxy(int x, int y) {
    COORD Cur;
    Cur.X = x;
    Cur.Y = y;
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(output, Cur);
}

int main() {
    int width, height; //���ο� ������ �Է°��� �޾ƹ���

    // ��ȿ�� �Է� ���� ������ �ݺ�
    while (1) {
        printf("���ϴ� ���� ����� �Է��ϼ��� : "); // ù ��° �Է� �޴°� ���� ������
        scanf_s("%d", &width);
        printf("���ϴ� ���� ����� �Է��ϼ��� : "); // �� ��° �Է� �޴°� ���� ������
        scanf_s("%d", &height);

        system("cls"); // �Է� �޾����ϱ� ���� �����ִ°� �����

        if (width >= 2 && height >= 2) break;
        printf("���ο� ���δ� �ּ� 2 �̻��̾�� �մϴ�. �ٽ� �Է��ϼ���.\n\n"); //2 �̸����� ���� ��� ������ �Ұ����ϴϱ� �̷��� �����
    }

    int middle = 2; // �� ��° �ٿ����� ������ *�� ������ �ϱ� ���� �Է� ��

    // ��� �׵θ� ���
    gotoxy(0, 0); // �� ���� ���� ����� �Ǿ�� �մϴ�.
    for (int i = 0; i < width; i++) printf("-"); //ù �� �׵θ� �Է�

    // �߰� �� ���
    for (int i = 1; i < height - 1; i++) {
        gotoxy(0, i); //�߰����ʹϱ� 0, i��

        // �߰� ��ġ�� '*' �׵θ� ���
        if (i == middle) {
            for (int j = 0; j < width; j++) printf("-");
        }
        else {
            printf("|");
            for (int j = 1; j < width - 1; j++) printf(" ");
            printf("|");
        }
    }

    // �ϴ� �׵θ� ���
    gotoxy(0, height - 1); // ������ �ٿ��� * �����
    for (int i = 0; i < width; i++) printf("-");

    gotoxy(0, height + 1); // Ŀ�� �ڽ��� �Ʒ��� ������
    return 0;
}