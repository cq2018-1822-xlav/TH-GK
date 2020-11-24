#pragma once

#ifndef CV_INCLUDE_H
#define CV_INCLUDE_H

#define _USE_MATH_DEFINES

// CV Include
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

// CV Core
#include <opencv2/core/core_c.h>

// STL Include
#include <math.h>
#include <functional>
#include <string>

// Converter
#include "Converter.h"

// Developer define constant
// 0.2989 R + 0.5870 G + 0.1141 B
#define ALPHA_1 0.2989
#define ALPHA_2 0.5870
#define ALPHA_3 0.1141

// 0.2125 R + 0.7154 G + 0.0721 B
#define _ALPHA_1 0.2125
#define _ALPHA_2 0.7154
#define _ALPHA_3 0.0721

// 0.2126 R + 0.7152 G + 0.0722 B 
#define _ALPHA_1_ 0.2126
#define _ALPHA_2_ 0.7152
#define _ALPHA_3_ 0.0722


#endif // CV_INCLUDE_H