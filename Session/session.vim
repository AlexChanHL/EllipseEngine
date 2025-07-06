let SessionLoad = 1
let s:so_save = &g:so | let s:siso_save = &g:siso | setg so=0 siso=0 | setl so=-1 siso=-1
let v:this_session=expand("<sfile>:p")
silent only
silent tabonly
cd ~/Project\ Files/C++/C++\ Active\ Projects/EllipseEngine
if expand('%') == '' && !&modified && line('$') <= 1 && getline(1) == ''
  let s:wipebuf = bufnr('%')
endif
let s:shortmess_save = &shortmess
if &shortmess =~ 'A'
  set shortmess=aoOA
else
  set shortmess=aoO
endif
badd +1 src/App/Core/DemoLayer.hpp
badd +18 src/App/3D/Core/GUILayer.cpp
badd +18 src/App/3D/Core/GUILayer.hpp
badd +86 src/App/3D/Core/DemoLayer.cpp
badd +10010 term://~/Project\ Files/C++/C++\ Active\ Projects/EllipseEngine//10014:/bin/bash
badd +47 src/EllipseEngine3D/Engine3D/src/Core/Core/RenderModule.hpp
badd +210 src/EngineInterface/Engine/Core/ModelManagerModule.cpp
badd +20 src/App/3D/Core/ModelList.hpp
badd +395 src/EngineInterface/Engine/Core/ModelManagerModule.hpp
badd +130 src/EllipseEngine3D/Engine3D/src/Core/Core/RenderModule.cpp
badd +41 src/EngineInterface/Engine/Core/Layer.hpp
badd +34 src/App/Core/DemoApp.cpp
badd +118 src/EngineInterface/Engine/Core/Application.cpp
badd +21 src/EngineInterface/Engine/Engine/Engine.hpp
badd +13 src/App/3D/Core/ModelList2D.hpp
badd +6 src/App/CMakeLists.txt
badd +56 src/EngineInterface/Engine/CMakeLists.txt
badd +2 src/EngineInterface/Engine/Renderer/RenderModule.hpp
badd +8 src/App/Core/Light.hpp
badd +19 src/EngineInterface/Engine/Platform/Window/SDLWindow/SDLWindow.cpp
badd +1 src/EngineInterface/Engine/Platform/Window/SDLWindow/SDLWindow.hpp
badd +15 src/App/3D/Core/ModelVal.hpp
badd +19 src/App/Core/Material.hpp
badd +18 src/EllipseEngine2D/Engine2D/src/Core/Core/RenderModule.hpp
badd +8 Build/_deps/glmlib-src/glm/trigonometric.hpp
badd +27 src/EngineInterface/Engine/Math/TrigonometricUnits.hpp
badd +64 src/EngineInterface/Engine/Math/LinearFunc.hpp
badd +13 Build/_deps/glmlib-src/glm/vec3.hpp
badd +62 Build/_deps/glmlib-src/glm/ext.hpp
badd +12 Build/_deps/glmlib-src/glm/ext/vector_uint4.hpp
badd +1 Build/_deps/glmlib-src/glm/simd/vector_relational.h
badd +124 Build/_deps/glmlib-src/glm/glm.hpp
badd +94 Build/_deps/glmlib-src/glm/geometric.hpp
badd +22 Build/_deps/glmlib-src/glm/common.hpp
badd +6 Build/_deps/glmlib-src/glm/simd/trigonometric.h
badd +803 Build/_deps/glmlib-src/glm/simd/matrix.h
badd +1 Build/_deps/glmlib-src/glm/simd/platform.h
badd +43 Build/_deps/glmlib-src/glm/gtx/rotate_vector.hpp
badd +102 src/EngineInterface/Engine/Core/Base.hpp
badd +49 Build/_deps/glmlib-src/glm/gtx/rotate_vector.inl
badd +1 Build/_deps/glmlib-src/glm/simd/packing.h
badd +1 Build/_deps/glmlib-src/glm/simd/common.h
badd +18 Build/_deps/glmlib-src/glm/ext/vector_float1_precision.hpp
badd +73 Build/_deps/glmlib-src/CMakeLists.txt
badd +288 Build/_deps/glmlib-src/readme.md
badd +1900 Build/_deps/glmlib-src/manual.md
badd +8 Build/Debug/bin/Assets/Shader/Quad.frag.glsl
badd +17 src/EngineInterface/Engine/Assets/Shader/Quad.vert.glsl
badd +12 src/EngineInterface/Engine/Assets/Shader/Quad.frag.glsl
badd +50 src/EngineInterface/Vendor/CMakeLists.txt
badd +11 src/App/3D/Core/main.cpp
badd +34 src/App/3D/Core/DemoApp.cpp
badd +58 src/EngineInterface/Engine/Core/Application.hpp
badd +8 src/App/2D/Core/DemoApp.cpp
badd +11 src/App/2D/Core/main.cpp
badd +25 src/App/2D/Core/DemoLayer.hpp
badd +43 src/App/2D/Core/DemoLayer.cpp
badd +7 BuildScripts/configureSettings.txt
badd +26 CMake/ProjectSettings.cmake
badd +5 src/CMakeLists.txt
badd +14 CMakeLists.txt
badd +40 src/EllipseEngine2D/Engine2D/src/Core/Core/RenderModule.cpp
badd +104 src/App/2D/Core/ModelList.hpp
badd +79 src/App/3D/Core/DemoLayer.hpp
badd +1 src/App/Core/GUILayer.cpp
badd +21 src/App/Core/GUILayer.hpp
badd +169 src/App/Core/DemoLayer.cpp
badd +1 src/App/Core/ModelList.hpp
badd +1 src/App/Core/ModelList2D.hpp
badd +1 src/App/Core/ModelVal.hpp
badd +118 src/App/2D/Core/ModelVal.hpp
badd +26 src/EngineInterface/Engine/Platform/RenderPlugin/OpenGL/GLRenderPlugin.cpp
badd +299 src/EngineInterface/Engine/Renderer/UniformVarible.hpp
badd +68 src/EngineInterface/Engine/Renderer/Renderer.cpp
badd +67 src/EngineInterface/Engine/Platform/RenderPlugin/OpenGL/OpenGLObj.hpp
badd +1 src/EngineInterface/CMakeLists.txt
badd +20 README.md
badd +1 src/EngineInterface/Engine/Platform/RenderPlugin/OpenGL/OpenGLObj.cpp
badd +128 src/EngineInterface/Engine/Assets/Shader/Cube.frag.glsl
badd +59 src/EngineInterface/Engine/Renderer/RenderObj.hpp
badd +18 src/EngineInterface/Vendor/stb_image/stb_image.h
badd +1 Build/src/EngineInterface/Engine/CMakeFiles/EllipseEngineInterface.dir/Renderer/Renderer.cpp.o
badd +22 src/EngineInterface/Engine/Assets/Shader/Cube.vert.glsl
badd +3 src/EngineInterface/Engine/Assets/Fonts/times.ttf
argglobal
%argdel
edit BuildScripts/configureSettings.txt
let s:save_splitbelow = &splitbelow
let s:save_splitright = &splitright
set splitbelow splitright
wincmd _ | wincmd |
vsplit
1wincmd h
wincmd _ | wincmd |
split
1wincmd k
wincmd _ | wincmd |
vsplit
wincmd _ | wincmd |
vsplit
2wincmd h
wincmd _ | wincmd |
split
1wincmd k
wincmd w
wincmd w
wincmd _ | wincmd |
split
wincmd _ | wincmd |
split
wincmd _ | wincmd |
split
3wincmd k
wincmd w
wincmd _ | wincmd |
vsplit
1wincmd h
wincmd w
wincmd w
wincmd w
wincmd w
wincmd _ | wincmd |
split
wincmd _ | wincmd |
split
2wincmd k
wincmd w
wincmd w
wincmd w
wincmd w
wincmd _ | wincmd |
split
1wincmd k
wincmd w
let &splitbelow = s:save_splitbelow
let &splitright = s:save_splitright
wincmd t
let s:save_winminheight = &winminheight
let s:save_winminwidth = &winminwidth
set winminheight=0
set winheight=1
set winminwidth=0
set winwidth=1
exe '1resize ' . ((&lines * 21 + 28) / 57)
exe 'vert 1resize ' . ((&columns * 74 + 186) / 373)
exe '2resize ' . ((&lines * 22 + 28) / 57)
exe 'vert 2resize ' . ((&columns * 74 + 186) / 373)
exe '3resize ' . ((&lines * 10 + 28) / 57)
exe 'vert 3resize ' . ((&columns * 148 + 186) / 373)
exe '4resize ' . ((&lines * 10 + 28) / 57)
exe 'vert 4resize ' . ((&columns * 74 + 186) / 373)
exe '5resize ' . ((&lines * 10 + 28) / 57)
exe 'vert 5resize ' . ((&columns * 73 + 186) / 373)
exe '6resize ' . ((&lines * 11 + 28) / 57)
exe 'vert 6resize ' . ((&columns * 148 + 186) / 373)
exe '7resize ' . ((&lines * 10 + 28) / 57)
exe 'vert 7resize ' . ((&columns * 148 + 186) / 373)
exe '8resize ' . ((&lines * 14 + 28) / 57)
exe 'vert 8resize ' . ((&columns * 74 + 186) / 373)
exe '9resize ' . ((&lines * 14 + 28) / 57)
exe 'vert 9resize ' . ((&columns * 74 + 186) / 373)
exe '10resize ' . ((&lines * 14 + 28) / 57)
exe 'vert 10resize ' . ((&columns * 74 + 186) / 373)
exe '11resize ' . ((&lines * 10 + 28) / 57)
exe 'vert 11resize ' . ((&columns * 298 + 186) / 373)
exe '12resize ' . ((&lines * 27 + 28) / 57)
exe 'vert 12resize ' . ((&columns * 74 + 186) / 373)
exe '13resize ' . ((&lines * 27 + 28) / 57)
exe 'vert 13resize ' . ((&columns * 74 + 186) / 373)
argglobal
balt src/App/3D/Core/GUILayer.cpp
setlocal foldmethod=manual
setlocal foldexpr=0
setlocal foldmarker={{{,}}}
setlocal foldignore=#
setlocal foldlevel=0
setlocal foldminlines=1
setlocal foldnestmax=20
setlocal foldenable
silent! normal! zE
let &fdl = &fdl
let s:l = 8 - ((7 * winheight(0) + 10) / 21)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 8
normal! 0
wincmd w
argglobal
if bufexists(fnamemodify("src/App/2D/Core/DemoLayer.cpp", ":p")) | buffer src/App/2D/Core/DemoLayer.cpp | else | edit src/App/2D/Core/DemoLayer.cpp | endif
if &buftype ==# 'terminal'
  silent file src/App/2D/Core/DemoLayer.cpp
