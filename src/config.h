#ifndef GAMES_ENGINEERING_CONFIG_H
#define GAMES_ENGINEERING_CONFIG_H

#include <string>
#include <vector>
#include <memory>

class Config {
private:
    const static std::string DEFAULT_SETTINGS_DIR;
    const static std::string DEFAULT_LANG_DIR;
    const static std::string DEFAULT_LANGUAGE;
    const static std::string SETTINGS_FILE;
    const static std::string DEFAULT_FONT;
    static std::string _currentLanguage;

public:
    static bool firstRun();

    static const std::string &getDefaultFont();

    static const std::string &getDefaultSettingsDir();

    static const std::string &getDefaultLang();

    static const std::string &getSettingsFile();

    static const std::string &getCurrentLanguage();

    static const std::string getLocalisedString(const std::string &setting);

    static const std::string getSetting(const std::string &setting);

    static void setSetting(const std::string& key, const std::string& value);

    static void setCurrentLanguage(const std::string &lang);
};


#endif //GAMES_ENGINEERING_CONFIG_H
