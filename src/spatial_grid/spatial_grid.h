#pragma once

#define MAX_BUCKETS 256

typedef enum EntryType {
    ENTRY_TYPE_PLAYER,
    ENTRY_TYPE_ENEMY
} EntryType;

typedef struct GridEntry {
    void* entity;
    EntryType type;
} GridEntry;

typedef struct SpatialGrid {
    GridEntry buckets[MAX_BUCKETS];
} SpatialGrid;

SpatialGrid* LoadSpatialGrid();
void UnloadSpatialGrid(SpatialGrid* spatialGrid);