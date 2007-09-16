#include "sttyciarui_cli_main.hh"

#include <QTextStream>

SttyciarCLIMain::SttyciarCLIMain()
{
    draw();
}

void SttyciarCLIMain::draw()
{
    QTextStream out(stdout);
    out << "Select a device type:\n";
    out << "---------------------\n";
    out << '\n';
    out << "1: Hub\n";
    out << '\n';
    out << "0: Exit\n";
    out << '\n';
    out << "Enter Selection: >> ";

    QTextStream in(stdin);

    int selection = -1;

    if (((QIODevice*)stdin)->waitForReadyRead(1000))
        in >> selection;

    switch (selection)
    {
        case 0:
        {
            emit exit();
            return;
        }
        case 1:
        {
            emit startSttyciar(QString("hub"));
            return;
        }
        default:
        {
            emit redraw();
            return;
        }
    }
}
