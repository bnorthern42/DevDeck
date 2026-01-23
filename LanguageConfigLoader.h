#ifndef LANGUAGECONFIGLOADER_H
#define LANGUAGECONFIGLOADER_H

#include <QObject>
#include <QComboBox>

class LanguageConfigLoader : public QObject {
    Q_OBJECT

public:
    explicit LanguageConfigLoader(QComboBox *languageSelector, QObject *parent = nullptr);

signals:
    void languageChanged(const QString &language);

private slots:
    void onLanguageChanged(int index);

private:
    QComboBox *languageSelector;
};

#endif // LANGUAGECONFIGLOADER_H
