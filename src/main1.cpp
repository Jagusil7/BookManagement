#include "stdafx.h"

int main()
{
	int input = 0;
	BookManager bm;

	string bookname;
	string writer;
	string number;
	for (int i = 0; i < 10; i++)
	{
		bookname = "book" + to_string(i);
		writer = "Writer" + to_string(i);
		number = to_string(i);
		bm.InsertBook(bookname, writer, number);
	}
	while (true)
	{
		cout << "������ 1 �ݳ��� 2 ����� 0�� �Է��ϼ���" << endl;
		cin >> input;

		if (input == 0)
		{
			break;
		}
		else if (input == 1)
		{
			cout << "�뿩�� å �̸��� �Է��� �ּ��� : ";
			cin >> bookname;
			Book* temp = bm.FindBook(bookname);
			// ã�� å�� ������� ���¸� Ȯ���մϴ�.
			if (temp != nullptr)
			{
				// å�� �������� ������� �뿩�մϴ�.
				if (temp->getStatus() == 0)
				{
					cout << bookname << "å�� �뿩�մϴ�" << endl;
					temp->setStatus();
				}
				// �뿩���ϰ�� �Ұ��� �޼����� �ѱ�ϴ�.
				else
				{
					cout << bookname << "å�� �̹� �뿩���Դϴ�" << endl;
				}
			}
			// ã�� å�̾������ ����մϴ�.
			else
			{
				cout << "ã�� å�� �����ϴ�" << endl;
			}
		}
		else if (input == 2)
		{
			cout << "�ݳ��� å �̸��� �Է��� �ּ��� : ";
			cin >> bookname;
			Book* temp = bm.FindBook(bookname);
			// å�� ã���� �ݳ��������� Ȯ���մϴ�.
			if (temp != nullptr)
			{
				//�뿩���� �ƴϸ� �Ұ��� �޼����� ��ȯ�մϴ�.
				if (temp->getStatus() == 0)
				{
					cout << bookname << "å�� �뿩���� �ƴմϴ�" << endl;
				}
				//�뿩���ϰ�� �ݳ��մϴ�.
				else
				{
					cout << bookname << "å�� �ݳ��մϴ�" << endl;
					temp->setStatus();
				}
			}
			//ã��å�� ������� ����մϴ�.
			else
			{
				cout << "ã�� å�� �����ϴ�" << endl;
			}
		}
	}

	return 0;
}