#ifndef HANDLEINPUT_H
#define HANDLEINPUT_H

#include "../model/window.h"
#include "../model/model.h"

void handleInput(int *ch, int *destLen, char destText[], InputType fieldType, int maxLen, mutationFunc createFunc, InputField fields[], fetcherAdmin dataFetcher, windowModel *windowM);

#endif