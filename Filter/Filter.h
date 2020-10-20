#pragma once
#ifndef FILTER_H
#define FILTER_H
#define ABSOLUTE_DIFFERENCE(A,B) ((A-B)<0 ? (-(A-B)): (A-B))
#include <QList>
#include <QWidget>


template <class Type>
class Filter {
public:
    virtual void init()=0;
	Type filtered;
	void setVal(Type *_val) {filtered = _val;}
	Type getVal() {return filtered;}
	virtual void update(Type newVal) = 0;
	void reset() {filtered=0.0;}
    QList<Filter<Type>*> operator+(const Filter<Type> &b) {
        QList<Filter<Type>*> list;
		list.pushBack(this);
		list.pushBack(b);
		return list;
	}
    virtual QWidget* getWidget()=0;
	virtual Filter* clone() = 0;
};




#endif
