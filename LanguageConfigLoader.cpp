#include "LanguageConfigLoader.h"
#include <QDebug>

LanguageConfigLoader::LanguageConfigLoader(QComboBox *languageSelector, QObject *parent) : QObject(parent), languageSelector(languageSelector) {
    connect(languageSelector, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &LanguageConfigLoader::onLanguageChanged);
}

void LanguageConfigLoader::onLanguageChanged(int index) {
    QString selectedLanguage = languageSelector->itemText(index);
    emit languageChanged(selectedLanguage);
}
