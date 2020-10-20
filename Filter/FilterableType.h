#pragma once
#ifndef FILTERABLE_TYPE_H
#define FILTERABLE_TYPE_H
#include "Arduino.h"

#include "C:/Users/kamil/Documents/Programming/HawkRC/handlers/Filter/Filter.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/handlers/Filter/FilterableValue.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/structures/List.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/structures/HPair.h"


template <class Type>
class FilterableType {
protected:
	List<HPair<Type*, List<Filter<Type>*>>> listOfValuesFilters;
	FilterableType(){}
	List<List<Filter<Type>*>> filters;
	/*~FilterableType(){
		for(typename List<HPair<Type*, List<Filter<Type>*>>>::Node *it = listOfValuesFilters.front; it!=nullptr; it=it->next) {
			for(typename List<Filter<Type>*>::Node *filtIt = it->val.second.front; filtIt!=nullptr; filtIt=filtIt->next) {
				delete filtIt->val;	
			}
		}
	}*/
    void addValueReference(Type& valueToAdd) {
		listOfValuesFilters.pushBack(HPair<Type*, List<Filter<Type>*>>(&valueToAdd, List<Filter<Type>*>()));
	}
	void _addFilters(Filter<Type>* fltr) {
		for(typename List<HPair<Type*, List<Filter<Type>*>>>::Node *it = listOfValuesFilters.top(); it!=nullptr; it=it->next) {
			//Filter<Type>* filterToAdd = ;
			it->val.second.pushBack(fltr->clone());
		}
		delete fltr;
	}
	void _addFilter(Type* ptrToVal, Filter<Type>* fltr) {
		for(typename List<HPair<Type*, List<Filter<Type>*>>>::Node *it = listOfValuesFilters.top(); it!=nullptr; it=it->next) {
			if(ptrToVal == it->val.first) {
				it->val.second.pushBack(fltr);
			}
		}
	}
	void _updateFilters(List<Type> updateValues) {
		//if(updateValues.count()!=values.count()) return;
		typename List<Type>::Node *newValsIt = updateValues.top();
		for(typename List<HPair<Type*, List<Filter<Type>*>>>::Node *it = listOfValuesFilters.top(); it!=nullptr; it=it->next) {
			Type passingVal = newValsIt->val;
			for(typename List<Filter<Type>*>::Node *filterIt = it->val.second.top(); filterIt!=nullptr; filterIt=filterIt->next) {
				filterIt->val->update(passingVal);
				passingVal = filterIt->val->filtered;
			}
			*it->val.first = passingVal;
			newValsIt = newValsIt->next;
		}

		/*typename List<Type>::Node *newValsIt = updateValues.top();
        for(typename List<Type*>::Node *valuesIt = values.top(); valuesIt!=nullptr; valuesIt=valuesIt->next) {
            Type passingVal = newValsIt->val;
            for(typename List<Filter<Type>*>::Node *filterIt = filters.top(); filterIt!=nullptr; filterIt=filterIt->next) {
                filterIt->val->update(passingVal);
                passingVal = filterIt->val->filtered;
            }
			newValsIt=newValsIt->next;
            *valuesIt->val = passingVal;
        }*/
	}
	/*void reset() {
		typename List<Filter<Type>*>::Node *current = filters.front;
		if(current!=nullptr) {
			filters.front->val->reset();
			current = current->next;
		}
	}*/
	void addFilter(Filter<Type>* filter) {
		filters.pushBack(filter);
	}
	void addFilter(List<Filter<Type>*> filter) {
		filters.Union(filter);
	}
};

#endif