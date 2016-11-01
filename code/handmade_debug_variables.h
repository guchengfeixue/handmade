#ifndef HANDMADE_DEBUG_VARIABLES_H
#define HANDMADE_DEBUG_VARIABLES_H

struct debug_variable_definition_context {
    debug_state *State;
    memory_arena *Arena;
    debug_variable_reference *Group;
};

internal debug_variable *
DEBUGAddUnreferencedVariable(debug_state *DebugState, debug_variable_type Type, char *Name)
{
    debug_variable *Var = PushStruct(&DebugState->DebugArena, debug_variable);
    Var->Type = Type;
    Var->Name = (char *)PushCopy(&DebugState->DebugArena, StringLength(Name) + 1, Name);

    return Var;
}

internal debug_variable_reference *
DEBUGAddVariableReference(debug_state *DebugState, debug_variable_reference *GroupRef, debug_variable *Var)
{
    debug_variable_reference *Ref = PushStruct(&DebugState->DebugArena, debug_variable_reference);
    Ref->Var = Var;
    Ref->Next = 0;

    Ref->Parent = GroupRef;
    debug_variable *Group = (Ref->Parent) ? Ref->Parent->Var : 0;
    if (Group) {
        if (Group->Group.LastChild) {
            Group->Group.LastChild = Group->Group.LastChild->Next = Ref;
        } else {
            Group->Group.LastChild = Group->Group.FirstChild = Ref;
        }
    }
    return Ref;
}

internal debug_variable_reference *
DEBUGAddVariableReference(debug_variable_definition_context *Context, debug_variable *Var)
{
    debug_variable_reference *Ref = DEBUGAddVariableReference(Context->State, Context->Group, Var);

    return Ref;
}

internal debug_variable_reference *
DEBUGAddVariable(debug_variable_definition_context *Context, debug_variable_type Type, char *Name)
{
    debug_variable *Var = DEBUGAddUnreferencedVariable(Context->State, Type, Name);
    debug_variable_reference *Ref = DEBUGAddVariableReference(Context, Var);
    return Ref;
}

internal debug_variable *
DEBUGAddRootGroupInternal(debug_state *DebugState, char *Name)
{
    debug_variable *Group = DEBUGAddUnreferencedVariable(DebugState, DebugVariableType_Group, Name);
    Group->Group.Expanded = true;
    Group->Group.FirstChild = Group->Group.LastChild = 0;

    return Group;
}

internal debug_variable_reference *
DEBUGAddRootGroup(debug_state *DebugState, char *Name)
{
    debug_variable_reference *Group =
        DEBUGAddVariableReference(DebugState, 0, DEBUGAddRootGroupInternal(DebugState, Name));

    return Group;
}

internal debug_variable_reference *
DEBUGBeginVariableGroup(debug_variable_definition_context *Context, char *Name)
{
    debug_variable_reference *Group =
        DEBUGAddVariableReference(Context, DEBUGAddRootGroupInternal(Context->State, Name));
    Group->Var->Group.Expanded = false;

    Context->Group = Group;

    return Group;
}

internal debug_variable_reference *
DEBUGAddVariable(debug_variable_definition_context *Context, char *Name, b32 Value)
{
    debug_variable_reference *Ref = DEBUGAddVariable(Context, DebugVariableType_Bool32, Name);
    Ref->Var->Bool32 = Value;
    return Ref;
}

internal debug_variable_reference *
DEBUGAddVariable(debug_variable_definition_context *Context, char *Name, r32 Value)
{
    debug_variable_reference *Ref = DEBUGAddVariable(Context, DebugVariableType_Real32, Name);
    Ref->Var->Real32 = Value;
    return Ref;
}

internal debug_variable_reference *
DEBUGAddVariable(debug_variable_definition_context *Context, char *Name, v4 Value)
{
    debug_variable_reference *Ref = DEBUGAddVariable(Context, DebugVariableType_V4, Name);
    Ref->Var->Vector4 = Value;
    return Ref;
}

internal void
DEBUGEndVariableGroup(debug_variable_definition_context *Context)
{
    Assert(Context->Group);

    Context->Group = Context->Group->Parent;
}

internal void
DEBUGCreateVariables(debug_variable_definition_context *Context) {
    debug_variable_reference *UseDebugCameraRef = 0;

#define DEBUG_VARIABLE_LISTING(Name) DEBUGAddVariable(Context, #Name, DEBUGUI_##Name)

    DEBUGBeginVariableGroup(Context, "Ground Chunks");
    DEBUG_VARIABLE_LISTING(GroundChunkOutlines);
    DEBUG_VARIABLE_LISTING(GroundChunkCheckerboards);
    DEBUG_VARIABLE_LISTING(RecomputeGroundChunksOnEXEChange);
    DEBUGEndVariableGroup(Context);

    DEBUGBeginVariableGroup(Context, "Particles");
    DEBUG_VARIABLE_LISTING(ParticleTest);
    DEBUG_VARIABLE_LISTING(ParticleGrid);
    DEBUGEndVariableGroup(Context);

    DEBUGBeginVariableGroup(Context, "Renderer");
    {
        DEBUG_VARIABLE_LISTING(TestWeirdDrawBufferSize);
        DEBUG_VARIABLE_LISTING(ShowLightingSamples);

        DEBUGBeginVariableGroup(Context, "Camera");
        {
            UseDebugCameraRef = DEBUG_VARIABLE_LISTING(UseDebugCamera);
            DEBUG_VARIABLE_LISTING(DebugCameraDistance);
            DEBUG_VARIABLE_LISTING(UseRoomBasedCamera);
        }
        DEBUGEndVariableGroup(Context);

    }
    DEBUGEndVariableGroup(Context);

    DEBUG_VARIABLE_LISTING(FamiliarFollowsHero);
    DEBUG_VARIABLE_LISTING(UseSpaceOutlines);
    DEBUG_VARIABLE_LISTING(FauxV4);

    DEBUGAddVariableReference(Context, UseDebugCameraRef->Var);
#undef DEBUG_VARIABLE_LISTING
}

#endif
