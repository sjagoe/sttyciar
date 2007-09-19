/********************************************************************************
** Form generated from reading ui file 'textstatisticswidget.ui'
**
** Created: Wed Sep 19 12:38:56 2007
**      by: Qt User Interface Compiler version 4.3.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_TEXTSTATISTICSWIDGET_H
#define UI_TEXTSTATISTICSWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QTableWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

class Ui_TextStatisticsWidget
{
public:
    QVBoxLayout *vboxLayout;
    QGroupBox *grpBalance;
    QHBoxLayout *hboxLayout;
    QTableWidget *tblBalance;
    QGroupBox *grpRates;
    QGridLayout *gridLayout;
    QLabel *lblPacketsPerSecond;
    QLabel *lblBytesPerSecond;
    QLineEdit *edtPacketsPerSecond;
    QLineEdit *edtBytesPerSecond;

    void setupUi(QWidget *TextStatisticsWidget)
    {
    if (TextStatisticsWidget->objectName().isEmpty())
        TextStatisticsWidget->setObjectName(QString::fromUtf8("TextStatisticsWidget"));
    QSize size(392, 432);
    size = size.expandedTo(TextStatisticsWidget->minimumSizeHint());
    TextStatisticsWidget->resize(size);
    vboxLayout = new QVBoxLayout(TextStatisticsWidget);
    vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
    grpBalance = new QGroupBox(TextStatisticsWidget);
    grpBalance->setObjectName(QString::fromUtf8("grpBalance"));
    hboxLayout = new QHBoxLayout(grpBalance);
    hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
    tblBalance = new QTableWidget(grpBalance);
    tblBalance->setObjectName(QString::fromUtf8("tblBalance"));
    tblBalance->setAlternatingRowColors(true);

    hboxLayout->addWidget(tblBalance);


    vboxLayout->addWidget(grpBalance);

    grpRates = new QGroupBox(TextStatisticsWidget);
    grpRates->setObjectName(QString::fromUtf8("grpRates"));
    gridLayout = new QGridLayout(grpRates);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    lblPacketsPerSecond = new QLabel(grpRates);
    lblPacketsPerSecond->setObjectName(QString::fromUtf8("lblPacketsPerSecond"));

    gridLayout->addWidget(lblPacketsPerSecond, 0, 0, 1, 1);

    lblBytesPerSecond = new QLabel(grpRates);
    lblBytesPerSecond->setObjectName(QString::fromUtf8("lblBytesPerSecond"));

    gridLayout->addWidget(lblBytesPerSecond, 0, 1, 1, 1);

    edtPacketsPerSecond = new QLineEdit(grpRates);
    edtPacketsPerSecond->setObjectName(QString::fromUtf8("edtPacketsPerSecond"));
    edtPacketsPerSecond->setReadOnly(true);

    gridLayout->addWidget(edtPacketsPerSecond, 1, 0, 1, 1);

    edtBytesPerSecond = new QLineEdit(grpRates);
    edtBytesPerSecond->setObjectName(QString::fromUtf8("edtBytesPerSecond"));
    edtBytesPerSecond->setReadOnly(true);

    gridLayout->addWidget(edtBytesPerSecond, 1, 1, 1, 1);


    vboxLayout->addWidget(grpRates);

    lblPacketsPerSecond->setBuddy(edtPacketsPerSecond);
    lblBytesPerSecond->setBuddy(edtBytesPerSecond);

    retranslateUi(TextStatisticsWidget);

    QMetaObject::connectSlotsByName(TextStatisticsWidget);
    } // setupUi

    void retranslateUi(QWidget *TextStatisticsWidget)
    {
    TextStatisticsWidget->setWindowTitle(QApplication::translate("TextStatisticsWidget", "Statistics", 0, QApplication::UnicodeUTF8));
    grpBalance->setTitle(QApplication::translate("TextStatisticsWidget", "Load Balance", 0, QApplication::UnicodeUTF8));
    grpRates->setTitle(QApplication::translate("TextStatisticsWidget", "Data Rates", 0, QApplication::UnicodeUTF8));
    lblPacketsPerSecond->setText(QApplication::translate("TextStatisticsWidget", "Packets/Second:", 0, QApplication::UnicodeUTF8));
    lblBytesPerSecond->setText(QApplication::translate("TextStatisticsWidget", "Bytes/Second:", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(TextStatisticsWidget);
    } // retranslateUi

};

namespace Ui {
    class TextStatisticsWidget: public Ui_TextStatisticsWidget {};
} // namespace Ui

#endif // UI_TEXTSTATISTICSWIDGET_H
