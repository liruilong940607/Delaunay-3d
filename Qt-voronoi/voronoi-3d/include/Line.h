/**
 * Line class
 *
 * @author Ruilong Li
 */
#ifndef _LINE_H
#define _LINE_H

#include "Vector3.h"
class Line {
public:
    Vector3 start, end;
    Line(Vector3 start, Vector3 end) {
        this->start = start;
        this->end = end;
    }

    void reverse() {
        Vector3 tmp = this->start;
        this->start = this->end;
        this->end = tmp;
    }

    bool equals(Line l) {
        if ((this->start == l.start && this->end == l.end)
                || (this->start == l.end && this->end == l.start))
            return true;
        return false;
    }
};
#endif