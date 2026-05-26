#include "spatial_grid/spatial_grid.h"

static int HashCell(int x, int y, int bucketCount) {
    unsigned int h = (unsigned int)(x * 73856093) ^ (unsigned int)(y * 19349663);
    return h % bucketCount;
}