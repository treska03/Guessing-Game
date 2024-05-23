#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <cstdlib>
#include <ctime>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QFont>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , currentScore(0)
    , highScore(0)
{
    ui->setupUi(this);
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // Define the scale factor
    const int scaleFactor = 3;

    // Set up labels with increased font size
    QFont font;
    font.setPointSize(10 * scaleFactor);

    highscoreLabel = new QLabel("Highscore: 0");
    highscoreLabel->setFont(font);
    highscoreLabel->setAlignment(Qt::AlignCenter);

    currentscoreLabel = new QLabel("Current Score: 0");
    currentscoreLabel->setFont(font);
    currentscoreLabel->setAlignment(Qt::AlignCenter);

    yourlastguessLabel = new QLabel("Your Last Guess:");
    yourlastguessLabel->setFont(font);

    correctguessLabel = new QLabel("Correct Guess:");
    correctguessLabel->setFont(font);

    // Set up input field with increased size and font
    inputField = new QLineEdit();
    inputField->setPlaceholderText("Enter your guess");
    inputField->setFont(font);
    inputField->setAlignment(Qt::AlignCenter);
    inputField->setMinimumHeight(30 * scaleFactor);

    // Set up range input fields side by side
    rangeStartField = new QLineEdit();
    rangeStartField->setPlaceholderText("Lower bound");
    rangeStartField->setFont(font);
    rangeStartField->setAlignment(Qt::AlignCenter);
    rangeStartField->setMinimumHeight(30 * scaleFactor);

    rangeEndField = new QLineEdit();
    rangeEndField->setPlaceholderText("Upper bound");
    rangeEndField->setFont(font);
    rangeEndField->setAlignment(Qt::AlignCenter);
    rangeEndField->setMinimumHeight(30 * scaleFactor);

    QHBoxLayout *rangeLayout = new QHBoxLayout;
    rangeLayout->addWidget(rangeStartField);
    rangeLayout->addWidget(rangeEndField);

    // Set up button with increased size and font
    submitButton = new QPushButton("Guess!");
    submitButton->setFont(font);
    submitButton->setMinimumHeight(30 * scaleFactor);

    // Set up layout
    QFormLayout *formLayout = new QFormLayout;
    formLayout->addRow(highscoreLabel);
    formLayout->addRow(currentscoreLabel);

    QHBoxLayout *guessLayout = new QHBoxLayout;
    guessLayout->addWidget(yourlastguessLabel);
    guessLayout->addWidget(correctguessLabel);

    QVBoxLayout *inputLayout = new QVBoxLayout;
    inputLayout->addLayout(rangeLayout);  // Add range layout here
    inputLayout->addLayout(guessLayout);
    inputLayout->addWidget(inputField);
    inputLayout->addWidget(submitButton);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(formLayout);
    mainLayout->addLayout(inputLayout);

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);

    // Adjust the window size to accommodate larger components
    setWindowTitle("Game UI");
    resize(400 * scaleFactor, 200 * scaleFactor);

    // Connect the submit button to the onGuessSubmit slot
    connect(submitButton, &QPushButton::clicked, this, &MainWindow::onGuessSubmit);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resetGame()
{
    currentScore = 0;
    currentscoreLabel->setText("Current Score: 0");
    currentscoreLabel->setStyleSheet("QLabel { color : black; }");
}

void MainWindow::generateRandomNumber(int min, int max)
{
    randomNumber = std::rand() % (max - min + 1) + min;
}

void MainWindow::onGuessSubmit()
{
    bool ok;
    int guess = inputField->text().toInt(&ok);

    if (!ok) {
        yourlastguessLabel->setText("Your Last Guess: Invalid input!");
        return;
    }

    int rangeStart = rangeStartField->text().toInt();
    int rangeEnd = rangeEndField->text().toInt();
    if (rangeStartField->text().isEmpty() || rangeEndField->text().isEmpty() || rangeStart >= rangeEnd) {
        generateRandomNumber(1, 10);
    } else {
        generateRandomNumber(rangeStart, rangeEnd);
    }

    yourlastguessLabel->setText("Your Last Guess: " + QString::number(guess));

    correctguessLabel->setText("Correct Guess: " + QString::number(randomNumber));
    yourlastguessLabel->setText("Your Last Guess: " + QString::number(guess));

    if (guess == randomNumber) {
        currentScore++;
        if (currentScore > highScore) {
            highScore = currentScore;
            highscoreLabel->setText("Highscore: " + QString::number(highScore));
            currentscoreLabel->setStyleSheet("QLabel { color : red; }");
        }
    } else {
        currentScore = 0; // Reset the current score
        resetGame();
    }

    currentscoreLabel->setText("Current Score: " + QString::number(currentScore));
    inputField->clear(); // Clear the input field for the next guess
}
