#ifndef CUSTOMTABLEWIDGETITEM_H
#define CUSTOMTABLEWIDGETITEM_H

#include <QObject>
#include <QTableWidgetItem>
#include <QDebug>

class CustomTableWidgetItem : public QTableWidgetItem
{

public:

    bool operator< (const QTableWidgetItem &other) const
    {

        quint64 ulnCurrent=0;
        QString strCurrent=this->text();

        if(strCurrent.contains("KB"))// 1 KB
        {
            strCurrent.remove((strCurrent.length()-2),2);
            strCurrent.replace(" ","");
            ulnCurrent=strCurrent.toUInt()*1024;

        }else if(strCurrent.contains("MB"))
        {
            strCurrent.remove((strCurrent.length()-2),2);
            strCurrent.replace(" ","");
            ulnCurrent=strCurrent.toUInt()*1024*1024;

        }else if(strCurrent.contains("GB"))
        {
            strCurrent.remove((strCurrent.length()-2),2);
            strCurrent.replace(" ","");
            ulnCurrent=strCurrent.toUInt()*1024*1024*1024;
        }

        quint64 ulnOther=0;
        QString strOther=other.text();

        if(strOther.contains("KB"))
        {
            strOther.remove((strOther.length()-2),2);
            strOther.replace(" ","");
            ulnOther=strOther.toUInt()*1024;
        }else if(strOther.contains("MB"))
        {
            strOther.remove((strOther.length()-2),2);
            strOther.replace(" ","");
            ulnOther=strOther.toUInt()*1024*1024;
        }else if(strOther.contains("GB"))
        {
            strOther.remove((strOther.length()-2),2);
            strOther.replace(" ","");
            ulnOther=strOther.toUInt()*1024*1024*1024;
        }


//        qDebug() << ulnOther << strOther << "  " << ulnCurrent << strCurrent;


        return (ulnCurrent < ulnOther);/*11<10*/
    }
};


#endif // CUSTOMTABLEWIDGETITEM_H
