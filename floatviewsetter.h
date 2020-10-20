#ifndef FLOATVIEWSETTER_H
#define FLOATVIEWSETTER_H

#include <QWidget>

namespace Ui {
class FloatViewSetter;
}

class FloatViewSetter : public QWidget
{
    Q_OBJECT
    float* value=nullptr;
public:
    explicit FloatViewSetter(float* _value, const QString &name, QWidget *parent = nullptr);
    ~FloatViewSetter();

private slots:
    void on_edit_editingFinished();

private:
    Ui::FloatViewSetter *ui;
};

#endif // FLOATVIEWSETTER_H
