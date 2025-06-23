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
badd +66 src/App/Core/DemoLayer.hpp
badd +45 src/App/Core/GUILayer.cpp
badd +10 src/App/Core/GUILayer.hpp
badd +135 src/App/Core/DemoLayer.cpp
badd +9650 term://~/Project\ Files/C++/C++\ Active\ Projects/EllipseEngine//10014:/bin/bash
badd +33 src/EllipseEngine3D/Engine3D/src/Core/Core/RenderModule.hpp
badd +206 src/EngineInterface/Engine/Core/ModelManagerModule.cpp
badd +15 src/App/Core/ModelList.hpp
badd +32 src/EngineInterface/Engine/Core/ModelManagerModule.hpp
badd +129 src/EllipseEngine3D/Engine3D/src/Core/Core/RenderModule.cpp
badd +41 src/EngineInterface/Engine/Core/Layer.hpp
badd +1 src/App/Core/DemoApp.cpp
badd +125 src/EngineInterface/Engine/Core/Application.cpp
badd +21 src/EngineInterface/Engine/Engine/Engine.hpp
badd +47 ~/Project\ Files/C++/C++\ Active\ Projects/EllipseEngine/src/App/Core/ModelList2D.hpp
badd +7 src/App/CMakeLists.txt
badd +14 src/EngineInterface/Engine/CMakeLists.txt
badd +39 src/EngineInterface/Engine/Renderer/RenderModule.hpp
badd +8 src/App/Core/Light.hpp
badd +19 src/EngineInterface/Engine/Platform/Window/SDLWindow/SDLWindow.cpp
badd +1 src/EngineInterface/Engine/Platform/Window/SDLWindow/SDLWindow.hpp
badd +17 src/App/Core/ModelVal.hpp
badd +19 src/App/Core/Material.hpp
badd +39 src/EllipseEngine2D/Engine2D/src/Core/Core/RenderModule.hpp
badd +8 Build/_deps/glmlib-src/glm/trigonometric.hpp
badd +0 src/EngineInterface/Engine/Math/TrigonometricUnits.hpp
argglobal
%argdel
edit src/App/Core/DemoApp.cpp
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
wincmd _ | wincmd |
vsplit
1wincmd h
wincmd w
wincmd w
wincmd _ | wincmd |
vsplit
1wincmd h
wincmd w
wincmd w
wincmd w
wincmd _ | wincmd |
split
wincmd _ | wincmd |
split
wincmd _ | wincmd |
split
wincmd _ | wincmd |
split
4wincmd k
wincmd w
wincmd w
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
exe '1resize ' . ((&lines * 16 + 33) / 67)
exe 'vert 1resize ' . ((&columns * 210 + 158) / 316)
exe '2resize ' . ((&lines * 15 + 33) / 67)
exe 'vert 2resize ' . ((&columns * 105 + 158) / 316)
exe '3resize ' . ((&lines * 15 + 33) / 67)
exe 'vert 3resize ' . ((&columns * 104 + 158) / 316)
exe '4resize ' . ((&lines * 16 + 33) / 67)
exe 'vert 4resize ' . ((&columns * 105 + 158) / 316)
exe '5resize ' . ((&lines * 16 + 33) / 67)
exe 'vert 5resize ' . ((&columns * 104 + 158) / 316)
exe '6resize ' . ((&lines * 15 + 33) / 67)
exe 'vert 6resize ' . ((&columns * 210 + 158) / 316)
exe '7resize ' . ((&lines * 12 + 33) / 67)
exe 'vert 7resize ' . ((&columns * 105 + 158) / 316)
exe '8resize ' . ((&lines * 12 + 33) / 67)
exe 'vert 8resize ' . ((&columns * 105 + 158) / 316)
exe '9resize ' . ((&lines * 12 + 33) / 67)
exe 'vert 9resize ' . ((&columns * 105 + 158) / 316)
exe '10resize ' . ((&lines * 13 + 33) / 67)
exe 'vert 10resize ' . ((&columns * 105 + 158) / 316)
exe '11resize ' . ((&lines * 12 + 33) / 67)
exe 'vert 11resize ' . ((&columns * 105 + 158) / 316)
argglobal
balt src/App/Core/GUILayer.hpp
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
let s:l = 14 - ((12 * winheight(0) + 8) / 16)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 14
normal! 0
wincmd w
argglobal
if bufexists(fnamemodify("~/Project\ Files/C++/C++\ Active\ Projects/EllipseEngine/src/App/Core/ModelList2D.hpp", ":p")) | buffer ~/Project\ Files/C++/C++\ Active\ Projects/EllipseEngine/src/App/Core/ModelList2D.hpp | else | edit ~/Project\ Files/C++/C++\ Active\ Projects/EllipseEngine/src/App/Core/ModelList2D.hpp | endif
if &buftype ==# 'terminal'
  silent file ~/Project\ Files/C++/C++\ Active\ Projects/EllipseEngine/src/App/Core/ModelList2D.hpp
