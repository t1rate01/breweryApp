#include "brewerydata.h"

breweryData::breweryData()
{
    networkmanager = new QNetworkAccessManager(this);
    connect(networkmanager, SIGNAL(finished (QNetworkReply*)), this, SLOT(getDataSlot(QNetworkReply*)));
}

void breweryData::updateBreweries()
{
    QString apiUrl="https://api.openbrewerydb.org/v1/breweries?by_state=georgia"; // make the api call by id's, assuming its the only way to find first entry
    QNetworkRequest request((apiUrl));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    reply = networkmanager->get(request);
}

QString breweryData::getNorthern()
{
    return northName;
}

QString breweryData::getNorthPopupText()
{
    QString returnString;
    returnString += getNorthern() + "\n";
    if (!northernBrewery.value("website_url").isNull()){
        returnString += "Website: " + northernBrewery.value("website_url").toString() + "\n";
    } else {
        returnString += "No website available \n";
    }
    if (!northernBrewery.value("city").isNull()){
        returnString += "City: " + northernBrewery.value("city").toString();
    } else {
        returnString += "No city available";
    }
    qDebug()<<"Website " + northernBrewery.value("website_url").toString();

    return returnString;
}

QString breweryData::getSouthers()
{
    return southName;
}

QString breweryData::getSouthernPopupText()
{
    QString returnString;
    returnString += getSouthers() + "\n";
    if (!southernBrewery.value("website_url").isNull()){
        returnString += "Website: " + southernBrewery.value("website_url").toString() +"\n";
    } else {
        returnString += "No website available \n";
    }

    if (!southernBrewery.value("city").isNull())
    {
        returnString += "City: " + southernBrewery.value("city").toString();
    } else {
        returnString += "No city available";
    }

    return returnString;
}


QString breweryData::getFirstBrew()
{
    return firstName;
}

QString breweryData::getFirstPopupText()
{
    QString returnString;
    returnString += getFirstBrew() + "\n";
    if(!firstBrewery.value("website_url").isNull()){
        returnString += "Website: " + firstBrewery.value("website_url").toString() + "\n";
    } else {
        returnString += "No website available \n";
    }
    if(!firstBrewery.value("city").isNull()){
        returnString += "City: " + firstBrewery.value("city").toString();
    } else {
        returnString += "No city available";
    }

    return returnString;
}

void breweryData::handleData(QJsonDocument document)
{
        // no check if document is array/object since we know whats coming from the api, assuming the api is running
        QJsonArray jsonArray = document.array();
        QJsonObject northernMostObj;
        QJsonObject southernMostObj;
        double northernMostLat= -90; // initialize with a southern point
        double southernMostLat= 90; // same but opposite

        for(QJsonArray::iterator i = jsonArray.begin(); i != jsonArray.end(); i++)
        {
            QJsonObject jsonObj = i->toObject(); // take current
            if(i == jsonArray.begin()) // Grab the first entry
            {
                firstBrewery = jsonObj;
                updateFirst(jsonObj.value("name").toString());
              //  qDebug()<<"First brew added";
            }

            if(!jsonObj.value("latitude").isNull()) // ignore NULL values, since there were data with NULL latitude values
            {
                double currentLat=jsonObj.value("latitude").toString().toDouble();

                if (currentLat > northernMostLat ){
                    northernMostLat = currentLat;
                    northernMostObj = jsonObj;
            }
                if (currentLat < southernMostLat){
                    southernMostLat = currentLat;
                    southernMostObj = jsonObj;
                }}}
    northernBrewery = northernMostObj;
    updateNorth(northernBrewery.value("name").toString());
    southernBrewery = southernMostObj;
    updateSouth(southernBrewery.value("name").toString());
   // qDebug()<<"Northernmost brewery is " << northernBrewery.value("name").toString();
   // qDebug()<<"Southernmost brewery is " << southernBrewery.value("name").toString();
   // qDebug()<<"First added brewery is " << firstBrewery.value("name").toString();

}

void breweryData::updateNorth(QString newstring)
{
    if(newstring != northName)
    {
        northName = newstring;
        emit northNameChanged();
    }
}

void breweryData::updateSouth(QString newstring)
{
    if(newstring != southName)
    {
        southName = newstring;
        emit southNameChanged();
    }

}

void breweryData::updateFirst(QString newstring)
{
    if(newstring != firstName)
    {
        firstName = newstring;
        emit firstNameChanged();
    }
}


void breweryData::getDataSlot(QNetworkReply *reply)
{
    responsedata = reply->readAll();
    //qDebug()<<"DATA : "+responsedata;
    QJsonDocument json_doc = QJsonDocument::fromJson(responsedata);
    handleData(json_doc);
    reply->deleteLater();
}
