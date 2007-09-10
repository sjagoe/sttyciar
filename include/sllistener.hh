#ifndef __SLLISTENER_HH__
#define __SLLISTENER_HH__


class SLListener
{
    public:
        virtual void updateStatistics(
            /* some class containing meaningful information */ ) = 0;

        virtual void availableInterfaces(
            /* interface linked list class thing */ ) = 0;
};

#endif
