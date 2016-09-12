#include "IdUtils.h"

unsigned int IdUtils::createKey(unsigned int id1, unsigned int id2) {
    if (id1 < id2) {
        return id1 * 1000 + id2;
    }
    return id2 * 1000 + id1;
}
