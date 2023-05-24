#ifndef LCDDISPLAY_H
#define LCDDISPLAY_H

#include <QWidget>
#include <QMainWindow>

class LcdDisplay : public QMainWindow//QWidget
{
    Q_OBJECT

public:
    explicit LcdDisplay(QWidget *parent = nullptr);
    void displayText(const QString &text);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QString lcdText;

signals:

};

#endif // LCDDISPLAY_H