endif
balt src/App/3D/Core/DemoLayer.cpp
setlocal foldmethod=manual
setlocal foldexpr=0
setlocal foldmarker={{{,}}}
setlocal foldignore=#
setlocal foldlevel=0
setlocal foldminlines=1
setlocal foldnestmax=20
setlocal foldenable
silent! normal! zE
let &fdl = &fdl
let s:l = 36 - ((10 * winheight(0) + 11) / 22)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 36
normal! 021|
wincmd w
argglobal
if bufexists(fnamemodify("src/EngineInterface/Engine/Assets/Shader/Cube.frag.glsl", ":p")) | buffer src/EngineInterface/Engine/Assets/Shader/Cube.frag.glsl | else | edit src/EngineInterface/Engine/Assets/Shader/Cube.frag.glsl | endif
if &buftype ==# 'terminal'
  silent file src/EngineInterface/Engine/Assets/Shader/Cube.frag.glsl
endif
balt src/EngineInterface/Engine/Assets/Shader/Quad.frag.glsl
setlocal foldmethod=manual
setlocal foldexpr=0
setlocal foldmarker={{{,}}}
setlocal foldignore=#
setlocal foldlevel=0
setlocal foldminlines=1
setlocal foldnestmax=20
setlocal foldenable
silent! normal! zE
let &fdl = &fdl
let s:l = 131 - ((8 * winheight(0) + 5) / 10)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 131
normal! 022|
wincmd w
argglobal
if bufexists(fnamemodify("src/EngineInterface/Engine/Assets/Shader/Quad.vert.glsl", ":p")) | buffer src/EngineInterface/Engine/Assets/Shader/Quad.vert.glsl | else | edit src/EngineInterface/Engine/Assets/Shader/Quad.vert.glsl | endif
if &buftype ==# 'terminal'
  silent file src/EngineInterface/Engine/Assets/Shader/Quad.vert.glsl
