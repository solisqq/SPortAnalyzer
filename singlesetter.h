#ifndef SINGLESETTER_H
#define SINGLESETTER_H

#include <QWidget>

namespace Ui {
class SingleSetter;
}

class SingleSetter : public QWidget
{
    Q_OBJECT
    double value=0;
public:
    explicit SingleSetter(const QString referencePath, double val, QWidget *parent = nullptr);
    ~SingleSetter();

private slots:
    void on_dataEdit_editingFinished();

private:
    Ui::SingleSetter *ui;
    void setValue(double val);
    void setName(const QString &path);
signals:
    void requestChangeValue(const QString& valName, double val);
};

#endif // SINGLESETTER_H
