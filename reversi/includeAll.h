#pragma once

#include <iostream>
#include <algorithm>
#include <functional>
#include "map"
#include "iomanip"
#include "vector"
#include "array"
#include "string"
#include "windows.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <d2d1.h>
#include <windowsx.h>
#include <math.h>
#include <memory>
#include <stdexcept>

#include "Chip.h"
#include <game_exceptions.h>
#include "Point.h"
#include "constants.h"
#include "Field.h"
#include "ReversiEngine.h"
#include "GameListener.h"
#include "Player.h"
#include "HumanPlayer.h"
#include "AiPlayer.h"
#include "ConsoleReversi.h"

#include "ui/components/Drawable.h"
#include "ui/components/Clickable.h"
#include "ui/components/Palette.h"
#include "ui/components/Label.h"
#include "ui/components/MultilineLabel.h"
#include "ui/components/Button.h"
#include "ui/components/ChipButton.h"
#include "ui/components/RadioButtonGroup.h"
#include "ui/components/ButtonsFieldListener.h"
#include "ui/components/ButtonsField.h"
#include "ReversiAi.h"
