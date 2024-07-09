#include "hi.parser/bidirectional_map.h"

namespace hi
{
namespace detail
{

template <uint32_t N, typename T = uint8_t>
constexpr std::unordered_map<std::string_view, T> BidirectionalStringMap::createStrToValueMap() {
  std::unordered_map<std::string_view, T> map;
  for (T i = 0; i < arr_.size(); ++i) { 
    map[arr_[i]] = i; 
  }
  return map;
}

template <uint32_t N, typename T = uint8_t>
constexpr std::unordered_map<T, std::string_view> BidirectionalStringMap::createValueToStrMap() {
  std::unordered_map<T, std::string_view> map;
  for (T i = 0; i < arr_.size(); ++i) { 
    map[i] = arr_[i]; 
  }
  return map;
}


} // namespace detail
} // namespace hi