endif
balt src/App/Core/DemoApp.cpp
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
let s:l = 47 - ((10 * winheight(0) + 7) / 15)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 47
normal! 039|
wincmd w
argglobal
if bufexists(fnamemodify("src/App/Core/ModelList.hpp", ":p")) | buffer src/App/Core/ModelList.hpp | else | edit src/App/Core/ModelList.hpp | endif
if &buftype ==# 'terminal'
  silent file src/App/Core/ModelList.hpp
endif
balt ~/Project\ Files/C++/C++\ Active\ Projects/EllipseEngine/src/App/Core/ModelList2D.hpp
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
let s:l = 28 - ((8 * winheight(0) + 7) / 15)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 28
normal! 05|
wincmd w
argglobal
if bufexists(fnamemodify("src/App/Core/GUILayer.cpp", ":p")) | buffer src/App/Core/GUILayer.cpp | else | edit src/App/Core/GUILayer.cpp | endif
if &buftype ==# 'terminal'
  silent file src/App/Core/GUILayer.cpp
endif
balt src/App/Core/GUILayer.hpp
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
let s:l = 35 - ((10 * winheight(0) + 8) / 16)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 35
normal! 030|
wincmd w
argglobal
if bufexists(fnamemodify("src/App/Core/GUILayer.hpp", ":p")) | buffer src/App/Core/GUILayer.hpp | else | edit src/App/Core/GUILayer.hpp | endif
if &buftype ==# 'terminal'
  silent file src/App/Core/GUILayer.hpp
endif
balt src/App/Core/GUILayer.cpp
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
let s:l = 20 - ((14 * winheight(0) + 8) / 16)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 20
normal! 02|
wincmd w
argglobal
if bufexists(fnamemodify("term://~/Project\ Files/C++/C++\ Active\ Projects/EllipseEngine//10014:/bin/bash", ":p")) | buffer term://~/Project\ Files/C++/C++\ Active\ Projects/EllipseEngine//10014:/bin/bash | else | edit term://~/Project\ Files/C++/C++\ Active\ Projects/EllipseEngine//10014:/bin/bash | endif
if &buftype ==# 'terminal'
  silent file term://~/Project\ Files/C++/C++\ Active\ Projects/EllipseEngine//10014:/bin/bash
endif
balt src/App/Core/DemoLayer.cpp
setlocal foldmethod=manual
setlocal foldexpr=0
setlocal foldmarker={{{,}}}
setlocal foldignore=#
setlocal foldlevel=0
setlocal foldminlines=1
setlocal foldnestmax=20
setlocal foldenable
let s:l = 167 - ((3 * winheight(0) + 7) / 15)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 167
normal! 063|
wincmd w
argglobal
if bufexists(fnamemodify("src/App/Core/DemoLayer.cpp", ":p")) | buffer src/App/Core/DemoLayer.cpp | else | edit src/App/Core/DemoLayer.cpp | endif
if &buftype ==# 'terminal'
  silent file src/App/Core/DemoLayer.cpp
