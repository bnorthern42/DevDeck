#ifndef TEMPLATES_HPP
#define TEMPLATES_HPP

#include <QString>
#include <QJsonDocument>
#include <QFile>
#include <qjsondocument.h>
#include <qlogging.h>
#include <QJsonObject>
#include <QIODevice>
//load in json templates
class LangTemplate
{   
    public:

    QString name;
    QString icon;
    QString file_extension;
    QString default_code;
    QString build_command;
    QString run_command;
    QString comment_syntax;
    int exec_timeout_secs;
LangTemplate() = default;
LangTemplate(const QString& LangCodeName)
{
    //load template into memory/
    QString filename = LangCodeName + ".json";
    QFile jsonFile( filename);
    jsonFile.open(QIODevice::ReadOnly | QIODevice::Text);
    auto jsonDoc =QJsonDocument().fromJson(jsonFile.readAll());
    QJsonObject jsonObj = jsonDoc.object();
    
    this->name              = jsonObj["name"].toString();
    this->icon              = jsonObj["icon"].toString();
    this->file_extension    = jsonObj["file_extension"].toString();
    this->default_code      = jsonObj["default_code"].toString();
    this->build_command     = jsonObj["build_command"].toString();
    this->run_command       = jsonObj["run_command"].toString();
    this->comment_syntax    = jsonObj["comment_syntax"].toString();
    this->exec_timeout_secs = jsonObj["exec_timeout_secs"].toInt();


}

~LangTemplate()
{

}
 QString getName()
{
    return name;
}
 QString getIcon()
{
    return icon;
}
 QString getFileExt()
{
    return file_extension;
}
 QString getDefaultCode()
{
    return default_code;
}
 QString getBuildCMD()
{
    return build_command;
}
 QString getRunCMD()
{
    return run_command;
}
 QString getCommentStax()
{
    return comment_syntax;
}
 int getTimeout()
{
    return exec_timeout_secs;
}
void PrintAll()
{
    qDebug() << "JSON DATA: " << name ; 
}
}; 

#endif TEMPLATES_HPP
