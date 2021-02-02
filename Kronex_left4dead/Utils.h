#pragma once

namespace Utils
{
  ValueTypes GetValueType(const string &str);
  bool IsFloat(const string &str);
  bool IsInt(const string &str);

  void* FindPattern(DWORD module, string pattern, string callInfo = "", int dwFinalOffset = 0);
  template<class T> T FindPattern(DWORD module, string pattern, string callInfo = "", int dwFinalOffset = 0)
  {
    return (T)FindPattern(module, pattern, callInfo, dwFinalOffset);
  }

  const float Get2dDistance(float* point1, float* point2);
  const float Get3dDistance(float* point1, float* point2);
  const float GetAngleDistance(float* angle1, float* angle2);
  const float Get2dSummaryVelocity(float velocity1, float velocity2);
  const float Get3dSummaryVelocity(float velocity1, float velocity2, float velocity3);

  const void LimitAngles(QAngle &angles);
  const void LimitVector(Vector &vector);

  const DWORD CountPatternBytes(const string &pattern);

  const bool MemCopyToPattern(string& pattern, void* src, DWORD size);

  const DWORD PatternToHexString(const string &pattern, string &hexString);
  const DWORD PatternToHexString(const string &pattern, string &hexString, string &mask);

  const string ByteToHex(byte byte);
  const void HexStringToPattern(const string &hexString, string &pattern, DWORD length);

  const wchar_t* GetWC(const char *c);

  string U16S_S8(const u16string &u16str);
  u16string S8_U16S(const string &str8);
  wstring S8_WS(const string &str8);
  string WS_S8(const wstring &wstr);

  vector<int> SeparatorPos(const string &str, const string &separator);
  vector<string> split_S8(const string &str, const char separator);
  vector<string> split_S8(const string &str, const string &separator);

  void DrawOutlinedRect(int x0, int y0, int x1, int y1, int thickness = 1);
  void DrawLine(int x0, int y0, int x1, int y1, int thickness = 1);
  void DrawFilledCircle(int x, int y, int radius, int segments);
  void DrawPrintText(const string &text, vgui::FontDrawType_t drawType = vgui::FONT_DRAW_DEFAULT);
};

#define BEGIN_NAMESPACE( x ) namespace x {
#define END_NAMESPACE }

BEGIN_NAMESPACE(XorCompileTime)

constexpr auto time = __TIME__;
constexpr auto seed = static_cast< int >(time[7]) + static_cast< int >(time[6]) * 10 + static_cast< int >(time[4]) * 60 + static_cast< int >(time[3]) * 600 + static_cast< int >(time[1]) * 3600 + static_cast< int >(time[0]) * 36000;

template < int N >
struct RandomGenerator
{
private:
  static constexpr unsigned a = 16807; // 7^5
  static constexpr unsigned m = 2147483647; // 2^31 - 1

  static constexpr unsigned s = RandomGenerator< N - 1 >::value;
  static constexpr unsigned lo = a * (s & 0xFFFF); // Multiply lower 16 bits by 16807
  static constexpr unsigned hi = a * (s >> 16); // Multiply higher 16 bits by 16807
  static constexpr unsigned lo2 = lo + ((hi & 0x7FFF) << 16); // Combine lower 15 bits of hi with lo's upper bits
  static constexpr unsigned hi2 = hi >> 15; // Discard lower 15 bits of hi
  static constexpr unsigned lo3 = lo2 + hi;

public:
  static constexpr unsigned max = m;
  static constexpr unsigned value = lo3 > m ? lo3 - m : lo3;
};

template <>
struct RandomGenerator< 0 >
{
  static constexpr unsigned value = seed;
};

template < int N, int M >
struct RandomInt
{
  static constexpr auto value = RandomGenerator< N + ((36 - 34) / 2) >::value % M;
};

template < int N >
struct RandomChar
{
  static const char value = static_cast< char >(((36 - 34) / 2) + RandomInt< N, 0x7F - ((36 - 34) / 2) >::value);
};

template < size_t N, int K >
struct XorString
{
private:
  const char _key;
  std::array< char, N + ((36 - 34) / 2) > _encrypted;

  constexpr char enc(char c) const
  {
    return c ^ _key;
  }

  char dec(char c) const
  {
    return c ^ _key;
  }

public:
  template < size_t... Is >
  constexpr __forceinline XorString(const char* str, std::index_sequence< Is... >) : _key(RandomChar< K >::value), _encrypted{ enc(str[Is])... }
  {
  }

  __forceinline decltype(auto) decrypt()
  {
    for (size_t i = 0; i < N; ++i) {
      _encrypted[i] = dec(_encrypted[i]);
    }
    _encrypted[N] = '\0';
    return _encrypted.data();
  }
};

#define XS( str ) ( XorCompileTime::XorString< sizeof( str ) - ((36 - 34) / 2), __COUNTER__ >( str, make_index_sequence< sizeof( str ) - ((36 - 34) / 2)>() ).decrypt() )

END_NAMESPACE
