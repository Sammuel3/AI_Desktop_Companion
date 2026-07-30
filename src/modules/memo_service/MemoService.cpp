#include "MemoService.h"

bool MemoService::begin() {
    initialized_ = true;
    return true;
}

void MemoService::update() {
}

void MemoService::setMemo(const String& memo) {
    memo_ = memo;
    memoValid_ = (memo.length() > 0);
}

bool MemoService::isInitialized() const {
    return initialized_;
}

bool MemoService::isMemoValid() const {
    return memoValid_;
}

String MemoService::getMemo() const {
    if (!memoValid_) {
        return "";
    }
    return memo_;
}
