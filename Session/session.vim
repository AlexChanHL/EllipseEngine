let SessionLoad = 1
let s:so_save = &g:so | let s:siso_save = &g:siso | setg so=0 siso=0 | setl so=-1 siso=-1
let v:this_session=expand("<sfile>:p")
silent only
silent tabonly
cd ~/Project\ Files/C++/C++\ ActiveProjects/EllipseEngine
if expand('%') == '' && !&modified && line('$') <= 1 && getline(1) == ''
  let s:wipebuf = bufnr('%')
endif
let s:shortmess_save = &shortmess
if &shortmess =~ 'A'
  set shortmess=aoOA
else
  set shortmess=aoO
endif
badd +368 src/Engine/Engine/Core/ModelManagerModule.cpp
badd +8 ~/Project\ Files/C++/C++\ ActiveProjects/EllipseEngine/.gitignore
badd +20 ~/Project\ Files/C++/C++\ ActiveProjects/EllipseEngine/src/Engine/Engine/Input/Input.hpp
badd +272 src/Engine/Engine/Core/ModelManagerModule.hpp
badd +18 ~/Project\ Files/C++/C++\ ActiveProjects/EllipseEngine/src/Engine/Engine/Event/Event.hpp
badd +19 ~/Project\ Files/C++/C++\ ActiveProjects/EllipseEngine/src/Engine/Engine/Renderer/RenderModule.hpp
badd +71 ~/Project\ Files/C++/C++\ ActiveProjects/EllipseEngine/src/Engine/Engine/Renderer/RenderModule.cpp
badd +121 ~/Project\ Files/C++/C++\ ActiveProjects/EllipseEngine/src/Engine/Engine/Renderer/UniformVarible.hpp
badd +35 ~/Project\ Files/C++/C++\ ActiveProjects/EllipseEngine/src/Engine/Engine/Renderer/RenderObj.hpp
badd +1 ~/Project\ Files/C++/C++\ ActiveProjects/EllipseEngine/src/Engine/Engine/Platform/GraphicsContext/SDLGraphicsContext.cpp
badd +1 ~/Project\ Files/C++/C++\ ActiveProjects/EllipseEngine/src/Engine/Engine/Platform/GraphicsContext/SDLGraphicsContext.hpp
badd +66 ~/Project\ Files/C++/C++\ ActiveProjects/EllipseEngine/src/Engine/Engine/Platform/RenderPlugin/OpenGL/GLRenderPlugin.cpp
badd +27 ~/Project\ Files/C++/C++\ ActiveProjects/EllipseEngine/src/Engine/Engine/Platform/RenderPlugin/OpenGL/GLRenderPlugin.hpp
badd +33 ~/Project\ Files/C++/C++\ ActiveProjects/EllipseEngine/src/Engine/Engine/Core/LayerStack.cpp
badd +37 ~/Project\ Files/C++/C++\ ActiveProjects/EllipseEngine/src/Engine/Engine/Core/LayerStack.hpp
badd +23 ~/Project\ Files/C++/C++\ ActiveProjects/EllipseEngine/src/Engine/Engine/Core/Base.hpp
badd +35 ~/Project\ Files/C++/C++\ ActiveProjects/EllipseEngine/CMake/ProjectSettings.cmake
badd +17 ~/Project\ Files/C++/C++\ ActiveProjects/EllipseEngine/CMake/ProjectWarnings.cmake
badd +20 ~/Project\ Files/C++/C++\ ActiveProjects/EllipseEngine/src/Engine/Vendor/CMakeLists.txt
badd +1 ~/Project\ Files/C++/C++\ ActiveProjects/EllipseEngine/src/Engine/Engine/Debug/Log/Log.hppa
badd +39 ~/Project\ Files/C++/C++\ ActiveProjects/EllipseEngine/src/Engine/Engine/CMakeLists.txt
badd +21 ~/Project\ Files/C++/C++\ ActiveProjects/EllipseEngine/src/App/CMakeLists.txt
badd +44 ~/Project\ Files/C++/C++\ ActiveProjects/EllipseEngine/src/Engine/Engine/Debug/Log/Log.hpp
badd +4 ~/Project\ Files/C++/C++\ ActiveProjects/EllipseEngine/src/Engine/Engine/Debug/Log/Log.cpp
badd +28 ~/Project\ Files/C++/C++\ ActiveProjects/EllipseEngine/src/App/Core/DemoLayer.cpp
badd +43 src/Engine/Engine/Core/Application.cpp
badd +75 ~/Project\ Files/C++/C++\ ActiveProjects/EllipseEngine/src/App/Core/DemoLayer.hpp
badd +101 ~/Project\ Files/C++/C++\ ActiveProjects/EllipseEngine/src/Engine/Engine/Platform/RenderPlugin/OpenGL/OpenGLObj.cpp
badd +206 ~/Project\ Files/C++/C++\ ActiveProjects/EllipseEngine/src/Engine/Engine/Platform/RenderPlugin/OpenGL/OpenGLObj.hpp
badd +3 man://float(3)
badd +27 ~/Project\ Files/C++/C++\ ActiveProjects/EllipseEngine/src/Engine/Engine/Renderer/Renderer.hpp
badd +23 ~/Project\ Files/C++/C++\ ActiveProjects/EllipseEngine/src/Engine/Engine/Renderer/Renderer.cpp
badd +25 src/Engine/Engine/Renderer/RenderPlugin.hpp
badd +28 src/Engine/Engine/Engine/Module.hpp
badd +14 ~/Project\ Files/C++/C++\ ActiveProjects/EllipseEngine/src/Engine/Engine/Engine/Engine.hpp
badd +89 ~/Project\ Files/C++/C++\ ActiveProjects/EllipseEngine/src/Engine/Engine/Engine/Engine.cpp
badd +301 ~/Project\ Files/C++/C++\ ActiveProjects/EllipseEngine/src/Engine/Engine/Core/Utils/VectorSharedIteratorHeap.hpp
badd +10 ~/Project\ Files/C++/C++\ ActiveProjects/EllipseEngine/src/Engine/Engine/Renderer/RenderPlugin.cpp
badd +20 ~/Project\ Files/C++/C++\ ActiveProjects/EllipseEngine/src/Engine/Engine/Assets/Shader/Triangle.vert.glsl
badd +11 ~/Project\ Files/C++/C++\ ActiveProjects/EllipseEngine/src/Engine/Engine/Assets/Shader/Triangle.frag.glsla1
badd +39 src/Engine/Engine/Core/Window.hpp
badd +15 ~/Project\ Files/C++/C++\ ActiveProjects/EllipseEngine/src/Engine/Engine/Math/Matrix.hpp
badd +1 man://builtin(1)
badd +26 src/Engine/Engine/Math/TrigonometricUnits.hpp
badd +0 man://if(3pm)
badd +104 src/Engine/Engine/Event/MouseEvent.hpp
badd +141 src/Engine/Engine/Platform/Window/SDLWindow/SDLWindow.hpp
badd +59 src/Engine/Engine/Core/Utils.hpp
badd +14 ~/Project\ Files/C++/C++\ ActiveProjects/EllipseEngine/src/Engine/Engine/Core/Formatter.hpp
badd +5 src/Engine/Engine/Ellipse.hpp
badd +39 ~/Project\ Files/C++/C++\ ActiveProjects/EllipseEngine/src/Engine/Engine/Assets/Shader/Triangle.frag.glsl
badd +12 ~/Project\ Files/C++/C++\ ActiveProjects/EllipseEngine/build/debug/Debug/bin/Assets/Shader/Triangle.vert.glsl
badd +11 ~/Project\ Files/C++/C++\ ActiveProjects/EllipseEngine/build/debug/Debug/bin/Assets/Shader/Triangle2.frag.glsl
badd +1 ~/Project\ Files/C++/C++\ ActiveProjects/EllipseEngine/build/debug/Debug/bin/Assets/Shader/Triangle.frag.glsl
badd +6 src/Engine/Engine/Assets/Shader/Light.frag.glsl
badd +2 ~/Project\ Files/C++/C++\ ActiveProjects/EllipseEngine/src/App/Core/DemoApp.cpp
badd +1 src/Engine/Engine/Core/Layer.cpp
badd +64 ~/Project\ Files/C++/C++\ ActiveProjects/EllipseEngine/src/Engine/Engine/Core/Layer.hpp
badd +10 src/Engine/Engine/Assets/Shader/Light.vert.glsl
badd +180 ~/Project\ Files/C++/C++\ ActiveProjects/EllipseEngine/src/App/Core/ModelList.hpp
badd +315 ~/Project\ Files/C++/C++\ ActiveProjects/EllipseEngine/src/App/Core/Light.hpp
badd +131 ~/Project\ Files/C++/C++\ ActiveProjects/EllipseEngine/src/App/Core/Weapon.hpp
badd +23 src/Engine/Engine/Core/TimeModule.hpp
badd +89 src/Engine/Engine/Platform/Window/SDLWindow/SDLWindow.cpp
badd +50 src/Engine/Engine/Core/MouseInformation.hpp
badd +1 ~/Project\ Files/C++/C++\ ActiveProjects/EllipseEngine/src/Engine/Engine/Core/Window.cpp
badd +1 ~/Project\ Files/C++/C++\ ActiveProjects/EllipseEngine/src/Engine/Engine/Core/KeyboardInformation.hpp
badd +1 ~/Project\ Files/C++/C++\ ActiveProjects/EllipseEngine/src/Engine/Engine/Event/GamePadEvent.hpp
badd +14 ~/Project\ Files/C++/C++\ ActiveProjects/EllipseEngine/src/Engine/Engine/Platform/Window/SDLWindow/SDLWindowInput.cpp
badd +1 ~/Project\ Files/C++/C++\ ActiveProjects/EllipseEngine/src/Engine/Engine/Renderer/Shape.hpp
badd +1 ~/Project\ Files/C++/C++\ ActiveProjects/EllipseEngine/src/Engine/Engine/Core/KeyCodes.hpp
badd +1 ~/Project\ Files/C++/C++\ ActiveProjects/EllipseEngine/src/Engine/Engine/Core/Model.hpp
badd +6 ~/Project\ Files/C++/C++\ ActiveProjects/EllipseEngine/src/Engine/Engine/Core/MouseCodes.hpp
badd +1 ~/Project\ Files/C++/C++\ ActiveProjects/EllipseEngine/src/Engine/Engine/Core/OSTime.cpp
badd +1 ~/Project\ Files/C++/C++\ ActiveProjects/EllipseEngine/src/Engine/Engine/Core/OSTime.hpp
badd +32 src/Engine/Engine/Math/Random/Random.hpp
badd +127 ~/Project\ Files/C++/C++\ ActiveProjects/EllipseEngine/src/Engine/Engine/Core/ScanCodes.hpp
badd +31 ~/Project\ Files/C++/C++\ ActiveProjects/EllipseEngine/src/App/Core/CubeMadeCube.hpp
badd +1 src/Engine/Vendor/glm/doc/manual/noise-simplex2.jpg
badd +2 ~/Project\ Files/C++/C++\ ActiveProjects/EllipseEngine/COPYING.txt
badd +0 ~/Project\ Files/C++/C++\ ActiveProjects/EllipseEngine/README.md
argglobal
%argdel
edit ~/Project\ Files/C++/C++\ ActiveProjects/EllipseEngine/src/Engine/Engine/Assets/Shader/Triangle.frag.glsl
let s:save_splitbelow = &splitbelow
let s:save_splitright = &splitright
set splitbelow splitright
wincmd _ | wincmd |
vsplit
1wincmd h
wincmd _ | wincmd |
split
wincmd _ | wincmd |
split
wincmd _ | wincmd |
split
3wincmd k
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
exe '1resize ' . ((&lines * 16 + 35) / 70)
exe 'vert 1resize ' . ((&columns * 102 + 102) / 204)
exe '2resize ' . ((&lines * 16 + 35) / 70)
exe 'vert 2resize ' . ((&columns * 102 + 102) / 204)
exe '3resize ' . ((&lines * 16 + 35) / 70)
exe 'vert 3resize ' . ((&columns * 102 + 102) / 204)
exe '4resize ' . ((&lines * 16 + 35) / 70)
exe 'vert 4resize ' . ((&columns * 102 + 102) / 204)
exe '5resize ' . ((&lines * 22 + 35) / 70)
exe 'vert 5resize ' . ((&columns * 101 + 102) / 204)
exe '6resize ' . ((&lines * 22 + 35) / 70)
exe 'vert 6resize ' . ((&columns * 101 + 102) / 204)
exe '7resize ' . ((&lines * 21 + 35) / 70)
exe 'vert 7resize ' . ((&columns * 101 + 102) / 204)
argglobal
balt ~/Project\ Files/C++/C++\ ActiveProjects/EllipseEngine/src/Engine/Engine/Assets/Shader/Triangle.frag.glsla1
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let &fdl = &fdl
let s:l = 100 - ((12 * winheight(0) + 8) / 16)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 100
normal! 06|
wincmd w
argglobal
if bufexists(fnamemodify("~/Project\ Files/C++/C++\ ActiveProjects/EllipseEngine/src/App/Core/DemoLayer.cpp", ":p")) | buffer ~/Project\ Files/C++/C++\ ActiveProjects/EllipseEngine/src/App/Core/DemoLayer.cpp | else | edit ~/Project\ Files/C++/C++\ ActiveProjects/EllipseEngine/src/App/Core/DemoLayer.cpp | endif
if &buftype ==# 'terminal'
  silent file ~/Project\ Files/C++/C++\ ActiveProjects/EllipseEngine/src/App/Core/DemoLayer.cpp
