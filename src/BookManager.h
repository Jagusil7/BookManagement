#pragma once
class BookManager
{
public :
	BookManager();
	~BookManager();

public :
	void InsertBook(string name,string writer,string number);
	Book* FindBook(string name);
private:
	Book* head = nullptr;
};

