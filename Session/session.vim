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
badd +1 src/App/Core/DemoLayer.hpp
badd +453 src/App/Core/DemoLayer.cpp
badd +1527 src/Engine/Engine/Core/ModelManagerModule.hpp
badd +140 src/Engine/Engine/Renderer/RenderModule.cpp
badd +47 ~/Project\ Files/C++/C++\ ActiveProjects/EllipseEngine/src/Engine/Engine/Core/Application.cpp
badd +1 ~/Project\ Files/C++/C++\ ActiveProjects/EllipseEngine/src/Engine/Engine/Renderer/RenderPlugin.cpp
badd +25 ~/Project\ Files/C++/C++\ ActiveProjects/EllipseEngine/src/Engine/Engine/Renderer/Renderer.hpp
badd +29 ~/Project\ Files/C++/C++\ ActiveProjects/EllipseEngine/src/Engine/Engine/Renderer/RenderPlugin.hpp
argglobal
%argdel
edit src/Engine/Engine/Core/ModelManagerModule.hpp
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
exe '1resize ' . ((&lines * 16 + 35) / 70)
exe 'vert 1resize ' . ((&columns * 112 + 112) / 225)
exe '2resize ' . ((&lines * 16 + 35) / 70)
exe 'vert 2resize ' . ((&columns * 112 + 112) / 225)
exe '3resize ' . ((&lines * 16 + 35) / 70)
exe 'vert 3resize ' . ((&columns * 112 + 112) / 225)
exe '4resize ' . ((&lines * 16 + 35) / 70)
exe 'vert 4resize ' . ((&columns * 112 + 112) / 225)
exe '5resize ' . ((&lines * 33 + 35) / 70)
exe 'vert 5resize ' . ((&columns * 112 + 112) / 225)
exe '6resize ' . ((&lines * 33 + 35) / 70)
exe 'vert 6resize ' . ((&columns * 112 + 112) / 225)
argglobal
balt src/App/Core/DemoLayer.cpp
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
let s:l = 1527 - ((6 * winheight(0) + 8) / 16)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 1527
normal! 019|
wincmd w
argglobal
if bufexists(fnamemodify("~/Project\ Files/C++/C++\ ActiveProjects/EllipseEngine/src/Engine/Engine/Core/Application.cpp", ":p")) | buffer ~/Project\ Files/C++/C++\ ActiveProjects/EllipseEngine/src/Engine/Engine/Core/Application.cpp | else | edit ~/Project\ Files/C++/C++\ ActiveProjects/EllipseEngine/src/Engine/Engine/Core/Application.cpp | endif
if &buftype ==# 'terminal'
  silent file ~/Project\ Files/C++/C++\ ActiveProjects/EllipseEngine/src/Engine/Engine/Core/Application.cpp
endif
balt src/App/Core/DemoLayer.cpp
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
let s:l = 47 - ((4 * winheight(0) + 8) / 16)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 47
normal! 0
wincmd w
argglobal
if bufexists(fnamemodify("~/Project\ Files/C++/C++\ ActiveProjects/EllipseEngine/src/Engine/Engine/Renderer/RenderPlugin.hpp", ":p")) | buffer ~/Project\ Files/C++/C++\ ActiveProjects/EllipseEngine/src/Engine/Engine/Renderer/RenderPlugin.hpp | else | edit ~/Project\ Files/C++/C++\ ActiveProjects/EllipseEngine/src/Engine/Engine/Renderer/RenderPlugin.hpp | endif
if &buftype ==# 'terminal'
  silent file ~/Project\ Files/C++/C++\ ActiveProjects/EllipseEngine/src/Engine/Engine/Renderer/RenderPlugin.hpp
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
let s:l = 29 - ((9 * winheight(0) + 8) / 16)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 29
normal! 0113|
wincmd w
argglobal
if bufexists(fnamemodify("src/App/Core/DemoLayer.cpp", ":p")) | buffer src/App/Core/DemoLayer.cpp | else | edit src/App/Core/DemoLayer.cpp | endif
if &buftype ==# 'terminal'
  silent file src/App/Core/DemoLayer.cpp
endif
balt src/App/Core/DemoLayer.hpp
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
let s:l = 462 - ((13 * winheight(0) + 8) / 16)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 462
normal! 012|
wincmd w
argglobal
if bufexists(fnamemodify("src/Engine/Engine/Core/ModelManagerModule.hpp", ":p")) | buffer src/Engine/Engine/Core/ModelManagerModule.hpp | else | edit src/Engine/Engine/Core/ModelManagerModule.hpp | endif
if &buftype ==# 'terminal'
  silent file src/Engine/Engine/Core/ModelManagerModule.hpp
endif
balt src/App/Core/DemoLayer.cpp
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
let s:l = 1530 - ((29 * winheight(0) + 16) / 33)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 1530
normal! 03|
wincmd w
argglobal
if bufexists(fnamemodify("src/Engine/Engine/Renderer/RenderModule.cpp", ":p")) | buffer src/Engine/Engine/Renderer/RenderModule.cpp | else | edit src/Engine/Engine/Renderer/RenderModule.cpp | endif
if &buftype ==# 'terminal'
  silent file src/Engine/Engine/Renderer/RenderModule.cpp
endif
balt src/Engine/Engine/Core/ModelManagerModule.hpp
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
let s:l = 134 - ((6 * winheight(0) + 16) / 33)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 134
normal! 0
wincmd w
4wincmd w
exe '1resize ' . ((&lines * 16 + 35) / 70)
exe 'vert 1resize ' . ((&columns * 112 + 112) / 225)
exe '2resize ' . ((&lines * 16 + 35) / 70)
exe 'vert 2resize ' . ((&columns * 112 + 112) / 225)
exe '3resize ' . ((&lines * 16 + 35) / 70)
exe 'vert 3resize ' . ((&columns * 112 + 112) / 225)
exe '4resize ' . ((&lines * 16 + 35) / 70)
exe 'vert 4resize ' . ((&columns * 112 + 112) / 225)
exe '5resize ' . ((&lines * 33 + 35) / 70)
exe 'vert 5resize ' . ((&columns * 112 + 112) / 225)
exe '6resize ' . ((&lines * 33 + 35) / 70)
exe 'vert 6resize ' . ((&columns * 112 + 112) / 225)
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
