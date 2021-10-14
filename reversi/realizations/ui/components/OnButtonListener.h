#include "includeAll.h"
class Button;
class OnButtonListener {
public:
    virtual void onClickListener(Button* view, int x, int y) = 0;
};

