//
// Created by Glenn R. Martin on 2019-05-09.
//


#import <opencv2/core/mat.hpp>
#import "./QT5Xformer.h"

#ifndef CVDICE_XFORMERBASE_H
#define CVDICE_XFORMERBASE_H

#ifdef CVD_USE_QT5
#   define XformerBase cvdice::transformers::QT5Xformer
#else
#   define XformerBase cvdice::transformers::Xformer
#endif

#define CHAIN_XFORMER(first, second) first->chainTo = [&second](cv::Mat mat) { second->chainAction(mat); }

#endif //CVDICE_XFORMERBASE_H