endif
balt src/Engine/Vendor/glm/doc/manual/noise-simplex2.jpg
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let &fdl = &fdl
let s:l = 47 - ((10 * winheight(0) + 8) / 16)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 47
normal! 03|
wincmd w
argglobal
if bufexists(fnamemodify("~/Project\ Files/C++/C++\ ActiveProjects/EllipseEngine/src/App/Core/DemoLayer.cpp", ":p")) | buffer ~/Project\ Files/C++/C++\ ActiveProjects/EllipseEngine/src/App/Core/DemoLayer.cpp | else | edit ~/Project\ Files/C++/C++\ ActiveProjects/EllipseEngine/src/App/Core/DemoLayer.cpp | endif
if &buftype ==# 'terminal'
  silent file ~/Project\ Files/C++/C++\ ActiveProjects/EllipseEngine/src/App/Core/DemoLayer.cpp
endif
balt src/Engine/Vendor/glm/doc/manual/noise-simplex2.jpg
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let &fdl = &fdl
let s:l = 52 - ((11 * winheight(0) + 8) / 16)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 52
normal! 0
wincmd w
argglobal
if bufexists(fnamemodify("~/Project\ Files/C++/C++\ ActiveProjects/EllipseEngine/src/App/Core/DemoLayer.cpp", ":p")) | buffer ~/Project\ Files/C++/C++\ ActiveProjects/EllipseEngine/src/App/Core/DemoLayer.cpp | else | edit ~/Project\ Files/C++/C++\ ActiveProjects/EllipseEngine/src/App/Core/DemoLayer.cpp | endif
if &buftype ==# 'terminal'
  silent file ~/Project\ Files/C++/C++\ ActiveProjects/EllipseEngine/src/App/Core/DemoLayer.cpp
