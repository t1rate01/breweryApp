#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "brewerydata.h"


int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    breweryData * brew = new(breweryData); // create breweryData object.
                                            // not deleting it since it runs in main and is basically the app
                                            // and it dies with the app.

    QQmlApplicationEngine engine;

    //  brewerydata to qml
    engine.rootContext()->setContextProperty("brew", brew);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
        &app, [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);
    engine.load(url);


    brew->updateBreweries(); // call the api calling function



    return app.exec();
}
