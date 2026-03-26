#ifndef RECTCUT_H_
#define RECTCUT_H_

#include <stdbool.h>

#define RECTCUT_MIN(a, b) (((a) < (b)) ? (a) : (b))
#define RECTCUT_MAX(a, b) (((a) > (b)) ? (a) : (b))

typedef struct Rect {
    float min_x, min_y, max_x, max_y;
} Rect;

extern Rect cut_left(Rect* rect, float a);
extern Rect cut_right(Rect* rect, float a);
extern Rect cut_top(Rect* rect, float a);
extern Rect cut_bottom(Rect* rect, float a);
extern Rect get_left(const Rect* rect, float a);
extern Rect get_right(const Rect* rect, float a);
extern Rect get_top(const Rect* rect, float a);
extern Rect get_bottom(const Rect* rect, float a);
extern Rect add_left(const Rect* rect, float a);
extern Rect add_right(const Rect* rect, float a);
extern Rect add_top(const Rect* rect, float a);
extern Rect add_bottom(const Rect* rect, float a);
extern Rect extend(const Rect* rect, float a);
extern Rect contract(const Rect* rect, float a);
extern bool in_rect(Rect* rect, float x, float y);

#ifdef RECTCUT_IMPLEMENTATION

Rect cut_left(Rect* rect, float a) {
    float min_x = rect->min_x;
    rect->min_x = RECTCUT_MIN(rect->max_x, rect->min_x + a);
    return (Rect){ min_x, rect->min_y, rect->min_x, rect->max_y };
}

Rect cut_right(Rect* rect, float a) {
    float max_x = rect->max_x;
    rect->max_x = RECTCUT_MAX(rect->min_x, rect->max_x - a);
    return (Rect){ rect->max_x, rect->min_y, max_x, rect->max_y };
}

Rect cut_top(Rect* rect, float a) {
    float min_y = rect->min_y;
    rect->min_y = RECTCUT_MIN(rect->max_y, rect->min_y + a);
    return (Rect){ rect->min_x, min_y, rect->max_x, rect->min_y };
}

Rect cut_bottom(Rect* rect, float a) {
    float max_y = rect->max_y;
    rect->max_y = RECTCUT_MAX(rect->min_y, rect->max_y - a);
    return (Rect){ rect->min_x, rect->max_y, rect->max_x, max_y };
}
Rect get_left(const Rect* rect, float a) {
    float max_x = 0;
    if (rect->max_x < rect->min_x + a) {
        max_x = rect->max_x;
    } else {
        max_x = rect->min_x + a;
    }
    return (Rect){ rect->min_x, rect->min_y, max_x, rect->max_y };
}

Rect get_right(const Rect* rect, float a) {
    float min_x = 0;
    if (rect->min_x > rect->max_x - a) {
        min_x = rect->min_x;
    } else {
        min_x = rect->max_x - a;
    }
    return (Rect){ min_x, rect->min_y, rect->max_x, rect->max_y };
}

Rect get_top(const Rect* rect, float a) {
    float max_y = 0;
    if (rect->max_y < rect->min_y + a) {
        max_y = rect->max_y;
    } else {
        max_y = rect->min_y + a;
    }
    return (Rect){ rect->min_x, rect->min_y, rect->max_x, max_y };
}

Rect get_bottom(const Rect* rect, float a) {
    float min_y = 0;
    if (rect->min_y > rect->max_y - a) {
        min_y = rect->min_y;
    } else {
        min_y = rect->max_y - a;
    }
    return (Rect){ rect->min_x, min_y, rect->max_x, rect->max_y };
}

Rect add_left(const Rect* rect, float a) {
    return (Rect){ rect->min_x - a, rect->min_y, rect->max_x, rect->max_y };
}

Rect add_right(const Rect* rect, float a) {
    return (Rect){ rect->min_x, rect->min_y, rect->max_x + a, rect->max_y };
}

Rect add_top(const Rect* rect, float a) {
    return (Rect){ rect->min_x, rect->min_y - a, rect->max_x, rect->max_y };
}

Rect add_bottom(const Rect* rect, float a) {
    return (Rect){ rect->min_x, rect->min_y, rect->max_x, rect->max_y + a};
}

Rect extend(const Rect* rect, float a) {
    return (Rect){ rect->min_x - a, rect->min_y - a, rect->max_x + a, rect->max_y + a};
}

Rect contract(const Rect* rect, float a) {
    return (Rect){ rect->min_x + a, rect->min_y + a, rect->max_x - a, rect->max_y - a};
}

bool in_rect(Rect* rect, float x, float y) {
    return (x > rect->min_x) && (y > rect->min_y) && (x < rect->max_x) && (y < rect->max_y);
}

#endif // RECTCUT_IMPLEMENTATION

#endif // !RECTCUT_H_
