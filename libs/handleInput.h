#ifndef HANDLEINPUT_H
#define HANDLEINPUT_H

#include "../model/window.h"
#include "../model/model.h"
#include "../libs/validator.h"

void handleInput(int *ch, InputParams *params, InputType fieldType, int maxLen, mutationFunc createFunc, InputField fields[], fetcherFunc dataFetcher, windowModel *windowM);

#endif