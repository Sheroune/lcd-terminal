#include <QPainter>
#include <QGridLayout>
#include <QDialog>
#include <QCloseEvent>

#include "lcdwindow.h"


LcdWindow::LcdWindow(QWidget *parent) : QMainWindow(parent) {
    setupUi();
    setFixedSize(800, 150);
    setWindowTitle("16x2 LCD");
}

LcdWindow::~LcdWindow() {
    for (int row = 0; row < 2; ++row) {
        for (int col = 0; col < 16; ++col) {
            delete display[row][col];
        }
    }
}

void LcdWindow::clearDisplay() {
    for (int row = 0; row < 2; ++row) {
        for (int col = 0; col < 16; ++col) {
            display[row][col]->clear();
        }
    }
}

void LcdWindow::setSymbol(int row, int col, const QString &symbol) {
    if (row < 0 || row >= 2 || col < 0 || col >= 16) {
        return;
    }

    display[row][col]->setText(symbol);
}

void LcdWindow::setupUi() {
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QGridLayout *gridLayout = new QGridLayout(centralWidget);

    for (int row = 0; row < 2; ++row) {
        for (int col = 0; col < 16; ++col) {
            QLabel *cell = new QLabel;
            cell->setAutoFillBackground(true);
            cell->setStyleSheet("background-color: black; color: green; font-family: Courier New; font-size: 40px; font-weight: bold;");
            cell->setAlignment(Qt::AlignCenter);

            display[row][col] = cell;

            gridLayout->addWidget(cell, row, col);
        }
    }

    centralWidget->setLayout(gridLayout);
}

void LcdWindow::closeEvent(QCloseEvent *event){
    emit closeLcd();
}
