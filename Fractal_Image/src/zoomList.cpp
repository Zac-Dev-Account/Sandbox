#include "zoomList.h"

namespace bitTest{
    ZoomList::ZoomList(int width, int height): m_width(width), m_height(height) {

    }

    ZoomList::~ZoomList() {}

    void ZoomList::add(const Zoom& zoom) {
            this->zooms.push_back(zoom);
            //distance of the x coordinate from the centrepoint of the screen
            //in fractal coordinates
            this->m_xCenter += (zoom.x - this->m_width/2) * this->m_scale;
            this->m_yCenter += (zoom.y - this->m_height/2) * this->m_scale;
            m_scale *= zoom.scale;
            
    }

    std::pair<double, double> ZoomList::doZoom(int x, int y) {
        double xFractal = (x - this->m_width/2)*this->m_scale + m_xCenter;
        double yFractal = (y - this->m_height/2)*this->m_scale + m_xCenter;
        return std::pair<double, double>(xFractal, yFractal);
    }
}