endif
balt src/App/Core/ModelList.hpp
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
let s:l = 220 - ((7 * winheight(0) + 6) / 12)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 220
normal! 028|
wincmd w
argglobal
if bufexists(fnamemodify("src/EngineInterface/Engine/Math/TrigonometricUnits.hpp", ":p")) | buffer src/EngineInterface/Engine/Math/TrigonometricUnits.hpp | else | edit src/EngineInterface/Engine/Math/TrigonometricUnits.hpp | endif
if &buftype ==# 'terminal'
  silent file src/EngineInterface/Engine/Math/TrigonometricUnits.hpp
endif
balt Build/_deps/glmlib-src/glm/trigonometric.hpp
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
let s:l = 27 - ((10 * winheight(0) + 6) / 12)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 27
normal! 0
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
let s:l = 129 - ((10 * winheight(0) + 6) / 12)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 129
normal! 0
wincmd w
argglobal
if bufexists(fnamemodify("src/EllipseEngine3D/Engine3D/src/Core/Core/RenderModule.hpp", ":p")) | buffer src/EllipseEngine3D/Engine3D/src/Core/Core/RenderModule.hpp | else | edit src/EllipseEngine3D/Engine3D/src/Core/Core/RenderModule.hpp | endif
if &buftype ==# 'terminal'
  silent file src/EllipseEngine3D/Engine3D/src/Core/Core/RenderModule.hpp
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
let s:l = 48 - ((12 * winheight(0) + 6) / 13)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 48
normal! 045|
wincmd w
argglobal
if bufexists(fnamemodify("src/EllipseEngine3D/Engine3D/src/Core/Core/RenderModule.cpp", ":p")) | buffer src/EllipseEngine3D/Engine3D/src/Core/Core/RenderModule.cpp | else | edit src/EllipseEngine3D/Engine3D/src/Core/Core/RenderModule.cpp | endif
if &buftype ==# 'terminal'
  silent file src/EllipseEngine3D/Engine3D/src/Core/Core/RenderModule.cpp
endif
balt src/EllipseEngine2D/Engine2D/src/Core/Core/RenderModule.hpp
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
let s:l = 107 - ((1 * winheight(0) + 6) / 12)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 107
normal! 015|
wincmd w
4wincmd w
exe '1resize ' . ((&lines * 16 + 33) / 67)
exe 'vert 1resize ' . ((&columns * 210 + 158) / 316)
exe '2resize ' . ((&lines * 15 + 33) / 67)
exe 'vert 2resize ' . ((&columns * 105 + 158) / 316)
exe '3resize ' . ((&lines * 15 + 33) / 67)
exe 'vert 3resize ' . ((&columns * 104 + 158) / 316)
exe '4resize ' . ((&lines * 16 + 33) / 67)
exe 'vert 4resize ' . ((&columns * 105 + 158) / 316)
exe '5resize ' . ((&lines * 16 + 33) / 67)
exe 'vert 5resize ' . ((&columns * 104 + 158) / 316)
exe '6resize ' . ((&lines * 15 + 33) / 67)
exe 'vert 6resize ' . ((&columns * 210 + 158) / 316)
exe '7resize ' . ((&lines * 12 + 33) / 67)
exe 'vert 7resize ' . ((&columns * 105 + 158) / 316)
exe '8resize ' . ((&lines * 12 + 33) / 67)
exe 'vert 8resize ' . ((&columns * 105 + 158) / 316)
exe '9resize ' . ((&lines * 12 + 33) / 67)
exe 'vert 9resize ' . ((&columns * 105 + 158) / 316)
exe '10resize ' . ((&lines * 13 + 33) / 67)
exe 'vert 10resize ' . ((&columns * 105 + 158) / 316)
exe '11resize ' . ((&lines * 12 + 33) / 67)
exe 'vert 11resize ' . ((&columns * 105 + 158) / 316)
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
