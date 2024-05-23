#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onGuessSubmit();

private:
    Ui::MainWindow *ui;
    int randomNumber;
    int currentScore;
    int highScore;

    void resetGame();
    void generateRandomNumber(int min, int max);

    QLabel *highscoreLabel;
    QLabel *currentscoreLabel;
    QLabel *yourlastguessLabel;
    QLabel *correctguessLabel;
    QLineEdit *inputField;
    QLineEdit *rangeStartField;
    QLineEdit *rangeEndField;
    QPushButton *submitButton;
};

#endif // MAINWINDOW_H
