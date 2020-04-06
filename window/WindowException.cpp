//
// Created by danseremet on 2020-04-04.
//

#include "WindowException.h"

const char *WindowException::what() const noexcept {
    return "There was a problem during window creation.";
}