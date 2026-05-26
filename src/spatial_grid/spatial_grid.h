#pragma once

#include <stdlib.h>

typedef enum EntityType {
    ENTITY_TYPE_PLAYER,
    ENTITY_TYPE_ENEMY,
} EntityType;

typedef struct {
    int x;
    int y;
} CellKey;

typedef struct GridEntity {
    void* data;
    EntityType type;
} GridEntity;

typedef struct SpatialCell {
    GridEntity* entities;
    int count;
    int capacity;
    CellKey key;

    struct SpatialCell* next;
} SpatialCell;

typedef struct {
    SpatialCell** buckets;
    int bucketCount;
    float cellSize;
} SpatialGrid;

typedef void (*SpatialGridQueryCallback)(const GridEntity* entity, void* userData);

SpatialGrid* InitSpatialGrid(int bucketCount, float cellSize);
void UnloadSpatialGrid(SpatialGrid* spatialGrid);

void SpatialGridAddEntity(SpatialGrid* spatialGrid, CellKey key, GridEntity entity);
void SpatialGridQuery3x3(
    SpatialGrid* spatialGrid,
    CellKey centerKey,
    SpatialGridQueryCallback callback,
    void* userData
);

void UpdateSpatialGrid(SpatialGrid* spatialGrid);
void DrawSpatialGrid(SpatialGrid* spatialGrid);