#include "config.h"
#include "Log.h"
#include <SFML/Window/Keyboard.hpp>
#include <settings_parser.h>

/*
 * Wrapper class for storing and retrieving settings and strings and some global variables are stored here instead of using externs.
 */

const std::string Config::DEFAULT_SETTINGS_DIR = "";
const std::string Config::DEFAULT_LANG_DIR = "res/lang/";
const std::string Config::DEFAULT_LANGUAGE = "en.txt";
const std::string Config::SETTINGS_FILE = "settings.txt";
const std::string Config::SCORE_FILE = "score.txt";
const std::string Config::DEFAULT_FONT = "AMERIKA.ttf";
std::string Config::_currentLanguage = DEFAULT_LANGUAGE;

int Config::_score = 0;
int Config::_time = 0;

const std::string& Config::getDefaultSettingsDir() { return DEFAULT_SETTINGS_DIR; }

const std::string& Config::getDefaultLang() { return DEFAULT_LANGUAGE; }

const std::string& Config::getSettingsFile() { return SETTINGS_FILE; }

const std::string& Config::getCurrentLanguage() { return _currentLanguage; }

//returning a copy rather than a reference because returning reference to a temporary string is not good!
const std::string Config::getLocalisedString(const std::string& setting)
{
	SettingsParser setPar;
	setPar.readFile(DEFAULT_LANG_DIR + _currentLanguage);
	auto result = setPar.get(setting);
	return result;
}

const std::string Config::getSetting(const std::string& setting)
{
	SettingsParser setPar;
	setPar.readFile(DEFAULT_SETTINGS_DIR + SETTINGS_FILE);
	auto result = setPar.get(setting);
	return result;
}

void Config::setSetting(const std::string& key, const std::string& value)
{
	SettingsParser setPar;
	setPar.readFile(DEFAULT_SETTINGS_DIR + SETTINGS_FILE);
	setPar.set(key, value);
}

void Config::setCurrentLanguage(const std::string& lang)
{
	_currentLanguage = lang;
	SettingsParser sp;
	sp.readFile(DEFAULT_SETTINGS_DIR + SETTINGS_FILE);
	sp.set("language", lang);
}

const std::string& Config::getDefaultFont() { return DEFAULT_FONT; }

//create the settings file if this is the first time the game is run!!!
bool Config::firstRun()
{
	SettingsParser sp;
	sp.readFile(DEFAULT_SETTINGS_DIR + SETTINGS_FILE);
	if(sp.get("width").empty())
	{
		sp.put("width", "1280");
		sp.put("height", "720");
		sp.put("fullscreen", "0");
		sp.put("language", "en.txt");
		sp.put("walkLeft", std::to_string(sf::Keyboard::A));
		sp.put("walkRight", std::to_string(sf::Keyboard::D));
		sp.put("jump", std::to_string(sf::Keyboard::W));
		sp.put("shoot", std::to_string(sf::Keyboard::Space));
		sp.put("sound", "1");
		sp.saveToFile(false);
	}

	SettingsParser score;
	score.readFile(DEFAULT_SETTINGS_DIR + SCORE_FILE);
	if(score.get("score1").empty())
	{
		score.put("score1", "0");
		score.put("score2", "0");
		score.put("score3", "0");
		sp.saveToFile(false);
		return true;
	}

	return false;
}

bool Config::updateHighScore()
{
	SettingsParser sp;
	sp.readFile(DEFAULT_SETTINGS_DIR + SCORE_FILE);

	auto s1 = stoi(sp.get("score1"));
	auto s2 = stoi(sp.get("score2"));
	auto s3 = stoi(sp.get("score3"));

	if(_score > s1)
	{
		sp.set("score1", std::to_string(_score));
		return true;
	}
	if(_score > s2)
	{
		sp.set("score2", std::to_string(_score));
		return true;
	}
	if(_score > s3)
	{
		sp.set("score3", std::to_string(_score));
		return true;
	}

	return false;
}

std::vector<std::string> Config::getScore(const std::string& key)
{
	SettingsParser sp;
	sp.readFile(DEFAULT_SETTINGS_DIR + SCORE_FILE);
	return sp.getAll();
}

//replacing the externs
int Config::get_score() { return _score; }

void Config::set_score(int score) { _score = score; }

int Config::get_time() { return _time; }

void Config::set_time(int time) { _time = time; }
