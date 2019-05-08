//
// Created by Glenn R. Martin on 2019-05-08.
//

#ifndef CVDICE_RESOURCEREADER_H
#define CVDICE_RESOURCEREADER_H

#include <map>
#include <vector>
#include <string>

typedef std::vector<unsigned char> RawByteVector;

class ResourceReader {
// Singleton
public:
    static ResourceReader& getInstance() {
        static ResourceReader instance;
        return instance;
    }

    ResourceReader(ResourceReader const&) = delete;
    void operator=(ResourceReader const&) = delete;

private:
    ResourceReader() {
        cache = std::map<std::string, RawByteVector>{};
    }

// Implementation
private:
    std::map<std::string, RawByteVector> cache;

public:
    RawByteVector getBytes(const std::string& resourceFileName);
    RawByteVector getJpegMarkedBytes(const std::string& resourceFileName, const RawByteVector& bytes);

};


#endif //CVDICE_RESOURCEREADER_H
