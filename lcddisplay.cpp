#include "lcddisplay.h"
#include <QPainter>


LcdDisplay::LcdDisplay(QWidget *parent) : QMainWindow(parent) {//QWidget(parent) {
    setFixedSize(160, 40);
    displayText("Hello, World!asdf");
}

void LcdDisplay::displayText(const QString &text){
    lcdText = text.left(16);
    update();
}

void LcdDisplay::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::white);
    painter.fillRect(rect(), Qt::black);

    QFont font("Courier", 14, QFont::Bold);
    painter.setFont(font);

    int x = 10;
    int y = 25;

    for (const QChar &c : lcdText) {
        painter.drawText(x, y, QString(c));
        x += 10;
    }
}
