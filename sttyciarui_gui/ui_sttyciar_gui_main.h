/********************************************************************************
** Form generated from reading ui file 'sttyciar_gui_main.ui'
**
** Created: Wed Sep 19 17:13:30 2007
**      by: Qt User Interface Compiler version 4.3.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_STTYCIAR_GUI_MAIN_H
#define UI_STTYCIAR_GUI_MAIN_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QStatusBar>
#include <QtGui/QTreeWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

class Ui_FormSttyciarGUIMain
{
public:
    QWidget *centralwidget;
    QVBoxLayout *vboxLayout;
    QHBoxLayout *hboxLayout;
    QLabel *label;
    QComboBox *comboNetworkDevices;
    QGroupBox *grpInterfaces;
    QVBoxLayout *vboxLayout1;
    QVBoxLayout *vboxLayout2;
    QLabel *lblInterfacesAvailable;
    QTreeWidget *treeAvailableInterfaces;
    QHBoxLayout *hboxLayout1;
    QSpacerItem *spacerItem;
    QPushButton *btnAddAllDevices;
    QPushButton *btnAddDevice;
    QPushButton *btnRemoveDevice;
    QPushButton *btnRemoveAllDevices;
    QSpacerItem *spacerItem1;
    QVBoxLayout *vboxLayout3;
    QLabel *lblUsedInterfaces;
    QTreeWidget *treeUsedInterfaces;
    QHBoxLayout *hboxLayout2;
    QSpacerItem *spacerItem2;
    QPushButton *btnStart;
    QPushButton *btnExit;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *FormSttyciarGUIMain)
    {
    if (FormSttyciarGUIMain->objectName().isEmpty())
        FormSttyciarGUIMain->setObjectName(QString::fromUtf8("FormSttyciarGUIMain"));
    QSize size(711, 600);
    size = size.expandedTo(FormSttyciarGUIMain->minimumSizeHint());
    FormSttyciarGUIMain->resize(size);
    centralwidget = new QWidget(FormSttyciarGUIMain);
    centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
    vboxLayout = new QVBoxLayout(centralwidget);
    vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
    hboxLayout = new QHBoxLayout();
    hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
    label = new QLabel(centralwidget);
    label->setObjectName(QString::fromUtf8("label"));

    hboxLayout->addWidget(label);

    comboNetworkDevices = new QComboBox(centralwidget);
    comboNetworkDevices->setObjectName(QString::fromUtf8("comboNetworkDevices"));
    QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    sizePolicy.setHorizontalStretch(5);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(comboNetworkDevices->sizePolicy().hasHeightForWidth());
    comboNetworkDevices->setSizePolicy(sizePolicy);

    hboxLayout->addWidget(comboNetworkDevices);


    vboxLayout->addLayout(hboxLayout);

    grpInterfaces = new QGroupBox(centralwidget);
    grpInterfaces->setObjectName(QString::fromUtf8("grpInterfaces"));
    vboxLayout1 = new QVBoxLayout(grpInterfaces);
    vboxLayout1->setObjectName(QString::fromUtf8("vboxLayout1"));
    vboxLayout2 = new QVBoxLayout();
    vboxLayout2->setObjectName(QString::fromUtf8("vboxLayout2"));
    lblInterfacesAvailable = new QLabel(grpInterfaces);
    lblInterfacesAvailable->setObjectName(QString::fromUtf8("lblInterfacesAvailable"));

    vboxLayout2->addWidget(lblInterfacesAvailable);

    treeAvailableInterfaces = new QTreeWidget(grpInterfaces);
    treeAvailableInterfaces->setObjectName(QString::fromUtf8("treeAvailableInterfaces"));
    treeAvailableInterfaces->setColumnCount(2);

    vboxLayout2->addWidget(treeAvailableInterfaces);


    vboxLayout1->addLayout(vboxLayout2);

    hboxLayout1 = new QHBoxLayout();
    hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
    spacerItem = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    hboxLayout1->addItem(spacerItem);

    btnAddAllDevices = new QPushButton(grpInterfaces);
    btnAddAllDevices->setObjectName(QString::fromUtf8("btnAddAllDevices"));
    QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
    sizePolicy1.setHorizontalStretch(0);
    sizePolicy1.setVerticalStretch(0);
    sizePolicy1.setHeightForWidth(btnAddAllDevices->sizePolicy().hasHeightForWidth());
    btnAddAllDevices->setSizePolicy(sizePolicy1);

    hboxLayout1->addWidget(btnAddAllDevices);

    btnAddDevice = new QPushButton(grpInterfaces);
    btnAddDevice->setObjectName(QString::fromUtf8("btnAddDevice"));
    sizePolicy1.setHeightForWidth(btnAddDevice->sizePolicy().hasHeightForWidth());
    btnAddDevice->setSizePolicy(sizePolicy1);

    hboxLayout1->addWidget(btnAddDevice);

    btnRemoveDevice = new QPushButton(grpInterfaces);
    btnRemoveDevice->setObjectName(QString::fromUtf8("btnRemoveDevice"));
    sizePolicy1.setHeightForWidth(btnRemoveDevice->sizePolicy().hasHeightForWidth());
    btnRemoveDevice->setSizePolicy(sizePolicy1);

    hboxLayout1->addWidget(btnRemoveDevice);

    btnRemoveAllDevices = new QPushButton(grpInterfaces);
    btnRemoveAllDevices->setObjectName(QString::fromUtf8("btnRemoveAllDevices"));
    sizePolicy1.setHeightForWidth(btnRemoveAllDevices->sizePolicy().hasHeightForWidth());
    btnRemoveAllDevices->setSizePolicy(sizePolicy1);

    hboxLayout1->addWidget(btnRemoveAllDevices);

    spacerItem1 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    hboxLayout1->addItem(spacerItem1);


    vboxLayout1->addLayout(hboxLayout1);

    vboxLayout3 = new QVBoxLayout();
    vboxLayout3->setObjectName(QString::fromUtf8("vboxLayout3"));
    lblUsedInterfaces = new QLabel(grpInterfaces);
    lblUsedInterfaces->setObjectName(QString::fromUtf8("lblUsedInterfaces"));

    vboxLayout3->addWidget(lblUsedInterfaces);

    treeUsedInterfaces = new QTreeWidget(grpInterfaces);
    treeUsedInterfaces->setObjectName(QString::fromUtf8("treeUsedInterfaces"));
    treeUsedInterfaces->setColumnCount(2);

    vboxLayout3->addWidget(treeUsedInterfaces);


    vboxLayout1->addLayout(vboxLayout3);


    vboxLayout->addWidget(grpInterfaces);

    hboxLayout2 = new QHBoxLayout();
    hboxLayout2->setObjectName(QString::fromUtf8("hboxLayout2"));
    spacerItem2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    hboxLayout2->addItem(spacerItem2);

    btnStart = new QPushButton(centralwidget);
    btnStart->setObjectName(QString::fromUtf8("btnStart"));
    sizePolicy1.setHeightForWidth(btnStart->sizePolicy().hasHeightForWidth());
    btnStart->setSizePolicy(sizePolicy1);

    hboxLayout2->addWidget(btnStart);

    btnExit = new QPushButton(centralwidget);
    btnExit->setObjectName(QString::fromUtf8("btnExit"));
    sizePolicy1.setHeightForWidth(btnExit->sizePolicy().hasHeightForWidth());
    btnExit->setSizePolicy(sizePolicy1);

    hboxLayout2->addWidget(btnExit);


    vboxLayout->addLayout(hboxLayout2);

    FormSttyciarGUIMain->setCentralWidget(centralwidget);
    menubar = new QMenuBar(FormSttyciarGUIMain);
    menubar->setObjectName(QString::fromUtf8("menubar"));
    menubar->setGeometry(QRect(0, 0, 711, 29));
    FormSttyciarGUIMain->setMenuBar(menubar);
    statusbar = new QStatusBar(FormSttyciarGUIMain);
    statusbar->setObjectName(QString::fromUtf8("statusbar"));
    FormSttyciarGUIMain->setStatusBar(statusbar);
    label->setBuddy(comboNetworkDevices);
    lblInterfacesAvailable->setBuddy(treeAvailableInterfaces);
    lblUsedInterfaces->setBuddy(treeUsedInterfaces);
    QWidget::setTabOrder(comboNetworkDevices, btnStart);
    QWidget::setTabOrder(btnStart, btnExit);
    QWidget::setTabOrder(btnExit, treeAvailableInterfaces);
    QWidget::setTabOrder(treeAvailableInterfaces, btnAddAllDevices);
    QWidget::setTabOrder(btnAddAllDevices, btnAddDevice);
    QWidget::setTabOrder(btnAddDevice, btnRemoveDevice);
    QWidget::setTabOrder(btnRemoveDevice, btnRemoveAllDevices);
    QWidget::setTabOrder(btnRemoveAllDevices, treeUsedInterfaces);

    retranslateUi(FormSttyciarGUIMain);

    QMetaObject::connectSlotsByName(FormSttyciarGUIMain);
    } // setupUi

    void retranslateUi(QMainWindow *FormSttyciarGUIMain)
    {
    FormSttyciarGUIMain->setWindowTitle(QApplication::translate("FormSttyciarGUIMain", "Sttyciar", 0, QApplication::UnicodeUTF8));
    label->setText(QApplication::translate("FormSttyciarGUIMain", "&Device Type:", 0, QApplication::UnicodeUTF8));
    grpInterfaces->setTitle(QApplication::translate("FormSttyciarGUIMain", "Interfaces", 0, QApplication::UnicodeUTF8));
    lblInterfacesAvailable->setText(QApplication::translate("FormSttyciarGUIMain", "Available Interfaces", 0, QApplication::UnicodeUTF8));
    treeAvailableInterfaces->headerItem()->setText(0, QApplication::translate("FormSttyciarGUIMain", "Device", 0, QApplication::UnicodeUTF8));
    treeAvailableInterfaces->headerItem()->setText(1, QApplication::translate("FormSttyciarGUIMain", "Information", 0, QApplication::UnicodeUTF8));
    treeAvailableInterfaces->clear();

    QTreeWidgetItem *__item = new QTreeWidgetItem(treeAvailableInterfaces);
    __item->setText(0, QApplication::translate("FormSttyciarGUIMain", "eth0", 0, QApplication::UnicodeUTF8));
    __item->setText(1, QApplication::translate("FormSttyciarGUIMain", "No Description", 0, QApplication::UnicodeUTF8));

    QTreeWidgetItem *__item1 = new QTreeWidgetItem(__item);
    __item1->setText(0, QApplication::translate("FormSttyciarGUIMain", "Address", 0, QApplication::UnicodeUTF8));
    __item1->setText(1, QApplication::translate("FormSttyciarGUIMain", "192.168.0.1", 0, QApplication::UnicodeUTF8));

    QTreeWidgetItem *__item2 = new QTreeWidgetItem(__item);
    __item2->setText(0, QApplication::translate("FormSttyciarGUIMain", "Net Mask", 0, QApplication::UnicodeUTF8));
    __item2->setText(1, QApplication::translate("FormSttyciarGUIMain", "255.255.255.0", 0, QApplication::UnicodeUTF8));

    QTreeWidgetItem *__item3 = new QTreeWidgetItem(treeAvailableInterfaces);
    __item3->setText(0, QApplication::translate("FormSttyciarGUIMain", "eth1", 0, QApplication::UnicodeUTF8));
    __item3->setText(1, QApplication::translate("FormSttyciarGUIMain", "No Description", 0, QApplication::UnicodeUTF8));

    QTreeWidgetItem *__item4 = new QTreeWidgetItem(__item3);
    __item4->setText(0, QApplication::translate("FormSttyciarGUIMain", "Address", 0, QApplication::UnicodeUTF8));
    __item4->setText(1, QApplication::translate("FormSttyciarGUIMain", "10.0.0.1", 0, QApplication::UnicodeUTF8));

    QTreeWidgetItem *__item5 = new QTreeWidgetItem(__item3);
    __item5->setText(0, QApplication::translate("FormSttyciarGUIMain", "Net Mask", 0, QApplication::UnicodeUTF8));
    __item5->setText(1, QApplication::translate("FormSttyciarGUIMain", "255.0.0.0", 0, QApplication::UnicodeUTF8));
    treeAvailableInterfaces->setToolTip(QApplication::translate("FormSttyciarGUIMain", "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans Serif'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">This displays the interfaces that are available to be bound to the device.</p></body></html>", 0, QApplication::UnicodeUTF8));
    btnAddAllDevices->setText(QApplication::translate("FormSttyciarGUIMain", "Add All", 0, QApplication::UnicodeUTF8));
    btnAddDevice->setText(QApplication::translate("FormSttyciarGUIMain", "Add Selected", 0, QApplication::UnicodeUTF8));
    btnRemoveDevice->setText(QApplication::translate("FormSttyciarGUIMain", "Remove Selected", 0, QApplication::UnicodeUTF8));
    btnRemoveAllDevices->setText(QApplication::translate("FormSttyciarGUIMain", "Remove All", 0, QApplication::UnicodeUTF8));
    lblUsedInterfaces->setText(QApplication::translate("FormSttyciarGUIMain", "Used Interfaces", 0, QApplication::UnicodeUTF8));
    treeUsedInterfaces->headerItem()->setText(0, QApplication::translate("FormSttyciarGUIMain", "Device", 0, QApplication::UnicodeUTF8));
    treeUsedInterfaces->headerItem()->setText(1, QApplication::translate("FormSttyciarGUIMain", "Information", 0, QApplication::UnicodeUTF8));
    treeUsedInterfaces->setToolTip(QApplication::translate("FormSttyciarGUIMain", "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans Serif'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">This displays the interfaces that will be bound to the device.</p></body></html>", 0, QApplication::UnicodeUTF8));
    btnStart->setText(QApplication::translate("FormSttyciarGUIMain", "&Start Device", 0, QApplication::UnicodeUTF8));
    btnExit->setText(QApplication::translate("FormSttyciarGUIMain", "&Exit", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(FormSttyciarGUIMain);
    } // retranslateUi

};

namespace Ui {
    class FormSttyciarGUIMain: public Ui_FormSttyciarGUIMain {};
} // namespace Ui

#endif // UI_STTYCIAR_GUI_MAIN_H
