#pragma once

inline const void** GetVMT(const void* instance, size_t offset = 0)
{
  return *reinterpret_cast<const void***>((size_t)instance + offset);
} 

template<typename Function>
inline Function GetVFunc(const void* instance, size_t index, size_t offset = 0)
{
  return reinterpret_cast<Function>(GetVMT(instance, offset)[index]);
}
