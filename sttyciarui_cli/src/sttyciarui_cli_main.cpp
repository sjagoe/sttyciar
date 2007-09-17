#include <QTextStream>

#include "sttyciarui_cli.hh"
#include "sttyciarui_cli_main.hh"

const short SttyciarUI::EXIT;
const short SttyciarUI::HUB_TYPE;

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
    out << SttyciarUI::HUB_TYPE << ": Hub\n";
    out << '\n';
    out << SttyciarUI::EXIT << ": Exit\n";
    out << '\n';
    out << "Enter Selection: >> ";

    QTextStream in(stdin);

    int selection = -1;

    if (((QIODevice*)stdin)->waitForReadyRead(1000))
        in >> selection;

    switch (selection)
    {
        case SttyciarUI::EXIT:
        {
            emit exit();
            return;
        }
        case SttyciarUI::HUB_TYPE:
        {
            emit startSttyciar(SttyciarUI::HUB_TYPE);
            return;
        }
        default:
        {
            emit redraw();
            return;
        }
    }
}
