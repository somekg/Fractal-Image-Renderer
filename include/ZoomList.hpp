/**
 * @file ZoomList.h
 * @brief Manages a collection of zoom coordinates and transforms pixel spaces 
 * to fractal spaces.
 * @author Alex
 */

#pragma once

#include <utility>
#include <vector>

#include "Zoom.hpp"

using namespace std;

/**
 * @brief Manages zoom history, scales, and coordinate transformations for the 
 * fractal renderer.
 */
class ZoomList {

private:

    double m_xCenter{ 0 };      
    double m_yCenter{ 0 };      
    double m_scale{ 1.0 };      

    int m_width{ 0 };          
    int m_height{ 0 };          

    vector<Zoom> zooms;         

public:

    /**
     * @brief Construct a new ZoomList object.
     * @param width The width of the target image.
     * @param height The height of the target image.
     */
    ZoomList(int width, int height);

    /**
     * @brief Add a zoom instruction, updating the center offset and scaling 
     * factor.
     * @param zoom The Zoom configuration to add.
     */
    void add(const Zoom& zoom);

    /**
     * @brief Transform screen pixel coordinates into corresponding fractal 
     * coordinates.
     * @param x The pixel x-coordinate.
     * @param y The pixel y-coordinate.
     * @return pair<double, double> The calculated fractal coordinates (x, y).
     */
    pair<double,double> doZoom(double x, double y);
};