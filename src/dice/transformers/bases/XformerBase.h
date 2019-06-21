//
// Created by Glenn R. Martin on 2019-05-09.
//

#ifndef CVDICE_XFORMERBASE_H
#define CVDICE_XFORMERBASE_H

#import <opencv2/core/mat.hpp>

#ifdef CVD_USE_QT5
#   import "./QT5Xformer.h"
#   define XformerBase cvdice::transformers::QT5Xformer
#else
#   define XformerBase cvdice::transformers::Xformer
#endif

#define CHAIN_XFORMER(first, second) first->chainTo = [&second](cv::Mat mat) { second->chainAction(mat); }

#endif //CVDICE_XFORMERBASE_H
