//
// Created by danseremet on 2020-04-04.
//

#ifndef OPENWORLD_WINDOWEXCEPTION_H
#define OPENWORLD_WINDOWEXCEPTION_H

#include <iostream>

class WindowException : public std::exception {
public:
    [[nodiscard]] const char *what() const noexcept override;
};



#endif //OPENWORLD_WINDOWEXCEPTION_H