endif
balt src/Engine/Vendor/glm/doc/manual/noise-simplex2.jpg
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let &fdl = &fdl
let s:l = 28 - ((1 * winheight(0) + 8) / 16)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 28
normal! 02|
wincmd w
argglobal
if bufexists(fnamemodify("~/Project\ Files/C++/C++\ ActiveProjects/EllipseEngine/src/Engine/Engine/Renderer/RenderModule.cpp", ":p")) | buffer ~/Project\ Files/C++/C++\ ActiveProjects/EllipseEngine/src/Engine/Engine/Renderer/RenderModule.cpp | else | edit ~/Project\ Files/C++/C++\ ActiveProjects/EllipseEngine/src/Engine/Engine/Renderer/RenderModule.cpp | endif
if &buftype ==# 'terminal'
  silent file ~/Project\ Files/C++/C++\ ActiveProjects/EllipseEngine/src/Engine/Engine/Renderer/RenderModule.cpp
endif
balt ~/Project\ Files/C++/C++\ ActiveProjects/EllipseEngine/src/Engine/Engine/Renderer/RenderModule.hpp
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let &fdl = &fdl
let s:l = 139 - ((19 * winheight(0) + 11) / 22)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 139
normal! 060|
wincmd w
argglobal
if bufexists(fnamemodify("~/Project\ Files/C++/C++\ ActiveProjects/EllipseEngine/src/Engine/Engine/Platform/RenderPlugin/OpenGL/GLRenderPlugin.cpp", ":p")) | buffer ~/Project\ Files/C++/C++\ ActiveProjects/EllipseEngine/src/Engine/Engine/Platform/RenderPlugin/OpenGL/GLRenderPlugin.cpp | else | edit ~/Project\ Files/C++/C++\ ActiveProjects/EllipseEngine/src/Engine/Engine/Platform/RenderPlugin/OpenGL/GLRenderPlugin.cpp | endif
if &buftype ==# 'terminal'
  silent file ~/Project\ Files/C++/C++\ ActiveProjects/EllipseEngine/src/Engine/Engine/Platform/RenderPlugin/OpenGL/GLRenderPlugin.cpp
