#ifndef TEMPLATES_HPP
#define TEMPLATES_HPP

#include <QString>
#include <QJsonDocument>


//load in json templates
class LangTemplate:
{   private;
       
    public:

    QString name;
    QString icon;
    QString file_extension;
    QString default_code;
    QString build_command;
    QString run_command;
    QString comment_syntax;
    int exec_timeout_secs;


} 
LangTemplate();

~LangTemplate();


#endif TEMPLATES_HPP
