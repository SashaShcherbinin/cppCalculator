#ifndef TESET_CALCULATOR_H
#define TESET_CALCULATOR_H

#include <QtWidgets>
#include <QRegExp>

class Calculator : public QWidget {
Q_OBJECT

public:
    explicit Calculator(QWidget *parent = nullptr) : QWidget(parent), display(new QLineEdit) {
        setMinimumWidth(400);
        setMinimumHeight(300);

        auto grid = new QGridLayout(this);
        initDisplay();
        grid->addWidget(display, 0, 0, 1, 4);

        for (int i = 1; i <= 9; ++i) {
            auto button = createButton(QString::number(i));
            grid->addWidget(button, (9 - i - 1) / 3 + 1, (i - 1) % 3);
        }

        grid->addWidget(createButton("0"), 4, 1);
        grid->addWidget(createButton("+"), 1, 3);
        grid->addWidget(createButton("-"), 2, 3);
        grid->addWidget(createButton("*"), 3, 3);
        grid->addWidget(createButton("/"), 4, 3);
        grid->addWidget(createButton("="), 4, 2);
        grid->addWidget(createButton("C"), 4, 0);
    }

private slots:

    void buttonClicked() {
        auto button = qobject_cast<QPushButton *>(sender());
        QString text = button->text();
        QString displayText = display->text();

        QString lastNumber = getLastNumber(displayText);
ª
        if (text == "C") {
            display->clear();
            storedNumber.clear();
            storedOperator.clear();
        } else if (text == "=") {
            if (!storedNumber.isEmpty() && !storedOperator.isEmpty() && !isCalculated) {
                double result = calculate(storedNumber.toDouble(), lastNumber.toDouble(), storedOperator);
                display->setText(displayText + text + QString::number(result));
                storedNumber = QString::number(result);
                isCalculated = true;
            }
        } else if (text == "+" || text == "-" || text == "*" || text == "/") {
            isCalculated = false;
            if (!storedOperator.isEmpty()) {
                display->clear();
            } else {
                storedNumber = displayText;
            }
            display->setText(storedNumber + text);
            storedOperator = text;
        } else {
            if (isCalculated) {
                display->clear();
                display->setText(text);
                storedNumber.clear();
                storedOperator.clear();
                isCalculated = false;
            } else {
                display->setText(displayText + text);
            }
        }
    }

    [[nodiscard]] static QString getLastNumber(const QString &displayText) {
        static QRegularExpression digitsRe("\\D(\\d+)");
        QRegularExpressionMatchIterator i = digitsRe.globalMatch(displayText);
        QRegularExpressionMatch lastMatch;
        while (i.hasNext()) {
            lastMatch = i.next();
        }
        QString lastNumber = lastMatch.captured(1);
        return lastNumber;
    }

private:
    [[nodiscard]] QPushButton *createButton(const QString &text) const {
        auto button = new QPushButton(text);
        button->setStyleSheet(
                "QPushButton { "
                "border-radius: 20px;"
                "background-color: #008CBA;"
                "color: white;"
                "font-size: 16px;"
                "font-weight: bold;"
                "padding: 12px 24px;"
                "}");
        connect(button, &QPushButton::clicked, this, &Calculator::buttonClicked);
        return button;
    }

    void initDisplay() {
        display->setReadOnly(true);
        display->setMinimumHeight(50);
        display->setAlignment(Qt::AlignRight);
        display->setTextMargins(5, 5, 5, 5);
        display->setStyleSheet("QLineEdit { font-size: 20px; }");
    }

    static double calculate(double left, double right, const QString &op) {
        if (op == "+") return left + right;
        if (op == "-") return left - right;
        if (op == "*") return left * right;
        if (op == "/") return right != 0 ? left / right : 0;
        return 0;
    }

    bool isCalculated = false;
    QString storedNumber;
    QString storedOperator;
    QLineEdit *display;
};


#endif //TESET_CALCULATOR_H