endif
balt ~/Project\ Files/C++/C++\ ActiveProjects/EllipseEngine/src/Engine/Engine/Renderer/Renderer.hpp
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let &fdl = &fdl
let s:l = 66 - ((7 * winheight(0) + 11) / 22)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 66
normal! 0
wincmd w
argglobal
if bufexists(fnamemodify("~/Project\ Files/C++/C++\ ActiveProjects/EllipseEngine/src/Engine/Engine/Renderer/RenderModule.cpp", ":p")) | buffer ~/Project\ Files/C++/C++\ ActiveProjects/EllipseEngine/src/Engine/Engine/Renderer/RenderModule.cpp | else | edit ~/Project\ Files/C++/C++\ ActiveProjects/EllipseEngine/src/Engine/Engine/Renderer/RenderModule.cpp | endif
if &buftype ==# 'terminal'
  silent file ~/Project\ Files/C++/C++\ ActiveProjects/EllipseEngine/src/Engine/Engine/Renderer/RenderModule.cpp
endif
balt src/Engine/Engine/Core/ModelManagerModule.cpp
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let &fdl = &fdl
let s:l = 170 - ((12 * winheight(0) + 10) / 21)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 170
normal! 0
wincmd w
4wincmd w
exe '1resize ' . ((&lines * 16 + 35) / 70)
exe 'vert 1resize ' . ((&columns * 102 + 102) / 204)
exe '2resize ' . ((&lines * 16 + 35) / 70)
exe 'vert 2resize ' . ((&columns * 102 + 102) / 204)
exe '3resize ' . ((&lines * 16 + 35) / 70)
exe 'vert 3resize ' . ((&columns * 102 + 102) / 204)
exe '4resize ' . ((&lines * 16 + 35) / 70)
exe 'vert 4resize ' . ((&columns * 102 + 102) / 204)
exe '5resize ' . ((&lines * 22 + 35) / 70)
exe 'vert 5resize ' . ((&columns * 101 + 102) / 204)
exe '6resize ' . ((&lines * 22 + 35) / 70)
exe 'vert 6resize ' . ((&columns * 101 + 102) / 204)
exe '7resize ' . ((&lines * 21 + 35) / 70)
exe 'vert 7resize ' . ((&columns * 101 + 102) / 204)
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
doautoall SessionLoadPost
unlet SessionLoad
" vim: set ft=vim :
