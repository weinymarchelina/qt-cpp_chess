#ifndef RESULTWINDOW_H
#define RESULTWINDOW_H

#include <QWidget>
#include <QString>

namespace Ui {
class ResultWindow;
}

class ResultWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ResultWindow(QWidget *parent = nullptr);
    ~ResultWindow();
    void setResult(QString result);

private:
    Ui::ResultWindow *ui;
    QString gameResult = "";

signals:
    void BackToMenuClicked();

private slots:
    void on_playAgainButton_clicked();
    void on_exitButton_clicked();
};

#endif // RESULTWINDOW_H
