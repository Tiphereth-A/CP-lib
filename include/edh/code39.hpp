#ifndef TIFALIBS_EDH_CODE39
#define TIFALIBS_EDH_CODE39

#include "../util/alias_others.hpp"

namespace tifa_libs {

class code39 {
  static CEXP u32 symbol[44]{1341, 3351, 1815, 3861, 1335, 3381, 1845, 1311, 3357, 1821, 3399, 1863, 3909, 1479, 3525, 1989, 1359, 3405, 1869, 1485, 3411, 1875, 3921, 1491, 3537, 2001, 1395, 3441, 1905, 1521, 3159, 1239, 3285, 1143, 3189, 1269, 1119, 3165, 1245, 17477, 17489, 17681, 20753, 1149};
  static CEXP char fullmap[] = "%U$A$B$C$D$E$F$G$H$I$J$K$L$M$N$O$P$Q$R$S$T$U$V$W$X$Y$Z%A%B%C%D%E */A/B/C/D/E/F/G/H/I/J/K/L-*.*/O0*1*2*3*4*5*6*7*8*9*/Z%F%G%H%I%J%VA*B*C*D*E*F*G*H*I*J*K*L*M*N*O*P*Q*R*S*T*U*V*W*X*Y*Z*%K%L%M%N%O%W+A+B+C+D+E+F+G+H+I+J+K+L+M+N+O+P+Q+R+S+T+U+V+W+X+Y+Z%P%Q%R%S%T";

  static CEXP strn expand(strnv s) NE {
    strn ans;
    ans.reserve(s.size() * 2);
    for (auto c : s)
      if (ans.push_back(fullmap[(u32)c * 2]); fullmap[(u32)c * 2 + 1] != '*') ans.push_back(fullmap[(u32)c * 2 + 1]);
    ans.shrink_to_fit();
    return ans;
  }
  static CEXP strn parse(strnv s) NE {
    strn ans;
    ans.reserve(s.size());
    flt_ (u32, i, 0, (u32)s.size())
      if (s[i] == '$') ans += char(s[++i] - 'A' + 1);
      else if (s[i] == '/') ans += char(s[++i] - 'A' + 33);
      else if (s[i] == '+') ans += (char)tolower(s[++i]);
      else if (s[i] == '%') {
        if (char c = s[++i]; c == 'U') ans += '\0';
        else if (c == 'V') ans += '\x40';
        else if (c == 'W') ans += '\x60';
        else if (c >= 'T') ans += '\x7f';
        else ans += char((c - 'A') / 5 * 32 + (c - 'A') % 5 + 27);
      } else ans += s[i];
    ans.shrink_to_fit();
    return ans;
  }

 public:
  static CEXP char alphabet[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ-. $/+%*";
  template <bool full = false>
  static CEXP vecu encode(strnv s) NE {
    strn _;
    if CEXP (full) _ = expand(s), s = _;
    vecu ret;
    ret.reserve((s.size() + 1) / 2);
    for (u32 i = 0; i + 1 < s.size(); i += 2) ret.push_back(symbol[std::find(alphabet, alphabet + 45, s[i]) - alphabet] << 16 | symbol[std::find(alphabet, alphabet + 45, s[i + 1]) - alphabet]);
    if (s.size() & 1) ret.push_back(symbol[std::find(alphabet, alphabet + 45, s.back()) - alphabet]);
    return ret;
  }
  template <bool mod10 = true>  //== false: mod43
  static CEXP u32 check_digit(spnu s) NE {
    u64 ans = 0;
    for (auto i : s) ans += u64((std::find(symbol, symbol + 44, i >> 16) - symbol) + (std::find(symbol, symbol + 44, i & 0xffff) - symbol));
    if CEXP (mod10) return u32(ans % 10);
    else return u32(ans % 43);
  }
  template <bool full = false>
  static CEXP strn decode(spnu s) NE {
    strn ans;
    ans.reserve(s.size() * 2);
    for (u32 i = 0; i + 1 < s.size(); ++i) (ans += alphabet[std::find(symbol, symbol + 44, s[i] >> 16) - symbol]) += alphabet[std::find(symbol, symbol + 44, s[i] & 0xffff) - symbol];
    if (s.back() >> 16) ans += alphabet[std::find(symbol, symbol + 44, s.back() >> 16) - symbol];
    ans += alphabet[std::find(symbol, symbol + 44, s.back() & 0xffff) - symbol];
    if CEXP (full) ans = parse(ans);
    return ans;
  }
};

}  // namespace tifa_libs

#endif