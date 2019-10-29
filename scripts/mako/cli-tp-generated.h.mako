/*
// Copyright (c) 2018-2019 Intel Corporation
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
*/

// This file is automatically genererated from cli-tp.h.mako!
// Please do not edit it manually!

%for function in spec.findall('feature/require/command'):
<%
    api = apisigs[function.get('name')]
%>
%if len(api.Params) >= 10:
// ${api.Name} has too many parameters and cannot be automatically generated.
%else:
TRACEPOINT_EVENT(
    CLIntercept,
    ${api.Name},
    TP_ARGS(
%  for i, param in enumerate(api.Params):
%    if i < len(api.Params)-1:
%      if param.Name == 'pfn_notify' or param.Name == 'user_func' or param.Name == 'pfn_free_func':
        void*, ${param.Name},   //${param.Type}${param.TypeEnd}
%      elif param.TypeEnd == '[]':
        ${param.Type}*, ${param.Name},
%      else:
        ${param.Type}${param.TypeEnd}, ${param.Name},
%      endif
%    else:
%      if param.Name != '':
        ${param.Type}${param.TypeEnd}, ${param.Name}
%      endif
%    endif
%  endfor
    ),
    TP_FIELDS(
%  for i, param in enumerate(api.Params):
%    if param.Type.endswith("_info"):
        ctf_integer_hex(int, ${param.Name}, ${param.Name})
%    endif
%  endfor
    )
)

/*
        LTTNG_TRACE(
            ${api.Name},
%  for i, param in enumerate(api.Params):
%    if i < len(api.Params)-1:
            ${param.Name},
%    else:
            ${param.Name} );
%    endif
%  endfor
*/
%endif
%endfor
