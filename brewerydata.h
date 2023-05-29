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
    Q_PROPERTY(QString northpopuptext READ getNorthPopupText NOTIFY northNameChanged) // these are macros to make sure the qml updates when theyre updated
    Q_PROPERTY(QString firstpopuptext READ getFirstPopupText NOTIFY firstNameChanged) // using the same signals here, didnt see a need for a new signal here
public:
    breweryData();  // Constructor creates the QNetworkaccessmanager and connects the signal.
                    // Was thinking if it should be created in the function and deleted as well,
                    // but thought of possible refresh button or other refreshing functions in the future so kept it alive

    void updateBreweries();     // makes the api call with a get request, uses an url that limits results by state
    QString getNorthern();      // returns the name string from the object
    QString getNorthPopupText();   // creates a string with some chosen example values to display in the popup

    QString getSouthers();  // same as above
    QString getSouthernPopupText(); // same as above

    QString getFirstBrew(); // same as above
    QString getFirstPopupText(); // same as above

signals:
    void southNameChanged();   // signals for the Q_PROPERTY macro to alert QML of a change
    void northNameChanged();
    void firstNameChanged();

private:
    QJsonObject northernBrewery;    // objects to store the brewery data
    QJsonObject southernBrewery;
    QJsonObject firstBrewery;
    QString northName="Receiving data...", southName="Receiving data...", firstName="Receiving data...";  // initialized strings if api call is slow
    void handleData(QJsonDocument); // Called by the getDataSlot, makes an array of the document, goes through the array using iterator
                                    // grabs the first to be the firstBrewery and then looks for the northernmost and southernmost latitude value in data
                                    // stores the objects and strings of said breweries

    void updateNorth(QString);      // update functions with possible refresh functionality in mind, sends the xxxxxChanged signal
    void updateSouth(QString);
    void updateFirst(QString);

    // api call related
    QByteArray responsedata; // for receiving the data in the getDataSlot
    QNetworkAccessManager * networkmanager; // created by constructor
    QNetworkReply * reply;  // passed from updateBreweries to getDataSlot and deleteLater by getDataSlot.



private slots:
    void getDataSlot(QNetworkReply *reply);  // receives api call data, stores it to QByteArray, creates a QJsonDocument and calls handledata with the document.
};

#endif // BREWERYDATA_H
