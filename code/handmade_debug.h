#ifndef HANDMADE_DEBUG_H
#define HANDMADE_DEBUG_H


enum debug_variable_type {
    DebugVariableType_Boolean,
    DebugVariableType_Group,
};

struct debug_variable;

struct debug_variable_group {
    b32 Expanded;
    debug_variable *FirstChild;
    debug_variable *LastChild;
};

struct debug_variable {
    debug_variable_type Type;
    char *Name;
    debug_variable *Next;
    debug_variable *Parent;

    union {
        b32 Bool32;
        debug_variable_group Group;
    };
};

struct render_group;
struct game_assets;
struct loaded_bitmap;
struct loaded_font;
struct hha_font;

enum debug_text_op {
    DEBUGTextOp_DrawText,
    DEBUGTextOp_SizeText,
};

struct debug_counter_snapshot {
    u32 HitCount;
    u64 CycleCount;
};

struct debug_counter_state {
    char *FileName;
    char *BlockName;

    u32 LineNumber;
};

struct debug_frame_region {
    debug_record *Record;
    u64 CycleCount;
    u16 LaneIndex;
    u16 ColorIndex;
    r32 MinT;
    r32 MaxT;
};

#define MAX_REGIONS_PER_FRAME 4*2048
struct debug_frame {
    u64 BeginClock;
    u64 EndClock;
    r32 WallSecondsElapsed;

    u32 RegionCount;
    debug_frame_region *Regions;
};

struct open_debug_block {
    u32 StartingFrameIndex;
    debug_record *Source;
    debug_event *OpeningEvent;
    open_debug_block *Parent;

    open_debug_block *NextFree;
};

struct debug_thread {
    u32 ID;
    u32 LaneIndex;
    open_debug_block *FirstOpenBlock;
    debug_thread *Next;
};

struct debug_state {
    b32 Initialized;

    platform_work_queue *HighPriorityQueue;

    memory_arena DebugArena;

    debug_variable *RootGroup;

    render_group *RenderGroup;
    loaded_font *DebugFont;
    hha_font *DebugFontInfo;

    b32 Compiling;
    debug_executing_process Compiler;

    v2 MenuP;
    b32 MenuActive;
    u32 HotMenuIndex;

    r32 LeftEdge;
    r32 AtY;
    r32 FontScale;
    font_id FontID;
    r32 Width;
    r32 Height;

    debug_record *ScopeToRecord;

    memory_arena CollateArena;
    temporary_memory CollateTemp;

    u32 CollationArrayIndex;
    debug_frame *CollationFrame;

    u32 FrameBarLaneCount;
    r32 FrameBarScale;
    u32 FrameCount;
    b32 Paused;

    b32 ProfileOn;
    rectangle2 ProfileRect;

    debug_frame *Frames;
    debug_thread *FirstThread;
    open_debug_block *FirstFreeBlock;
};

internal void DEBUGStart(game_assets *Assets, u32 Width, u32 Height);
internal void DEBUGEnd(game_input *Input, loaded_bitmap *DrawBuffer);
internal void RefreshCollation(debug_state *DebugState);

#endif // HANDMADE_DEBUG_H
