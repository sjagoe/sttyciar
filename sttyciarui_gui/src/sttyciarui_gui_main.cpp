#include <iostream>

#include <QList>
#include <QTreeWidgetItem>

#include "sttyciarui_gui_main.hh"
#include "sttyciarui_common.hh"

using namespace std;

const short SttyciarUI::HUB_TYPE;

SttyciarGUIMain::SttyciarGUIMain()
{
    _ui.setupUi(this);
    _ui.treeAvailableInterfaces->sortItems(0, Qt::AscendingOrder);
}

void SttyciarGUIMain::on_btnStart_clicked()
{
    emit startSttyciar(SttyciarUI::HUB_TYPE);
}

void SttyciarGUIMain::on_btnAddAllDevices_clicked()
{
    moveAllDevices( _ui.treeAvailableInterfaces, _ui.treeUsedInterfaces );
}

void SttyciarGUIMain::on_btnAddDevice_clicked()
{
    moveDevice( _ui.treeAvailableInterfaces, _ui.treeUsedInterfaces );
}

void SttyciarGUIMain::on_btnRemoveDevice_clicked()
{
    moveDevice( _ui.treeUsedInterfaces, _ui.treeAvailableInterfaces );
}

void SttyciarGUIMain::on_btnRemoveAllDevices_clicked()
{
    moveAllDevices( _ui.treeUsedInterfaces, _ui.treeAvailableInterfaces );
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
