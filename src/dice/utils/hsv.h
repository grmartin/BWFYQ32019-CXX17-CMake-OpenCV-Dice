//
// Created by Glenn R. Martin on 2019-06-13.
//

#ifndef CVDICE_HSV_H
#define CVDICE_HSV_H

#include <cstdint>
#include <cmath>

namespace cvdice::hsv {
    typedef int integralDegree;
    typedef int integralPercent;

    struct RGBColor {
        unsigned int r;
        unsigned int g;
        unsigned int b;
    };

    inline struct RGBColor hsvToRgb(integralDegree hueDeg, integralPercent satPct, integralPercent valPct) {
        auto toDeg = [](auto x) {return (x >= 360) ? x = 359 : x;};
        auto toPct1 = [](auto x) {return ((x > 100) ? x = 100 : x) / 100.0; };
        auto between = [](double x, double l, double h) { return (x >= l && x < h); };

        hueDeg = toDeg(hueDeg);

        auto satPctF = toPct1(satPct);
        auto valPctF = toPct1(valPct);

        double h6 = hueDeg / 60.0;

        auto C = valPctF * satPctF;
        auto X = C * (1.0 - fabs(((fmod(h6, 2)) - 1.0f)));

        double r = 0;
        double g = 0;
        double b = 0;
        if (between(h6, 0, 1)) {
            r = C;
            g = X;
        } else if (between(h6, 1, 2)) {
            r = X;
            g = C;
        } else if (between(h6, 2, 3)) {
            g = C;
            b = X;
        } else if (between(h6, 3, 4)) {
            g = X;
            b = C;
        } else if (between(h6, 4, 5)) {
            r = X;
            b = C;
        } else {
            r = C;
            b = X;
        }

        auto m255 = [valPctF, C](long double x) {
            return round((x + (valPctF - C)) * 255.0);
        };

        struct RGBColor rgb{};
        rgb.r = (int)m255(r);
        rgb.g = (int)m255(g);
        rgb.b = (int)m255(b);
        return rgb;
    }
}
#endif //CVDICE_HSV_H
