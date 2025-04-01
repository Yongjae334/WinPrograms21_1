#include <stdio.h>
#include <Windows.h>

void gotoxy(int x, int y)
{
	COORD cur;
	cur.X = x;
	cur.Y = y;
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(output, cur); 
}

int main()
{

	puts("\n\n\n\n");
	puts("---------------------------------------------------------------------------------- \n");
	puts("|                                                                                | \n");
	puts("---------------------------------------------------------------------------------- \n");
	puts("|                                                                                | \n");
	puts("|                                                                                | \n");
	puts("|                                                                                | \n");
	puts("|                                                                                | \n");
	puts("---------------------------------------------------------------------------------- \n");

	return 0;
}

int show() {
	int width, height;

	while (1) {
		puts("  ���� ����� �Է��Ͻÿ�.");
		scanf_s("%d, &width");
		printf(" ���� ����� �Է��Ͻÿ�.");
		scanf_s("%d", &height);

		system("cls");

		if (width >= 2 && height >= 2) break;
		printf("���ο� ���δ� �ּ� 2 �̻��̾�� �մϴ�. �ٽ� �Է��ϼ���.\n\n"); //2 �̸����� ���� ��� ������ �Ұ����ϴϱ� �̷��� �����
	}

	int middle = 2; // �� ��° �ٿ����� ������ *�� ������ �ϱ� ���� �Է� ��

	// ��� �׵θ� ���
	gotoxy(0, 0); // �� ���� ���� ����� �Ǿ�� �մϴ�.
	for (int i = 0; i < width; i++) printf("*"); //ù �� �׵θ� �Է�

	// �߰� �� ���
	for (int i = 1; i < height - 1; i++) {
		gotoxy(0, i); //�߰����ʹϱ� 0, i��

		// �߰� ��ġ�� '*' �׵θ� ���
		if (i == middle) {
			for (int j = 0; j < width; j++) printf("*");
		}
		else {
			printf("[");
			for (int j = 1; j < width - 1; j++) printf(" ");
			printf("]");
		}
	}

	// �ϴ� �׵θ� ���
	gotoxy(0, height - 1); // ������ �ٿ��� * �����
	for (int i = 0; i < width; i++) printf("*");

	gotoxy(0, height + 1); // Ŀ�� �ڽ��� �Ʒ��� ������
	return 0;
}