endif
balt src/EngineInterface/Engine/Assets/Shader/Quad.frag.glsl
setlocal foldmethod=manual
setlocal foldexpr=0
setlocal foldmarker={{{,}}}
setlocal foldignore=#
setlocal foldlevel=0
setlocal foldminlines=1
setlocal foldnestmax=20
setlocal foldenable
silent! normal! zE
let &fdl = &fdl
let s:l = 13 - ((7 * winheight(0) + 5) / 10)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 13
normal! 0
wincmd w
argglobal
if bufexists(fnamemodify("src/EngineInterface/Engine/Assets/Shader/Quad.frag.glsl", ":p")) | buffer src/EngineInterface/Engine/Assets/Shader/Quad.frag.glsl | else | edit src/EngineInterface/Engine/Assets/Shader/Quad.frag.glsl | endif
if &buftype ==# 'terminal'
  silent file src/EngineInterface/Engine/Assets/Shader/Quad.frag.glsl
endif
balt README.md
setlocal foldmethod=manual
setlocal foldexpr=0
setlocal foldmarker={{{,}}}
setlocal foldignore=#
setlocal foldlevel=0
setlocal foldminlines=1
setlocal foldnestmax=20
setlocal foldenable
silent! normal! zE
let &fdl = &fdl
let s:l = 9 - ((5 * winheight(0) + 5) / 10)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 9
normal! 0
wincmd w
argglobal
if bufexists(fnamemodify("src/EngineInterface/Engine/Platform/RenderPlugin/OpenGL/OpenGLObj.hpp", ":p")) | buffer src/EngineInterface/Engine/Platform/RenderPlugin/OpenGL/OpenGLObj.hpp | else | edit src/EngineInterface/Engine/Platform/RenderPlugin/OpenGL/OpenGLObj.hpp | endif
if &buftype ==# 'terminal'
  silent file src/EngineInterface/Engine/Platform/RenderPlugin/OpenGL/OpenGLObj.hpp
