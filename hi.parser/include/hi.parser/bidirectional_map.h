#ifndef HI_BIDIRECTIONAL_MAP_H
#define HI_BIDIRECTIONAL_MAP_H

#include <string>
#include <string_view>
#include <unordered_map>
#include <cstdint>
#include <array>

namespace hi
{
namespace detail
{
using namespace std::literals::string_view_literals;

template <uint32_t N, typename T = uint8_t>
class BidirectionalStringMap
{
  using Array = std::array<std::string_view, N>;
  const std::unordered_map<std::string_view, T> str_to_value_;
  const std::unordered_map<T, std::string_view> value_to_str_;
  constexpr Array arr_;

protected:
  virtual consteval Array createArray() = 0 const;

  static constexpr std::unordered_map<std::string_view, T> createStrToValueMap() {
    std::unordered_map<std::string_view, T> map;
    for (T i = 0; i < arr_.size(); ++i) { map[arr_[i]] = i; }
    return map;
  }

  static constexpr std::unordered_map<T, std::string_view> createValueToStrMap() {
    std::unordered_map<T, std::string_view> map;
    for (T i = 0; i < arr_.size(); ++i) { map[i] = arr_[i]; }
    return map;
  }

public:
  constexpr BidirectionalStringMap(const Array& arr)
    : arr_(arr),
    str_to_value_(createStrToValueMap()),
    value_to_str_(createValueToStrMap())
  {}
}; // class BidirectionalStringMap

class Html5Map : public BidirectionalStringMap<174>
{
protected:
  consteval Array createArray() const override;
};

} // namespace detail
} // namespace hi

#endif // HI_BIDIRECTIONAL_MAP_H