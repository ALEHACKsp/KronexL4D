#pragma once

namespace Hooks
{
  // __stdcall fn(...params... on the stack, in reverse order (right to left))
  // __thiscall fn(void* thisptr(ECX), ...params... pushed on stack)
  // __fastcall fn(void* thisptr, void* edx, ...params... stored in registers, then pushed on stack)

  // Client
  void __fastcall IBaseClientDLL_CreateMove(IBaseClientDLL* thisptr, void* pEdx, int sequence_number, float input_sample_frametime, bool active);
  bool __fastcall CreateMoveNew(void* thisptr, void* pEdx, float flInputSampleTime, CUserCmd *cmd);

  // IPanel
  void __fastcall IPanel_PaintTraverse(vgui::IPanel* thisptr, void* pEdx, unsigned int VGUIPanel, bool forcerepaint, bool allowforce);

  // GameMovement
  void __fastcall IGameMovement_ProcessMovement(IGameMovement* thisptr, void* pEdx, CBasePlayer* pPlayer, CMoveData* pMove);

  // prediction
  void __fastcall IPrediction_SetupMove(IPrediction* thisptr, void* pEdx, C_BasePlayer *player, CUserCmd *ucmd, IMoveHelper *pHelper, CMoveData *move);
  void __fastcall IPrediction_FinishMove(IPrediction* thisptr, void* pEdx, C_BasePlayer *player, CUserCmd *ucmd, CMoveData *move);

  // IEngineTrace
  void __fastcall IEngineTrace_TraceRay(IEngineTrace* thisptr, void* pEdx, const Ray_t &ray, unsigned int fMask, ITraceFilter *pTraceFilter, trace_t *pTrace);

  // IVModelRender
  int __fastcall IVModelRender_DrawModel(
    IVModelRender* thisptr,
    void* pEdx,
    int flags,
    IClientRenderable *pRenderable,
    ModelInstanceHandle_t instance,
    int entity_index,
    const model_t *model,
    Vector const &origin,
    QAngle const &angles,
    int skin,
    int body,
    int hitboxset,
    const matrix3x4_t *modelToWorld,
    const matrix3x4_t *pLightingOffset);

  void __fastcall IVModelRender_DrawModelExecute(
    IVModelRender* thisptr,
    void* pEdx,
    const DrawModelState_t &state,
    const ModelRenderInfo_t &pInfo,
    matrix3x4_t *pCustomBoneToWorld);
}