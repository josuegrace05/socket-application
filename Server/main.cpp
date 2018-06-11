#include <QApplication>
#include "server.h"

int main(int argc, char *argv[])
{
    QApplication app(argc,argv);

    Server server;//instanciate the server object
    server.show();//show teh server object

    return app.exec();
}