endif
balt src/EngineInterface/Engine/Platform/RenderPlugin/OpenGL/OpenGLObj.cpp
setlocal foldmethod=manual
setlocal foldexpr=0
setlocal foldmarker={{{,}}}
setlocal foldignore=#
setlocal foldlevel=0
setlocal foldminlines=1
setlocal foldnestmax=20
setlocal foldenable
silent! normal! zE
let &fdl = &fdl
let s:l = 249 - ((10 * winheight(0) + 5) / 11)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 249
normal! 022|
wincmd w
argglobal
if bufexists(fnamemodify("src/EngineInterface/Engine/Renderer/RenderObj.hpp", ":p")) | buffer src/EngineInterface/Engine/Renderer/RenderObj.hpp | else | edit src/EngineInterface/Engine/Renderer/RenderObj.hpp | endif
if &buftype ==# 'terminal'
  silent file src/EngineInterface/Engine/Renderer/RenderObj.hpp
endif
balt README.md
setlocal foldmethod=manual
setlocal foldexpr=0
setlocal foldmarker={{{,}}}
setlocal foldignore=#
setlocal foldlevel=0
setlocal foldminlines=1
setlocal foldnestmax=20
setlocal foldenable
silent! normal! zE
let &fdl = &fdl
let s:l = 57 - ((1 * winheight(0) + 5) / 10)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 57
normal! 022|
wincmd w
argglobal
if bufexists(fnamemodify("src/EngineInterface/Engine/Platform/RenderPlugin/OpenGL/OpenGLObj.hpp", ":p")) | buffer src/EngineInterface/Engine/Platform/RenderPlugin/OpenGL/OpenGLObj.hpp | else | edit src/EngineInterface/Engine/Platform/RenderPlugin/OpenGL/OpenGLObj.hpp | endif
if &buftype ==# 'terminal'
  silent file src/EngineInterface/Engine/Platform/RenderPlugin/OpenGL/OpenGLObj.hpp
