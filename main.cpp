#include "mainwindow.h"

#include <QApplication>
#include <QLayout>
#include <QAction>

#include "timertext.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    TimerText *text = new TimerText();
    text->setContextMenuPolicy(Qt::ContextMenuPolicy::NoContextMenu);
    text->installEventFilter(&w);
    text->start();
    w.layout()->addWidget(text);

    QAction *action = new QAction("Exit");
    QObject::connect(action, &QAction::triggered, &a, &QApplication::quit);
    w.addAction(action);

    qDebug() << "Showing main window";
    w.show();
    return a.exec();
}
