#include <QApplication>
#include <QSplashScreen>
#include <Windows.h>
#include "gtmainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

	GTMainWindow * w = new GTMainWindow();

	QString iconPath = ":/Resources/gt_icon.png";
    //QString iconPath = "G:\\data\\sebastianvilla139\\work\\qt\\last_v9\\GTGenerator\\GTGenerator\\Resources\\gt_icon.png";
    //QString iconPath = "gt_icon.png";

    QPixmap pixmap(iconPath);

    QFont splashFont;
    splashFont.setFamily("Arial");
    splashFont.setBold(true);
    splashFont.setPixelSize(12);

    QSplashScreen splash(pixmap);
    splash.setFont(splashFont);
    splash.show();
    splash.showMessage("GTGenerator v1.6.1\r\nLoading application . . .\r\nGPRS - 2015\r\n", Qt::AlignHCenter | Qt::AlignBottom, Qt::white);

    Sleep(uint(3000));
    a.processEvents();

    QPixmap fileImage;
    fileImage.load(iconPath);	

    w->setWindowIcon(QIcon(fileImage));
    w->setWindowTitle("GTGenerator");

    ShowWindow(w->winId(), SW_HIDE);
    SetWindowLongPtr(w->winId(), GWL_EXSTYLE, GetWindowLongPtr(w->winId(), GWL_EXSTYLE) | WS_EX_APPWINDOW);
    ShowWindow(w->winId(), SW_SHOW);

    w->showMaximized();
    splash.finish(w);

    return a.exec();
}
