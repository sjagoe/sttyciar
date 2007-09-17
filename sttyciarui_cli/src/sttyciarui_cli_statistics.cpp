#include "sttyciarui_cli_statistics.hh"

SttyciarCLIStatistics::SttyciarCLIStatistics()
{

}

void SttyciarCLIStatistics::draw()
{
    QTextStream out(stdout);
    QTextStream in(stdin);

    out << "Select an action:\n";
    out << "-----------------\n\n";
    out << "1: Stop Sttyciar and return to main menu\n\n";
    out << "0: Stop Sttyciar and exit\n\n";
    out << "Enter Selection: >> ";

    int selection = -1;
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
            emit stopSttyciar();
            return;
        }
        default:
        {
            emit redraw();
            return;
        }
    }
}
