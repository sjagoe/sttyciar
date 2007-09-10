#ifndef __SLLISTENER_HH__
#define __SLLISTENER_HH__

/*!
The SLListener is a (pure virtual) public interface that is implemented by the
User Interface so that the Statistics Layer can pass meaningful information
to it.

@author Simon Jagoe
*/
class SLListener
{
    public:
        /*!
        A method to send updated statistical/usage information to the UI.
        */
        virtual void updateStatistics(
            /* some class containing meaningful information */ ) = 0;

        /*!
        A method to send a list of available network interfaces/devices to the
        UI.
        */
        virtual void availableInterfaces(
            /* interface linked list class thing */ ) = 0;
};

#endif
