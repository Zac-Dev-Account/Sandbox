#ifndef ZOOM_H_
#define ZOOM_H_

namespace bitTest {
    //an obj to be stored inside a ZoomList class with an add method
    struct Zoom {
        //coordinates to zoom to in bitmap coord system
        int x {0};
        int y {0};
        double scale {0.0f};
        Zoom(int x, int y, double scale): x(x), y(y), scale(scale){};
    };
}
#endif