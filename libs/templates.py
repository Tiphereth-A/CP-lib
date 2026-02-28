TEMPLATE_CPVDOC_MD = """---
title: {name}
documentation_of: //{path}/lib.hpp
---
"""
TEMPLATE_DOC_TEX = """% {lib.hpp,start=4,stop=-2}
% {usage.cpp}
"""
TEMPLATE_DOC_TYP = """// {lib.hpp,start=4,stop=-2}
// {usage.cpp}
"""
TEMPLATE_LIB_HPP = """#ifndef TIFALIBS_{path_upper}
#define TIFALIBS_{path_upper}

namespace tifa_libs::{category} {{
}}  // namespace tifa_libs::{category}

#endif
"""
TEMPLATE_USAGE_CPP = """#define PROBLEM "https://example.com"

#include "lib.hpp"

int main() {
}

/*
description
*/

/*
input
========
output
*/
"""
