#ifndef GAMES_ENGINEERING_OPTION_BUTTON_H
#define GAMES_ENGINEERING_OPTION_BUTTON_H

#include "button.h"

class OptionButton : public Button {
private:
    std::vector<std::string> _options;
    unsigned int _currentOption;

public:
    OptionButton() = default;
    OptionButton(const sf::Vector2f& pos, const sf::Vector2f& size, const std::string& text);

    void onClick() override;
    void addOption(const std::string& option);
    void addOptions(const std::vector<std::string>& options);
    const std::string& getSelection() const override;
    void setSelection(const std::string& sel) override;
};


#endif //GAMES_ENGINEERING_OPTION_BUTTON_H
