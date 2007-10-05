//#include <iostream>

#include <Qt>
#include <QList>
#include <QTreeWidgetItem>
#include <QTreeWidget>
#include <QMessageBox>
#include <QFile>
#include <QFileDialog>

#include "ui_sttyciar_gui_main.h"

#include "sttyciarui_gui_main.hh"
#include "sttyciarui_common.hh"

#include "device.hh"

using namespace std;

//const short SttyciarUI::HUB_TYPE;

SttyciarGUIMain::SttyciarGUIMain(QWidget* parent)
    : QMainWindow(parent)
{
    _ui = new Ui::FormSttyciarGUIMain;
    _ui->setupUi(this);
    _ui->treeAvailableInterfaces->clear();
    _ui->treeAvailableInterfaces->setColumnWidth(0, 150);
    _ui->treeUsedInterfaces->setColumnWidth(0, 150);

    connect( this->_ui->chkEnableDump, SIGNAL( stateChanged(int) ), this, SLOT( on_chkEnableDump_stateChanged() ) );
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
            QTreeWidgetItem* topLevelItem = this->_ui->treeUsedInterfaces->topLevelItem(i);
            *devices << topLevelItem->text(0);
        }
        emit startSttyciar(this->_ui->comboNetworkDevices->currentText(), devices, this->_ui->edtDump->text());
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

void SttyciarGUIMain::on_chkEnableDump_stateChanged()
{
    // if the checkbox is checked (i.e. dump to file enabled)
    if (this->_ui->chkEnableDump->checkState() == Qt::Checked)
    {
        // if there is no filename
        if (this->_ui->edtDump->text() == QString())
        {
            this->on_btnBrowseDump_clicked();
        }
        if (this->_ui->edtDump->text() == QString())
        {
            this->_ui->chkEnableDump->setCheckState( Qt::Unchecked );
        }
    }
    else if ( this->_ui->chkEnableDump->checkState() == Qt::Unchecked )
    {
        this->_ui->edtDump->clear(  );
    }
}

void SttyciarGUIMain::on_btnBrowseDump_clicked()
{
    QString fileName =
        QFileDialog::getSaveFileName( this, tr( "Packet Dump File" ),
            QString(), tr( "Packet Capture Files (*.cap)" ) );
    if (fileName != QString())
    {
        this->_ui->edtDump->setText(fileName);
    }
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

void SttyciarGUIMain::on_treeAvailableInterfaces_itemDoubleClicked()
{
    moveDevice( _ui->treeAvailableInterfaces, _ui->treeUsedInterfaces );
}

void SttyciarGUIMain::on_treeUsedInterfaces_itemDoubleClicked()
{
    moveDevice( _ui->treeUsedInterfaces, _ui->treeAvailableInterfaces );
}
