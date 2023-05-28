#ifndef BREWERYDATA_H
#define BREWERYDATA_H

#include <QObject>
#include <QJsonDocument>
#include <QNetworkAccessManager>
#include <QtNetwork>
#include <QDebug>


class breweryData : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString southName READ getSouthers NOTIFY southNameChanged)
    Q_PROPERTY(QString northName READ getNorthern NOTIFY northNameChanged)
    Q_PROPERTY(QString firstName READ getFirstBrew NOTIFY firstNameChanged)
    // note so self on q_property (TYPE, the name the QML uses to access it, does not need to match the variable name here,
    // READ, how to access the relevant data here
    //NOTIFY(optional), this is the signal that gets emitted, allows updates to QML
    // also excists: WRITE(optional), function in this class that writes the value, takes a parameter
    Q_PROPERTY(QString southpopuptext READ getSouthernPopupText NOTIFY southNameChanged)
    Q_PROPERTY(QString northpopuptext READ getNorthPopupText NOTIFY northNameChanged)
    Q_PROPERTY(QString firstpopuptext READ getFirstPopupText NOTIFY firstNameChanged)
public:
    breweryData();
    void updateBreweries();
    QString getNorthern();
    QString getNorthPopupText();

    QString getSouthers();
    QString getSouthernPopupText();

    QString getFirstBrew();
    QString getFirstPopupText();

signals:
    void northSignal(QJsonObject);
    void southSignal(QJsonObject);
    void firstSignal(QJsonObject);
    void southNameChanged();
    void northNameChanged();
    void firstNameChanged();

private:
    QJsonObject northernBrewery;
    QJsonObject southernBrewery;
    QJsonObject firstBrewery;
    QString northName="Receiving data...", southName="Receiving data...", firstName="Receiving data...";
    void handleData(QJsonDocument);
    void updateNorth(QString);
    void updateSouth(QString);
    void updateFirst(QString);

    // api call related
    QByteArray responsedata;
    QNetworkAccessManager * networkmanager;
    QNetworkReply * reply;



private slots:
    void getDataSlot(QNetworkReply *reply);
};

#endif // BREWERYDATA_H
