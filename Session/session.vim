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
badd +33 src/App/3D/Core/GUILayer.cpp
badd +18 src/App/3D/Core/GUILayer.hpp
badd +62 src/App/3D/Core/DemoLayer.cpp
badd +10006 term://~/Project\ Files/C++/C++\ Active\ Projects/EllipseEngine//10014:/bin/bash
badd +47 src/EllipseEngine3D/Engine3D/src/Core/Core/RenderModule.hpp
badd +210 src/EngineInterface/Engine/Core/ModelManagerModule.cpp
badd +20 src/App/3D/Core/ModelList.hpp
badd +395 src/EngineInterface/Engine/Core/ModelManagerModule.hpp
badd +148 src/EllipseEngine3D/Engine3D/src/Core/Core/RenderModule.cpp
badd +41 src/EngineInterface/Engine/Core/Layer.hpp
badd +34 src/App/Core/DemoApp.cpp
badd +118 src/EngineInterface/Engine/Core/Application.cpp
badd +21 src/EngineInterface/Engine/Engine/Engine.hpp
badd +102 src/App/3D/Core/ModelList2D.hpp
badd +6 src/App/CMakeLists.txt
badd +56 src/EngineInterface/Engine/CMakeLists.txt
badd +203 src/EngineInterface/Engine/Renderer/RenderModule.hpp
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
badd +15 src/EngineInterface/Engine/Assets/Shader/Quad.vert.glsl
badd +7 src/EngineInterface/Engine/Assets/Shader/Quad.frag.glsl
badd +20 src/EngineInterface/Vendor/CMakeLists.txt
badd +11 src/App/3D/Core/main.cpp
badd +34 src/App/3D/Core/DemoApp.cpp
badd +58 src/EngineInterface/Engine/Core/Application.hpp
badd +8 src/App/2D/Core/DemoApp.cpp
badd +11 src/App/2D/Core/main.cpp
badd +12 src/App/2D/Core/DemoLayer.hpp
badd +32 src/App/2D/Core/DemoLayer.cpp
badd +8 BuildScripts/configureSettings.txt
badd +26 CMake/ProjectSettings.cmake
badd +5 src/CMakeLists.txt
badd +14 CMakeLists.txt
badd +36 src/EllipseEngine2D/Engine2D/src/Core/Core/RenderModule.cpp
badd +62 src/App/2D/Core/ModelList.hpp
badd +79 src/App/3D/Core/DemoLayer.hpp
badd +1 src/App/Core/GUILayer.cpp
badd +21 src/App/Core/GUILayer.hpp
badd +169 src/App/Core/DemoLayer.cpp
badd +1 src/App/Core/ModelList.hpp
badd +1 src/App/Core/ModelList2D.hpp
badd +1 src/App/Core/ModelVal.hpp
badd +118 src/App/2D/Core/ModelVal.hpp
badd +227 src/EngineInterface/Engine/Platform/RenderPlugin/OpenGL/GLRenderPlugin.cpp
badd +299 src/EngineInterface/Engine/Renderer/UniformVarible.hpp
badd +70 src/EngineInterface/Engine/Renderer/Renderer.cpp
badd +110 src/EngineInterface/Engine/Platform/RenderPlugin/OpenGL/OpenGLObj.hpp
badd +1 src/EngineInterface/CMakeLists.txt
badd +13 README.md
badd +1 src/EngineInterface/Engine/Platform/RenderPlugin/OpenGL/OpenGLObj.cpp
badd +132 src/EngineInterface/Engine/Assets/Shader/Cube.frag.glsl
badd +121 src/EngineInterface/Engine/Renderer/RenderObj.hpp
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
2wincmd k
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
wincmd _ | wincmd |
split
2wincmd k
wincmd w
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
exe '1resize ' . ((&lines * 23 + 32) / 65)
exe 'vert 1resize ' . ((&columns * 91 + 185) / 370)
exe '2resize ' . ((&lines * 23 + 32) / 65)
exe 'vert 2resize ' . ((&columns * 91 + 185) / 370)
exe '3resize ' . ((&lines * 15 + 32) / 65)
exe 'vert 3resize ' . ((&columns * 92 + 185) / 370)
exe '4resize ' . ((&lines * 15 + 32) / 65)
exe 'vert 4resize ' . ((&columns * 92 + 185) / 370)
exe '5resize ' . ((&lines * 15 + 32) / 65)
exe 'vert 5resize ' . ((&columns * 92 + 185) / 370)
exe '6resize ' . ((&lines * 15 + 32) / 65)
exe 'vert 6resize ' . ((&columns * 91 + 185) / 370)
exe '7resize ' . ((&lines * 15 + 32) / 65)
exe 'vert 7resize ' . ((&columns * 91 + 185) / 370)
exe '8resize ' . ((&lines * 15 + 32) / 65)
exe 'vert 8resize ' . ((&columns * 91 + 185) / 370)
exe '9resize ' . ((&lines * 15 + 32) / 65)
exe 'vert 9resize ' . ((&columns * 276 + 185) / 370)
exe '10resize ' . ((&lines * 20 + 32) / 65)
exe 'vert 10resize ' . ((&columns * 93 + 185) / 370)
exe '11resize ' . ((&lines * 21 + 32) / 65)
exe 'vert 11resize ' . ((&columns * 93 + 185) / 370)
exe '12resize ' . ((&lines * 20 + 32) / 65)
exe 'vert 12resize ' . ((&columns * 93 + 185) / 370)
argglobal
balt src/App/2D/Core/DemoApp.cpp
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
let s:l = 8 - ((7 * winheight(0) + 11) / 23)
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
balt src/EllipseEngine3D/Engine3D/src/Core/Core/RenderModule.cpp
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
let s:l = 60 - ((11 * winheight(0) + 11) / 23)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 60
normal! 032|
wincmd w
argglobal
if bufexists(fnamemodify("README.md", ":p")) | buffer README.md | else | edit README.md | endif
if &buftype ==# 'terminal'
  silent file README.md
