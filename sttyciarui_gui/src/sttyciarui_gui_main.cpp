#include <iostream>

#include <QList>
#include <QTreeWidgetItem>
#include <QTreeWidget>
#include <QMessageBox>

#include "ui_sttyciar_gui_main.h"

#include "sttyciarui_gui_main.hh"
#include "sttyciarui_common.hh"

#include "device.hh"

using namespace std;

const short SttyciarUI::HUB_TYPE;

SttyciarGUIMain::SttyciarGUIMain(QWidget* parent)
    : QMainWindow(parent)
{
    _ui = new Ui::FormSttyciarGUIMain;
    _ui->setupUi(this);
    _ui->treeAvailableInterfaces->clear();
    _ui->treeAvailableInterfaces->setColumnWidth(0, 150);
    _ui->treeUsedInterfaces->setColumnWidth(0, 150);
}

void SttyciarGUIMain::setDevices( const QList<shared_ptr<Device> >& devices )
{
    _ui->treeAvailableInterfaces->clear();
    _ui->treeUsedInterfaces->clear();

    QTreeWidgetItem* rootItem;
    QTreeWidgetItem* subItem;
#if defined (WIN32)
    QTreeWidgetItem* subsubItem;
#endif

    //QList<shared_ptr<Device> >::const_iterator iter = devices->begin();
    //for (; iter != devices->end(); iter++)
    foreach ( shared_ptr<Device> device, devices )
    {
        rootItem = new QTreeWidgetItem( _ui->treeAvailableInterfaces );
        rootItem->setText(0, device->getName().data());
        QString description = device->getDescription().data();
        if (description == QString())
            description = "[No description available]";
        rootItem->setText(1, description);

        QList<DeviceAddress> addrList = device->getAddresses();

        foreach ( DeviceAddress address, addrList )
        {
            // IP Address
            subItem = new QTreeWidgetItem( rootItem );
            subItem->setText(0, tr("IP Address"));
            subItem->setText(1, address.getAddress().toIPString().data());
#if defined (WIN32)
            // Net Mask
            subsubItem = new QTreeWidgetItem( subItem );
            subsubItem->setText(0, tr("Netmask"));
            subsubItem->setText(1, address.getNetmask().toIPString().data());
            // Broadcast Address
            subsubItem = new QTreeWidgetItem( subItem );
            subsubItem->setText(0, tr("Broadcast Address"));
            subsubItem->setText(1, address.getBroadcastAddress().toIPString().data());
#endif
            // Destination Address
//            subsubItem = new QTreeWidgetItem( subItem );
//            subsubItem->setText(0, tr("Destination Address"));
//            subsubItem->setText(1, address.getDestinationAddress().toIPString().data());
//            cout << "9" << endl;
        }
    }
    _ui->treeAvailableInterfaces->sortItems(0, Qt::AscendingOrder);
}

void SttyciarGUIMain::setNetworkDevices( QMap<int, QString> networkDevices )
{
    for (int i = 0; i < networkDevices.size(); i++)
    {
        if (!networkDevices[i].isEmpty())
        {
            _ui->comboNetworkDevices->addItem( networkDevices[i] );
        }
    }
}

void SttyciarGUIMain::on_btnStart_clicked()
{
    shared_ptr<QStringList> devices(new QStringList);
    int numDevices = _ui->treeUsedInterfaces->topLevelItemCount();
    if (numDevices > 0)
    {
        for (int i = 0; i < numDevices; i++)
        {
            QTreeWidgetItem* topLevelItem = _ui->treeUsedInterfaces->topLevelItem(i);
            *devices << topLevelItem->text(0);
        }
        emit startSttyciar(_ui->comboNetworkDevices->currentText(), devices);
    }
    else
    {
        QMessageBox::critical( this, tr("Error"), tr("Please bind network interfaces to the device.") );
    }
}

void SttyciarGUIMain::on_btnAddAllDevices_clicked()
{
    moveAllDevices( _ui->treeAvailableInterfaces, _ui->treeUsedInterfaces );
}

void SttyciarGUIMain::on_btnAddDevice_clicked()
{
    moveDevice( _ui->treeAvailableInterfaces, _ui->treeUsedInterfaces );
}

void SttyciarGUIMain::on_btnRemoveDevice_clicked()
{
    moveDevice( _ui->treeUsedInterfaces, _ui->treeAvailableInterfaces );
}

void SttyciarGUIMain::on_btnRemoveAllDevices_clicked()
{
    moveAllDevices( _ui->treeUsedInterfaces, _ui->treeAvailableInterfaces );
}

void SttyciarGUIMain::on_btnExit_clicked()
{
    emit exit();
}

void SttyciarGUIMain::moveAllDevices(QTreeWidget* sourceInterfaceTree,
    QTreeWidget* destinationInterfaceTree)
{
    while ( sourceInterfaceTree->topLevelItemCount() != 0 )
    {
        QTreeWidgetItem* selectedItem =
            sourceInterfaceTree->takeTopLevelItem(0);
        destinationInterfaceTree->addTopLevelItem(selectedItem);
        destinationInterfaceTree->sortItems(0, Qt::AscendingOrder);
    }
}

void SttyciarGUIMain::moveDevice(QTreeWidget* sourceInterfaceTree,
    QTreeWidget* destinationInterfaceTree)
{
    QList<QTreeWidgetItem*> selection =
        sourceInterfaceTree->selectedItems();
    if (! selection.isEmpty())
    {
        QTreeWidgetItem* selectedItem = selection.first();
        while (selectedItem->parent() != 0)
        {
            selectedItem = selectedItem->parent();
        }
        int selectedItemIndex =
            sourceInterfaceTree->indexOfTopLevelItem(selectedItem);

        if (selectedItemIndex != -1)
        {
            selectedItem = sourceInterfaceTree->takeTopLevelItem(
                selectedItemIndex);
            destinationInterfaceTree->addTopLevelItem(selectedItem);
            destinationInterfaceTree->sortItems(0, Qt::AscendingOrder);
        }
    }
}
