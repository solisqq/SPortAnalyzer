#pragma once
#ifndef FILTERABLEVALUE_H
#define FILTERABLEVALUE_H

#include "C:/Users/kamil/Documents/Programming/HawkRC/handlers/Filter/Filter.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/structures/List.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/handlers/Output/AllowPrint.h"

template <class Type>
class FilterableValue: public AllowPrint {
public:
	Type value;
	FilterableValue(){}
	List<Filter<Type>*> filters;
	~FilterableValue(){
		for(typename List<Filter<Type>*>::Node *it = filters.front; it!=nullptr; it=it->next) 
			delete it->val;
		
	}
	void update(Type val) {
		if(filters.count()==0) {
			value = val;
			return;
		}
		typename List<Filter<Type>*>::Node *current = filters.front;
		if(current!=nullptr) {
			filters.front->val->update(val);
			current = current->next;
			while(current!=nullptr) {
				current->val->update(current->prev->val->filtered);
				current = current->next;
			}
			value = filters.back->val->filtered;
		}
	}
	void reset() {
		typename List<Filter<Type>*>::Node *current = filters.top();
		if(current!=nullptr) {
			current->val->reset();
			current = current->next;
		}
	}
	void addFilter(Filter<Type>* filter) {
		filters.pushBack(filter);
	}
	void addFilter(List<Filter<Type>*> filter) {
		filters.Union(filter);
	}
	String toString() {
		return String(value);
	}
};

#endif