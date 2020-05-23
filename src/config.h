#ifndef GAMES_ENGINEERING_CONFIG_H
#define GAMES_ENGINEERING_CONFIG_H

#include <memory>
#include <string>
#include <vector>

class Config
{
private:
	const static std::string DEFAULT_SETTINGS_DIR;
	const static std::string DEFAULT_LANG_DIR;
	const static std::string DEFAULT_LANGUAGE;
	const static std::string SETTINGS_FILE;
	const static std::string SCORE_FILE;
	const static std::string DEFAULT_FONT;
	static std::string _currentLanguage;

	static int _score;
	static int _time;

public:
	static bool firstRun();

	static const std::string& getDefaultFont();

	static const std::string& getDefaultSettingsDir();

	static const std::string& getDefaultLang();

	static const std::string& getSettingsFile();

	static const std::string& getCurrentLanguage();

	static const std::string getLocalisedString(const std::string& setting);

	static const std::string getSetting(const std::string& setting);

	static void setSetting(const std::string& key, const std::string& value);

	static void setCurrentLanguage(const std::string& lang);

	static std::vector<std::string> getScore(const std::string& key);

	static bool updateHighScore();

	static int get_score();

	static void set_score(int score);

	static int get_time();

	static void set_time(int time);
};

#endif //GAMES_ENGINEERING_CONFIG_H