endif
balt src/App/2D/Core/DemoLayer.cpp
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
let s:l = 5 - ((4 * winheight(0) + 7) / 15)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 5
normal! 02|
wincmd w
argglobal
if bufexists(fnamemodify("src/EngineInterface/Engine/Renderer/RenderObj.hpp", ":p")) | buffer src/EngineInterface/Engine/Renderer/RenderObj.hpp | else | edit src/EngineInterface/Engine/Renderer/RenderObj.hpp | endif
if &buftype ==# 'terminal'
  silent file src/EngineInterface/Engine/Renderer/RenderObj.hpp
endif
balt src/App/2D/Core/DemoLayer.hpp
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
let s:l = 107 - ((13 * winheight(0) + 7) / 15)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 107
normal! 02|
wincmd w
argglobal
if bufexists(fnamemodify("src/App/2D/Core/DemoLayer.hpp", ":p")) | buffer src/App/2D/Core/DemoLayer.hpp | else | edit src/App/2D/Core/DemoLayer.hpp | endif
if &buftype ==# 'terminal'
  silent file src/App/2D/Core/DemoLayer.hpp
endif
balt src/App/2D/Core/DemoLayer.cpp
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
let s:l = 23 - ((13 * winheight(0) + 7) / 15)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 23
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
let s:l = 77 - ((1 * winheight(0) + 7) / 15)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 77
normal! 02|
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
let s:l = 200 - ((0 * winheight(0) + 7) / 15)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 200
normal! 0
wincmd w
argglobal
if bufexists(fnamemodify("src/EngineInterface/Engine/Renderer/Renderer.cpp", ":p")) | buffer src/EngineInterface/Engine/Renderer/Renderer.cpp | else | edit src/EngineInterface/Engine/Renderer/Renderer.cpp | endif
if &buftype ==# 'terminal'
  silent file src/EngineInterface/Engine/Renderer/Renderer.cpp
endif
balt src/EllipseEngine3D/Engine3D/src/Core/Core/RenderModule.cpp
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
let s:l = 70 - ((10 * winheight(0) + 7) / 15)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 70
normal! 012|
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
let s:l = 10006 - ((8 * winheight(0) + 7) / 15)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 10006
normal! 057|
wincmd w
argglobal
if bufexists(fnamemodify("src/EngineInterface/Engine/Platform/RenderPlugin/OpenGL/OpenGLObj.hpp", ":p")) | buffer src/EngineInterface/Engine/Platform/RenderPlugin/OpenGL/OpenGLObj.hpp | else | edit src/EngineInterface/Engine/Platform/RenderPlugin/OpenGL/OpenGLObj.hpp | endif
if &buftype ==# 'terminal'
  silent file src/EngineInterface/Engine/Platform/RenderPlugin/OpenGL/OpenGLObj.hpp
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
let s:l = 57 - ((17 * winheight(0) + 10) / 20)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 57
normal! 020|
wincmd w
argglobal
if bufexists(fnamemodify("src/App/2D/Core/ModelList.hpp", ":p")) | buffer src/App/2D/Core/ModelList.hpp | else | edit src/App/2D/Core/ModelList.hpp | endif
if &buftype ==# 'terminal'
  silent file src/App/2D/Core/ModelList.hpp
endif
balt src/EllipseEngine2D/Engine2D/src/Core/Core/RenderModule.cpp
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
let s:l = 96 - ((18 * winheight(0) + 10) / 21)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 96
normal! 0
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
let s:l = 26 - ((17 * winheight(0) + 10) / 20)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 26
normal! 020|
wincmd w
2wincmd w
exe '1resize ' . ((&lines * 23 + 32) / 65)
exe 'vert 1resize ' . ((&columns * 91 + 185) / 370)
exe '2resize ' . ((&lines * 23 + 32) / 65)
exe 'vert 2resize ' . ((&columns * 91 + 185) / 370)
exe '3resize ' . ((&lines * 15 + 32) / 65)
exe 'vert 3resize ' . ((&columns * 92 + 185) / 370)
exe '4resize ' . ((&lines * 15 + 32) / 65)
exe 'vert 4resize ' . ((&columns * 92 + 185) / 370)
exe '5resize ' . ((&lines * 15 + 32) / 65)
exe 'vert 5resize ' . ((&columns * 92 + 185) / 370)
exe '6resize ' . ((&lines * 15 + 32) / 65)
exe 'vert 6resize ' . ((&columns * 91 + 185) / 370)
exe '7resize ' . ((&lines * 15 + 32) / 65)
exe 'vert 7resize ' . ((&columns * 91 + 185) / 370)
exe '8resize ' . ((&lines * 15 + 32) / 65)
exe 'vert 8resize ' . ((&columns * 91 + 185) / 370)
exe '9resize ' . ((&lines * 15 + 32) / 65)
exe 'vert 9resize ' . ((&columns * 276 + 185) / 370)
exe '10resize ' . ((&lines * 20 + 32) / 65)
exe 'vert 10resize ' . ((&columns * 93 + 185) / 370)
exe '11resize ' . ((&lines * 21 + 32) / 65)
exe 'vert 11resize ' . ((&columns * 93 + 185) / 370)
exe '12resize ' . ((&lines * 20 + 32) / 65)
exe 'vert 12resize ' . ((&columns * 93 + 185) / 370)
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