endif
balt src/EngineInterface/Engine/Platform/RenderPlugin/OpenGL/OpenGLObj.cpp
setlocal foldmethod=manual
setlocal foldexpr=0
setlocal foldmarker={{{,}}}
setlocal foldignore=#
setlocal foldlevel=0
setlocal foldminlines=1
setlocal foldnestmax=20
setlocal foldenable
silent! normal! zE
let &fdl = &fdl
let s:l = 64 - ((6 * winheight(0) + 7) / 14)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 64
normal! 024|
wincmd w
argglobal
if bufexists(fnamemodify("src/EngineInterface/Engine/Platform/RenderPlugin/OpenGL/GLRenderPlugin.cpp", ":p")) | buffer src/EngineInterface/Engine/Platform/RenderPlugin/OpenGL/GLRenderPlugin.cpp | else | edit src/EngineInterface/Engine/Platform/RenderPlugin/OpenGL/GLRenderPlugin.cpp | endif
if &buftype ==# 'terminal'
  silent file src/EngineInterface/Engine/Platform/RenderPlugin/OpenGL/GLRenderPlugin.cpp
endif
balt src/EngineInterface/Engine/Renderer/Renderer.cpp
setlocal foldmethod=manual
setlocal foldexpr=0
setlocal foldmarker={{{,}}}
setlocal foldignore=#
setlocal foldlevel=0
setlocal foldminlines=1
setlocal foldnestmax=20
setlocal foldenable
silent! normal! zE
let &fdl = &fdl
let s:l = 30 - ((12 * winheight(0) + 7) / 14)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 30
normal! 062|
wincmd w
argglobal
if bufexists(fnamemodify("src/EngineInterface/Engine/Renderer/Renderer.cpp", ":p")) | buffer src/EngineInterface/Engine/Renderer/Renderer.cpp | else | edit src/EngineInterface/Engine/Renderer/Renderer.cpp | endif
if &buftype ==# 'terminal'
  silent file src/EngineInterface/Engine/Renderer/Renderer.cpp
endif
balt Build/src/EngineInterface/Engine/CMakeFiles/EllipseEngineInterface.dir/Renderer/Renderer.cpp.o
setlocal foldmethod=manual
setlocal foldexpr=0
setlocal foldmarker={{{,}}}
setlocal foldignore=#
setlocal foldlevel=0
setlocal foldminlines=1
setlocal foldnestmax=20
setlocal foldenable
silent! normal! zE
let &fdl = &fdl
let s:l = 62 - ((3 * winheight(0) + 7) / 14)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 62
normal! 033|
wincmd w
argglobal
if bufexists(fnamemodify("term://~/Project\ Files/C++/C++\ Active\ Projects/EllipseEngine//10014:/bin/bash", ":p")) | buffer term://~/Project\ Files/C++/C++\ Active\ Projects/EllipseEngine//10014:/bin/bash | else | edit term://~/Project\ Files/C++/C++\ Active\ Projects/EllipseEngine//10014:/bin/bash | endif
if &buftype ==# 'terminal'
  silent file term://~/Project\ Files/C++/C++\ Active\ Projects/EllipseEngine//10014:/bin/bash
endif
balt src/App/3D/Core/DemoLayer.cpp
setlocal foldmethod=manual
setlocal foldexpr=0
setlocal foldmarker={{{,}}}
setlocal foldignore=#
setlocal foldlevel=0
setlocal foldminlines=1
setlocal foldnestmax=20
setlocal foldenable
let s:l = 10010 - ((9 * winheight(0) + 5) / 10)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 10010
normal! 046|
wincmd w
argglobal
if bufexists(fnamemodify("src/EllipseEngine3D/Engine3D/src/Core/Core/RenderModule.cpp", ":p")) | buffer src/EllipseEngine3D/Engine3D/src/Core/Core/RenderModule.cpp | else | edit src/EllipseEngine3D/Engine3D/src/Core/Core/RenderModule.cpp | endif
if &buftype ==# 'terminal'
  silent file src/EllipseEngine3D/Engine3D/src/Core/Core/RenderModule.cpp
