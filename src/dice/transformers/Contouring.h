//
// Created by Glenn R. Martin on 2019-05-10.
//

#ifndef CVDICE_CONTOURING_H
#define CVDICE_CONTOURING_H

#include "bases/Xformer.h"

//enum RetrievalModes {
//    /** retrieves only the extreme outer contours. It sets `hierarchy[i][2]=hierarchy[i][3]=-1` for
//    all the contours. */
//        RETR_EXTERNAL  = 0,
//    /** retrieves all of the contours without establishing any hierarchical relationships. */
//        RETR_LIST      = 1,
//    /** retrieves all of the contours and organizes them into a two-level hierarchy. At the top
//    level, there are external boundaries of the components. At the second level, there are
//    boundaries of the holes. If there is another contour inside a hole of a connected component, it
//    is still put at the top level. */
//        RETR_CCOMP     = 2,
//    /** retrieves all of the contours and reconstructs a full hierarchy of nested contours.*/
//        RETR_TREE      = 3,
//    RETR_FLOODFILL = 4 //!<
//};
//
////! the contour approximation algorithm
//enum ContourApproximationModes {
//    /** stores absolutely all the contour points. That is, any 2 subsequent points (x1,y1) and
//    (x2,y2) of the contour will be either horizontal, vertical or diagonal neighbors, that is,
//    max(abs(x1-x2),abs(y2-y1))==1. */
//        CHAIN_APPROX_NONE      = 1,
//    /** compresses horizontal, vertical, and diagonal segments and leaves only their end points.
//    For example, an up-right rectangular contour is encoded with 4 points. */
//        CHAIN_APPROX_SIMPLE    = 2,
//    /** applies one of the flavors of the Teh-Chin chain approximation algorithm @cite TehChin89 */
//        CHAIN_APPROX_TC89_L1   = 3,
//    /** applies one of the flavors of the Teh-Chin chain approximation algorithm @cite TehChin89 */
//        CHAIN_APPROX_TC89_KCOS = 4
//};


namespace cvdice::transformers {
    namespace types::contours {
        struct Contour {
            int index;
            std::vector<cv::Point> points;
            cv::Point center;
            cv::Moments moments;
            struct hierarchy {
                int depth;
                int next;
                int previous;
                int firstChild;
                int parent;
            } hierarchy;
        };

        typedef std::vector<Contour> Contours;

        struct DataListenerEvent {
            int depth;
            types::contours::Contours contours;
            cv::Mat* sourceImage;
        };
    };

    class Contouring : public Xformer {
        int retr = 0;
        int approx = 0;
        const int max_retr = 4;
        const int max_approx = 3; // x = (y+1)

    public:
        explicit Contouring(int retr = 0, int approx = 0) : Xformer() {
            this->retr = retr;
            this->approx = approx;
        }

        void performUpdate() override;

        std::function<std::any(types::contours::DataListenerEvent)> receivedDataListener;

        void setRetr(int retrVal) {
            retr = retrVal;
            this->update();
        }

        void setApprox(int approxVal) {
            approx = approxVal;
            this->update();
        }

        int getRetr() const {
            return retr;
        }

        int getApprox() const {
            return approx;
        }

        int getMaxRetr() const {
            return max_retr;
        }

        int getMaxApprox() const {
            return max_approx;
        }
    };
};

#endif //CVDICE_CONTOURING_H
