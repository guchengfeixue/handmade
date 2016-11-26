#ifndef HANDMADE_DEBUG_H
#define HANDMADE_DEBUG_H

struct debug_variable;

enum debug_variable_to_text_flag {
    DEBUGVarToText_AddDebugUI = 0x1,
    DEBUGVarToText_AddName = 0x2,
    DEBUGVarToText_FloatSuffix = 0x4,
    DEBUGVarToText_LineFeedEnd = 0x8,
    DEBUGVarToText_NullTerminator = 0x10,
    DEBUGVarToText_Colon = 0x20,
    DEBUGVarToText_PrettyBools = 0x40,
};

enum debug_variable_type {
    DebugVariableType_Bool32,
    DebugVariableType_Int32,
    DebugVariableType_UInt32,
    DebugVariableType_Real32,
    DebugVariableType_V2,
    DebugVariableType_V3,
    DebugVariableType_V4,

    DebugVariableType_CounterThreadList,
    DebugVariableType_BitmapDisplay,

    DebugVariableType_VarGroup,
};

inline b32
DEBUGShouldBeWritten(debug_variable_type Type) {
    b32 Result = ((Type != DebugVariableType_CounterThreadList) &&
                  (Type != DebugVariableType_BitmapDisplay));
    return Result;
}

struct debug_tree;
struct debug_variable;

struct debug_view_inline_block {
    v2 Dim;
};

enum debug_view_type {
    DebugViewType_Unknown,

    DebugViewType_Basic,
    DebugViewType_InlineBlock,
    DebugViewType_Collapsible,
};

struct debug_view_collapsible {
    b32 ExpandedAlways;
    b32 ExpandedAltView;
};

struct debug_id {
    void *Value[2];
};

struct debug_view {
    debug_id ID;
    debug_view *NextInHash;

    debug_view_type Type;
    union {
        debug_view_inline_block InlineBlock;
        debug_view_collapsible Collapsible;
    };
};

struct debug_tree {
    v2 UIP;
    debug_variable *Group;

    debug_tree *Prev;
    debug_tree *Next;
};

struct debug_profile_settings {
    int PlaceHolder;
};

struct debug_bitmap_display {
    bitmap_id ID;
};

struct debug_variable_link {
    debug_variable_link *Next;
    debug_variable_link *Prev;
    debug_variable *Var;
};

struct debug_variable {
    debug_variable_type Type;
    char *Name;

    union {
        b32 Bool32;
        s32 Int32;
        u32 UInt32;
        r32 Real32;
        v2 Vector2;
        v3 Vector3;
        v4 Vector4;
        debug_profile_settings Profile;
        debug_bitmap_display BitmapDisplay;
        debug_variable_link VarGroup;
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

enum debug_interaction_type {
    DebugInteraction_None,

    DebugInteraction_NOP,

    DebugInteraction_AutoModifyVariable,

    DebugInteraction_DragValue,
    DebugInteraction_ToggleValue,
    DebugInteraction_TearValue,

    DebugInteraction_Resize,
    DebugInteraction_Move,
};

struct debug_interaction {
    debug_id ID;
    debug_interaction_type Type;

    union {
        void *Generic;
        debug_variable *Var;
        debug_tree *Tree;
        v2 *P;
    };
};

struct debug_state {
    b32 Initialized;

    platform_work_queue *HighPriorityQueue;

    memory_arena DebugArena;

    render_group *RenderGroup;
    loaded_font *DebugFont;
    hha_font *DebugFontInfo;

    b32 Compiling;
    debug_executing_process Compiler;

    v2 MenuP;
    b32 MenuActive;

    debug_variable *RootGroup;
    debug_view *ViewHash[4096];
    debug_tree TreeSentinel;

    v2 LastMouseP;
    debug_interaction Interaction;
    debug_interaction HotInteraction;
    debug_interaction NextHotInteraction;

    r32 LeftEdge;
    r32 RightEdge;
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

    debug_frame *Frames;
    debug_thread *FirstThread;
    open_debug_block *FirstFreeBlock;
};

#endif // HANDMADE_DEBUG_H
