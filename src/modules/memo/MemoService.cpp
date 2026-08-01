#include "MemoService.h"
#include "../logger/Logger.h"

bool MemoService::begin(StorageService* storage) {
    if (storage == nullptr) {
        Logger::error("MemoService: StorageService is null");
        return false;
    }
    storage_ = storage;
    initialized_ = true;
    Logger::info("MemoService initialized");
    return true;
}

void MemoService::update() {
}

bool MemoService::addMemo(const String& title, const String& content) {
    if (!initialized_) return false;

    int count = getMemoCount();
    if (count >= MAX_MEMOS) {
        Logger::warn("MemoService: max memos reached");
        return false;
    }

    Memo memo;
    memo.title = title;
    memo.content = content;
    memo.timestamp = millis();

    saveMemo(count, memo);
    count++;
    saveCount();

    Logger::info(String("MemoService: added memo #") + String(count - 1));
    return true;
}

bool MemoService::removeMemo(int index) {
    if (!initialized_) return false;

    int count = getMemoCount();
    if (index < 0 || index >= count) return false;

    // Clear the given slot
    storage_->setString("memo_" + String(index) + "_title", "");
    storage_->setString("memo_" + String(index) + "_content", "");
    storage_->setString("memo_" + String(index) + "_timestamp", "0");

    // Compact remaining
    compact();
    count--;
    saveCount();

    Logger::info(String("MemoService: removed memo #") + String(index));
    return true;
}

bool MemoService::updateMemo(int index, const String& title, const String& content) {
    if (!initialized_) return false;

    int count = getMemoCount();
    if (index < 0 || index >= count) return false;

    Memo memo;
    memo.title = title;
    memo.content = content;
    memo.timestamp = millis();

    saveMemo(index, memo);
    return true;
}

int MemoService::getMemoCount() const {
    if (!initialized_) return 0;
    String val = storage_->getString("memo_count", "0");
    return val.toInt();
}

String MemoService::getMemoTitle(int index) const {
    if (!initialized_) return "";
    Memo m = loadMemo(index);
    return m.title;
}

String MemoService::getMemoContent(int index) const {
    if (!initialized_) return "";
    Memo m = loadMemo(index);
    return m.content;
}

bool MemoService::isInitialized() const {
    return initialized_;
}

void MemoService::saveCount() {
    storage_->setString("memo_count", String(getMemoCount()));
}

void MemoService::saveMemo(int index, const Memo& memo) {
    String prefix = "memo_" + String(index) + "_";
    storage_->setString(prefix + "title", memo.title);
    storage_->setString(prefix + "content", memo.content);
    storage_->setString(prefix + "timestamp", String(memo.timestamp));
}

Memo MemoService::loadMemo(int index) const {
    Memo m;
    String prefix = "memo_" + String(index) + "_";
    m.title = storage_->getString(prefix + "title", "");
    m.content = storage_->getString(prefix + "content", "");
    String ts = storage_->getString(prefix + "timestamp", "0");
    m.timestamp = static_cast<uint32_t>(ts.toInt());
    return m;
}

void MemoService::compact() {
    int countBefore = getMemoCount();
    int writeIdx = 0;
    for (int readIdx = 0; readIdx < countBefore; readIdx++) {
        String title = storage_->getString("memo_" + String(readIdx) + "_title", "");
        if (title.length() > 0) {
            if (writeIdx != readIdx) {
                Memo m = loadMemo(readIdx);
                saveMemo(writeIdx, m);
            }
            writeIdx++;
        }
    }
    // Clear trailing slots
    for (int i = writeIdx; i < countBefore; i++) {
        String prefix = "memo_" + String(i) + "_";
        storage_->setString(prefix + "title", "");
        storage_->setString(prefix + "content", "");
        storage_->setString(prefix + "timestamp", "0");
    }
}
