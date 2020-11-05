#pragma once

#include <iostream>

struct Node
{
	int32_t data;
	Node *next;
};

class List
{
	Node *begin;
	Node *end;
	size_t size;
public:
	List();
	List(int n);
	List(const List &other);
	List(List &&other);
	void push_back(int32_t n);
	void pop_back();
	void printer() const;
	int32_t operator[](size_t i) const;
	int32_t &operator[](size_t i);
	void clear();
	List &operator=(const List &other);
	List &operator=(List &&other);
	size_t get_size() const;
	~List();
};