endif
balt src/EngineInterface/Engine/Renderer/RenderModule.hpp
setlocal foldmethod=manual
setlocal foldexpr=0
setlocal foldmarker={{{,}}}
setlocal foldignore=#
setlocal foldlevel=0
setlocal foldminlines=1
setlocal foldnestmax=20
setlocal foldenable
silent! normal! zE
let &fdl = &fdl
let s:l = 153 - ((19 * winheight(0) + 13) / 27)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 153
normal! 034|
wincmd w
argglobal
if bufexists(fnamemodify("src/EllipseEngine2D/Engine2D/src/Core/Core/RenderModule.cpp", ":p")) | buffer src/EllipseEngine2D/Engine2D/src/Core/Core/RenderModule.cpp | else | edit src/EllipseEngine2D/Engine2D/src/Core/Core/RenderModule.cpp | endif
if &buftype ==# 'terminal'
  silent file src/EllipseEngine2D/Engine2D/src/Core/Core/RenderModule.cpp
endif
balt src/EngineInterface/Engine/Renderer/RenderModule.hpp
setlocal foldmethod=manual
setlocal foldexpr=0
setlocal foldmarker={{{,}}}
setlocal foldignore=#
setlocal foldlevel=0
setlocal foldminlines=1
setlocal foldnestmax=20
setlocal foldenable
silent! normal! zE
let &fdl = &fdl
let s:l = 37 - ((10 * winheight(0) + 13) / 27)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 37
normal! 0
wincmd w
2wincmd w
exe '1resize ' . ((&lines * 21 + 28) / 57)
exe 'vert 1resize ' . ((&columns * 74 + 186) / 373)
exe '2resize ' . ((&lines * 22 + 28) / 57)
exe 'vert 2resize ' . ((&columns * 74 + 186) / 373)
exe '3resize ' . ((&lines * 10 + 28) / 57)
exe 'vert 3resize ' . ((&columns * 148 + 186) / 373)
exe '4resize ' . ((&lines * 10 + 28) / 57)
exe 'vert 4resize ' . ((&columns * 74 + 186) / 373)
exe '5resize ' . ((&lines * 10 + 28) / 57)
exe 'vert 5resize ' . ((&columns * 73 + 186) / 373)
exe '6resize ' . ((&lines * 11 + 28) / 57)
exe 'vert 6resize ' . ((&columns * 148 + 186) / 373)
exe '7resize ' . ((&lines * 10 + 28) / 57)
exe 'vert 7resize ' . ((&columns * 148 + 186) / 373)
exe '8resize ' . ((&lines * 14 + 28) / 57)
exe 'vert 8resize ' . ((&columns * 74 + 186) / 373)
exe '9resize ' . ((&lines * 14 + 28) / 57)
exe 'vert 9resize ' . ((&columns * 74 + 186) / 373)
exe '10resize ' . ((&lines * 14 + 28) / 57)
exe 'vert 10resize ' . ((&columns * 74 + 186) / 373)
exe '11resize ' . ((&lines * 10 + 28) / 57)
exe 'vert 11resize ' . ((&columns * 298 + 186) / 373)
exe '12resize ' . ((&lines * 27 + 28) / 57)
exe 'vert 12resize ' . ((&columns * 74 + 186) / 373)
exe '13resize ' . ((&lines * 27 + 28) / 57)
exe 'vert 13resize ' . ((&columns * 74 + 186) / 373)
tabnext 1
if exists('s:wipebuf') && len(win_findbuf(s:wipebuf)) == 0 && getbufvar(s:wipebuf, '&buftype') isnot# 'terminal'
  silent exe 'bwipe ' . s:wipebuf
endif
unlet! s:wipebuf
set winheight=1 winwidth=20
let &shortmess = s:shortmess_save
let &winminheight = s:save_winminheight
let &winminwidth = s:save_winminwidth
let s:sx = expand("<sfile>:p:r")."x.vim"
if filereadable(s:sx)
  exe "source " . fnameescape(s:sx)
endif
let &g:so = s:so_save | let &g:siso = s:siso_save
set hlsearch
nohlsearch
doautoall SessionLoadPost
unlet SessionLoad
" vim: set ft=vim :
