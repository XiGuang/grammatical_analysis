//
// Created by xiguang on 2023/4/16.
//

#ifndef GRAMMATICAL_ANALYSIS_ERROR_H
#define GRAMMATICAL_ANALYSIS_ERROR_H

#include <string>

class Error {
private:
    Error() = default;

    Error(const Error &) = delete;

    Error &operator=(const Error &) = delete;

    Error(Error &&) = delete;

    Error &operator=(Error &&) = delete;

    ~Error() = default;

    bool hasError = false;

public:
    static Error &getInstance() {
        static Error instance;
        return instance;
    }

    void error(const std::string &message);

    bool hasErrorOccurred() const;
};


#endif //GRAMMATICAL_ANALYSIS_ERROR_H
