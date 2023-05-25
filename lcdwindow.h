#ifndef LcdWindow_H
#define LcdWindow_H

#include <QWidget>
#include <QMainWindow>
#include <QLabel>

class LcdWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LcdWindow(QWidget *parent = nullptr);
    ~LcdWindow();

    void clearDisplay();
    void setSymbol(int row, int col, const QString &symbol);

protected:
  void closeEvent(QCloseEvent *event);

private:
    void setupUi();
    QLabel *display[2][16];

signals:
       void closeLcd();
};

#endif
