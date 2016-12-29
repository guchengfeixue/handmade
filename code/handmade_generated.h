member_definition MembersOf_sim_entity_collision_volume[] = 
{
    {0, MetaType_v3, "OffsetP", (memory_index)(&(((sim_entity_collision_volume *)0)->OffsetP))},
    {0, MetaType_v3, "Dim", (memory_index)(&(((sim_entity_collision_volume *)0)->Dim))},
};
member_definition MembersOf_sim_entity_collision_volume_group[] = 
{
    {0, MetaType_sim_entity_collision_volume, "TotalVolume", (memory_index)(&(((sim_entity_collision_volume_group *)0)->TotalVolume))},
    {0, MetaType_uint32, "VolumeCount", (memory_index)(&(((sim_entity_collision_volume_group *)0)->VolumeCount))},
    {MetaMemberFlag_IsPointer, MetaType_sim_entity_collision_volume, "Volumes", (memory_index)(&(((sim_entity_collision_volume_group *)0)->Volumes))},
};
member_definition MembersOf_sim_entity[] = 
{
    {MetaMemberFlag_IsPointer, MetaType_world_chunk, "OldChunk", (memory_index)(&(((sim_entity *)0)->OldChunk))},
    {0, MetaType_uint32, "StorageIndex", (memory_index)(&(((sim_entity *)0)->StorageIndex))},
    {0, MetaType_bool32, "Updatable", (memory_index)(&(((sim_entity *)0)->Updatable))},
    {0, MetaType_entity_type, "Type", (memory_index)(&(((sim_entity *)0)->Type))},
    {0, MetaType_uint32, "Flags", (memory_index)(&(((sim_entity *)0)->Flags))},
    {0, MetaType_v3, "P", (memory_index)(&(((sim_entity *)0)->P))},
    {0, MetaType_v3, "dP", (memory_index)(&(((sim_entity *)0)->dP))},
    {0, MetaType_real32, "DistanceLimit", (memory_index)(&(((sim_entity *)0)->DistanceLimit))},
    {MetaMemberFlag_IsPointer, MetaType_sim_entity_collision_volume_group, "Collision", (memory_index)(&(((sim_entity *)0)->Collision))},
    {0, MetaType_real32, "FacingDirection", (memory_index)(&(((sim_entity *)0)->FacingDirection))},
    {0, MetaType_real32, "tBob", (memory_index)(&(((sim_entity *)0)->tBob))},
    {0, MetaType_int32, "dAbsTileZ", (memory_index)(&(((sim_entity *)0)->dAbsTileZ))},
    {0, MetaType_uint32, "HitPointMax", (memory_index)(&(((sim_entity *)0)->HitPointMax))},
    {0, MetaType_hit_point, "HitPoints", (memory_index)(&(((sim_entity *)0)->HitPoints))},
    {0, MetaType_entity_reference, "Sword", (memory_index)(&(((sim_entity *)0)->Sword))},
    {0, MetaType_v2, "WalkableDim", (memory_index)(&(((sim_entity *)0)->WalkableDim))},
    {0, MetaType_real32, "WalkableHeight", (memory_index)(&(((sim_entity *)0)->WalkableHeight))},
};
member_definition MembersOf_sim_region[] = 
{
    {MetaMemberFlag_IsPointer, MetaType_world, "World", (memory_index)(&(((sim_region *)0)->World))},
    {0, MetaType_real32, "MaxEntityRadius", (memory_index)(&(((sim_region *)0)->MaxEntityRadius))},
    {0, MetaType_real32, "MaxEntityVelocity", (memory_index)(&(((sim_region *)0)->MaxEntityVelocity))},
    {0, MetaType_world_position, "Origin", (memory_index)(&(((sim_region *)0)->Origin))},
    {0, MetaType_rectangle3, "Bounds", (memory_index)(&(((sim_region *)0)->Bounds))},
    {0, MetaType_rectangle3, "UpdatableBounds", (memory_index)(&(((sim_region *)0)->UpdatableBounds))},
    {0, MetaType_uint32, "MaxEntityCount", (memory_index)(&(((sim_region *)0)->MaxEntityCount))},
    {0, MetaType_uint32, "EntityCount", (memory_index)(&(((sim_region *)0)->EntityCount))},
    {MetaMemberFlag_IsPointer, MetaType_sim_entity, "Entities", (memory_index)(&(((sim_region *)0)->Entities))},
    {0, MetaType_sim_entity_hash, "Hash", (memory_index)(&(((sim_region *)0)->Hash))},
};
member_definition MembersOf_rectangle2[] = 
{
    {0, MetaType_v2, "Min", (memory_index)(&(((rectangle2 *)0)->Min))},
    {0, MetaType_v2, "Max", (memory_index)(&(((rectangle2 *)0)->Max))},
};
member_definition MembersOf_rectangle3[] = 
{
    {0, MetaType_v3, "Min", (memory_index)(&(((rectangle3 *)0)->Min))},
    {0, MetaType_v3, "Max", (memory_index)(&(((rectangle3 *)0)->Max))},
};
member_definition MembersOf_world_position[] = 
{
    {0, MetaType_int32, "ChunkX", (memory_index)(&(((world_position *)0)->ChunkX))},
    {0, MetaType_int32, "ChunkY", (memory_index)(&(((world_position *)0)->ChunkY))},
    {0, MetaType_int32, "ChunkZ", (memory_index)(&(((world_position *)0)->ChunkZ))},
    {0, MetaType_v3, "Offset_", (memory_index)(&(((world_position *)0)->Offset_))},
};
#define META_HANDLE_TYPE_DUMP(MemberPtr, NextIndentLevel) \
    case MetaType_world_position: DEBUGTextLine(Member->Name); DEBUGDumpStruct(ArrayCount(MembersOf_world_position), MembersOf_world_position, MemberPtr, (NextIndentLevel)); break; \
    case MetaType_rectangle3: DEBUGTextLine(Member->Name); DEBUGDumpStruct(ArrayCount(MembersOf_rectangle3), MembersOf_rectangle3, MemberPtr, (NextIndentLevel)); break; \
    case MetaType_rectangle2: DEBUGTextLine(Member->Name); DEBUGDumpStruct(ArrayCount(MembersOf_rectangle2), MembersOf_rectangle2, MemberPtr, (NextIndentLevel)); break; \
    case MetaType_sim_region: DEBUGTextLine(Member->Name); DEBUGDumpStruct(ArrayCount(MembersOf_sim_region), MembersOf_sim_region, MemberPtr, (NextIndentLevel)); break; \
    case MetaType_sim_entity: DEBUGTextLine(Member->Name); DEBUGDumpStruct(ArrayCount(MembersOf_sim_entity), MembersOf_sim_entity, MemberPtr, (NextIndentLevel)); break; \
    case MetaType_sim_entity_collision_volume_group: DEBUGTextLine(Member->Name); DEBUGDumpStruct(ArrayCount(MembersOf_sim_entity_collision_volume_group), MembersOf_sim_entity_collision_volume_group, MemberPtr, (NextIndentLevel)); break; \
    case MetaType_sim_entity_collision_volume: DEBUGTextLine(Member->Name); DEBUGDumpStruct(ArrayCount(MembersOf_sim_entity_collision_volume), MembersOf_sim_entity_collision_volume, MemberPtr, (NextIndentLevel)); break; 
