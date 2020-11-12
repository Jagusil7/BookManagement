#include "stdafx.h"
#include "BookManager.h"

BookManager::BookManager()
{
}

BookManager::~BookManager()
{
}

void BookManager::InsertBook(string name, string writer, string number)
{
	Book* insertBook =  new Book(name,writer,number);
	Book* tempBook = head;
	// ���� head�� ��������� �� å�� ù å�̴�.
	if (head == nullptr)
	{
		head = insertBook;
	}
	// �ƴҰ�쿡
	else
	{
		// å�� �ǳ����� ���ϴ�.
		while (tempBook->next != nullptr)
		{
			tempBook = tempBook->next;
		}
		// �ǳ��� ���ο� å�� �߰��մϴ�.
		tempBook->next = insertBook;
	}

}
//���ϴ� å�� ã���ϴ�.
Book* BookManager::FindBook(string name)
{
	Book* tempBook = head;
	// �̸��� ������ ��ȯ�մϴ�.
	if (tempBook->getTitle() == name)
	{
		cout << "å�� ã�ҽ��ϴ�" << endl;
		return tempBook;
	}
	else
	{
		// å ��� ��ü�� Ȯ���մϴ�.
		while (tempBook->next != nullptr)
		{
			tempBook = tempBook->next;
			if (tempBook->getTitle() == name)
			{
				cout << "å�� ã�ҽ��ϴ�" << endl;
				return tempBook;
			}
		}
		
	}
	//å�� ã�����ϸ� nullptr�� ��ȯ�մϴ�.
	cout << "å�� ã�����߽��ϴ�" << endl;
	return nullptr;
}
