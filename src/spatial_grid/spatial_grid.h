#pragma once

#include <stddef.h>

typedef enum EntryType {
    ENTRY_TYPE_PLAYER,
    ENTRY_TYPE_ENEMY
} EntryType;

typedef struct GridEntry {
    void* entity;
    EntryType type;
} GridEntry;

typedef struct Bucket {
    int hash;
    GridEntry* entries;
    size_t entryCount;
    size_t entryCapacity;
} Bucket;

typedef struct SpatialGrid {
    Bucket* buckets;
    size_t bucketCount;
    size_t bucketCapacity;
} SpatialGrid;

SpatialGrid* LoadSpatialGrid();
void UnloadSpatialGrid(SpatialGrid* spatialGrid);
