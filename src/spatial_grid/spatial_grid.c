#include "spatial_grid/spatial_grid.h"
#include "raylib.h"

static int HashCell(int x, int y) {
    unsigned int h = (unsigned int)(x * 73856093) ^ (unsigned int)(y * 19349663);
    return h;
}

SpatialGrid* LoadSpatialGrid() {
    SpatialGrid* grid = MemAlloc(sizeof(SpatialGrid));

    grid->bucketCount = 0;
    grid->bucketCapacity = 4;
    grid->buckets = MemAlloc(sizeof(GridEntry) * grid->bucketCapacity);

    return grid;
}

void RegisterEntity(SpatialGrid* spatialGrid, EntryType type, void* data) {

}

void UnloadSpatialGrid(SpatialGrid* spatialGrid) {
    MemFree(spatialGrid->buckets->entries);
    MemFree(spatialGrid->buckets);
    MemFree(spatialGrid);
}
