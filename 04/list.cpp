#include <iostream>
#include "list.h"

List::List()
{
	size = 0;
	begin = nullptr;
	end = nullptr;
}

List::List(int32_t number)
{
	begin = new Node;
	begin->data = number;
	begin->next = nullptr;
	size = 1;
	end = begin;
}

List::List(const List &other)
{
	Node *tmp = other.begin;
	if (!tmp) {
		size = 0;
		begin = nullptr;
		end = nullptr;
	} else {
		while (tmp) {
			this->push_back(tmp->data);
			tmp = tmp->next;
		}
	}
}

List::List(List &&other)
{
	size = std::move(other.size);
	begin = other.begin;
	end = other.end;
	other.size = 0;
	other.begin = nullptr;
	other.end = nullptr;
}

void List::push_back(int32_t number)
{
	if (begin) {
		end->next = new Node;
		end = end-> next;
		end->data = number;
		end->next = nullptr;
		size++;
	} else {
		begin = new Node;
		begin->data = number;
		begin->next = nullptr;
		end = begin;
		size = 1;
	}
}

void List::pop_back()
{
	Node *tmp = begin;
	if (!tmp) {
		return;
	}
	if (tmp == end) {
		delete tmp;
		size = 0;
		begin = nullptr;
		end = nullptr;
		return;
	}
	while (tmp->next != end) {
		tmp = tmp->next;
	}
	end = tmp;
	tmp = tmp->next;
	delete tmp;
	end->next = nullptr;
	size--;
	return;
}

int32_t List::operator[](size_t i) const
{
	if (i >= size){
		return static_cast<int32_t>(0);
	}
	Node *tmp = begin;
	for (size_t j = 0; j < i; ++j) {
		tmp = tmp->next;
	}
	return tmp->data;
}

int32_t &List::operator[](size_t i)
{
	if (i >= size){
		throw "Index out of range";
	}
	Node *tmp = begin;
	for (size_t j = 0; j < i; ++j) {
		tmp = tmp->next;
	}
	return tmp->data;
}

void List::clear()
{
	Node *tmp;
	while (begin) {
		tmp = begin;
		begin = begin->next;
		delete tmp;
	}
	begin = nullptr;
	end = nullptr;
	size = 0;
}

List &List::operator=(const List &other)
{
	if (this == &other) {
		return *this;
	}
	this->clear();
	Node *tmp = other.begin;
	while (tmp) {
		this->push_back(tmp->data);
		tmp = tmp->next;
	}
	return *this;
}

List &List::operator=(List &&other){
	if (this == &other) {
		return *this;
	}
	this->clear();
	size = std::move(other.size);
	begin = other.begin;
	end = other.end;
	other.size = 0;
	other.begin = nullptr;
	other.end = nullptr;
	return *this;
}

size_t List::get_size() const
{
	return size;
}

void List::printer() const
{
	Node *tmp = begin;
	while (tmp) {
		std::cout << tmp->data << std::endl;
		tmp = tmp->next;
	}
}

List::~List()
{
	Node *tmp;
	while (begin) {
		tmp = begin;
		begin = begin->next;
		delete tmp;
	}
}