#include <QCloseEvent>

#include "lcdwindow.h"


#include <QDebug>
#include "lcdinput.h"

LcdWindow::LcdWindow(QWidget *parent) : QMainWindow(parent) {
    setupUi();
    setFixedSize(800, 150);
    setWindowTitle("16x2 LCD");
    cursor = 0;
    displayRowPos = 0;

    display[0][0]->setStyleSheet("background-color: black; color: green; font-family: Courier New; font-size: 40px; font-weight: bold; border: 3px solid red");

    for (int row = 0; row < 16; ++row) {
        for (int col = 0; col < 16; ++col) {
            storedSymbols[row][col] = '\0';
        }
    }

    LcdInput *inp = new LcdInput(this);
    inp->show();
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

void LcdWindow::updateDisplay(bool down){
    clearDisplay();

    int pos = 1;
    // update in bottom direction
    if (down) {
        for (int row = 0; row < 2; ++row) {
            for (int col = 0; col < 16; ++col) {
                display[row][col]->setText(QString(storedSymbols[(cursor / 16) - pos][col]));
            }
            pos = 0;
        }
    }
    // update in top direction
    else {
        pos = 0;
        for (int row = 0; row < 2; ++row) {
            for (int col = 0; col < 16; ++col) {
                // error if cursor row > 3!
                display[row][col]->setText(QString(storedSymbols[(cursor / 16) + pos][col]));
            }
            pos = 1;
        }
    }
}

void LcdWindow::setSymbol(const char &symbol) {
    // Enter
    if (symbol == 0x0d) {

    }
    // Up Arrow
    else if (symbol == 0x18) {

    }
    // Down Arrow
    else if (symbol == 0x19) {

    }
    // Right Arrow
    else if (symbol == 0x1a) {
        if (cursor == 256) {
            return;
        }
        if (cursor == 255 && storedSymbols[cursor / 16][cursor % 16] != '\0') {
            display[displayRowPos][cursor % 16]->setStyleSheet("background-color: black; color: green; font-family: Courier New; font-size: 40px; font-weight: bold");
            cursor++;
            display[displayRowPos][cursor % 16]->setStyleSheet("background-color: black; color: green; font-family: Courier New; font-size: 40px; font-weight: bold; border-right: 3px solid red");
            return;
        }
        if (cursor % 16 == 15) {
            int tmp = cursor;
            do {
                tmp++;
            } while(storedSymbols[tmp / 16][tmp % 16] == '\0' && tmp != 255);

            if (tmp == 255) {
                return;
            }

            display[displayRowPos][cursor % 16]->setStyleSheet("background-color: black; color: green; font-family: Courier New; font-size: 40px; font-weight: bold");
            cursor = tmp;
            displayRowPos = 1;
            updateDisplay(1);
            display[displayRowPos][cursor % 16]->setStyleSheet("background-color: black; color: green; font-family: Courier New; font-size: 40px; font-weight: bold; border: 3px solid red");
        }
        else if (storedSymbols[cursor / 16][cursor % 16] != '\0'){
            display[displayRowPos][cursor % 16]->setStyleSheet("background-color: black; color: green; font-family: Courier New; font-size: 40px; font-weight: bold");
            cursor++;
            display[displayRowPos][cursor % 16]->setStyleSheet("background-color: black; color: green; font-family: Courier New; font-size: 40px; font-weight: bold; border: 3px solid red");
        }
    }
    // Left Arrow
    else if (symbol == 0x1b) {
        if (cursor == 0) {
            return;
        }
        if (cursor % 16 == 0) {
            display[displayRowPos][cursor % 16]->setStyleSheet("background-color: black; color: green; font-family: Courier New; font-size: 40px; font-weight: bold");
            do {
                cursor--;
            } while(storedSymbols[cursor / 16][cursor % 16] == '\0');
            displayRowPos = 0;
            updateDisplay(0);
            display[displayRowPos][cursor % 16]->setStyleSheet("background-color: black; color: green; font-family: Courier New; font-size: 40px; font-weight: bold; border: 3px solid red");
        }
        else {
            display[displayRowPos][cursor % 16]->setStyleSheet("background-color: black; color: green; font-family: Courier New; font-size: 40px; font-weight: bold");
            cursor--;
            display[displayRowPos][cursor % 16]->setStyleSheet("background-color: black; color: green; font-family: Courier New; font-size: 40px; font-weight: bold; border: 3px solid red");
        }
    }
    // Delete
    else if (symbol == 0x7f) {

    }
    // Backspace
    else if (symbol == 0x08) {

    }
    // Other allowed symbols
    else if (symbol >= 0x20 && symbol <= 0x7e) {
        qDebug() << "Symbol: " << symbol << "; Hex: " << hex << (int)symbol;

        // check forbidden cursor pos
        if (cursor == 256){
            return;
        }
        // check last cursor pos
        if (cursor == 255) {
            storedSymbols[cursor / 16][cursor % 16] = symbol;

            // update display
            display[displayRowPos][cursor % 16]->setText(QString(symbol));
            display[displayRowPos][cursor % 16]->setStyleSheet("background-color: black; color: green; font-family: Courier New; font-size: 40px; font-weight: bold; border-right: 3px solid red");

            // update cursor
            cursor++;
            return;
        }
        // check for last position
        if (cursor % 16 == 15){
            // update all stored chars
            storedSymbols[cursor / 16][cursor % 16] = symbol;

            // update display
            display[displayRowPos][cursor % 16]->setText(QString(symbol));
            display[displayRowPos][cursor % 16]->setStyleSheet("background-color: black; color: green; font-family: Courier New; font-size: 40px; font-weight: bold;");

            // update cursors
            cursor++;
            displayRowPos = 1;

            display[displayRowPos][cursor % 16]->setStyleSheet("background-color: black; color: green; font-family: Courier New; font-size: 40px; font-weight: bold; border: 3px solid red");

            updateDisplay(1);
        }

        // check for elements after cursor
        //else if (storedSymbols[(cursor+1) / 16][(cursor+1) % 16] != '\0'){

        //}

        else {
            storedSymbols[cursor / 16][cursor % 16] = symbol;

            display[displayRowPos][cursor % 16]->setText(QString(symbol));
            display[displayRowPos][cursor % 16]->setStyleSheet("background-color: black; color: green; font-family: Courier New; font-size: 40px; font-weight: bold;");

            cursor++;

            display[displayRowPos][cursor % 16]->setStyleSheet("background-color: black; color: green; font-family: Courier New; font-size: 40px; font-weight: bold; border: 3px solid red");
        }


    }
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
