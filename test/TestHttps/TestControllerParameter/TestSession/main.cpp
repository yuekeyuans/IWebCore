#include <IWebCore>

#include <web/session/ISessionManager.h>
#include <web/session/ISessionWare.h>

int main(int argc, char *argv[])
{
    IApplication app(argc, argv);

    {
        IWebCore::ISessionWare* session = ISessionManager::instance ()->getSessionWare();

        auto sessionId = session->createSession ();
        qDebug() << sessionId;

        session->setSessionValue (sessionId, "name", "yuekeyua");

        auto value = session->getSessionValue (sessionId, "name").toString ();
        qDebug() << value;
    }

    IHttpServer server;
    server.listen();


    return app.exec ();
}
