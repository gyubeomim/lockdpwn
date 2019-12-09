scripte utf-8
""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" 프로그램 기본 설정
""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

" 오리지널 Vi 와의 호환성을 없애고, Vim 만의 기능들을 쓸 수 있게 함.
set nocp

" 모든 옵션을 원래대로 복원
set all&

" 명령어 기록을 남길 갯수 지정
set hi=100

" 백스페이스 사용
set bs=indent,eol,start

" 인코딩 설정
" 문서를 읽을 때 BOM 을 자동으로 제거하려면, fencs 맨 앞에 ucs-bom 를 추가하세요.
" 한글 설정
set enc=utf8
set fenc=utf-8
set fencs=ucs-bom,utf-8,cp949,latin1
" set guifont=DejaVu\ Sans\ Mono\ for\ Powerline\ 11
set guifont=Source\ Code\ Pro\ 10
set guifontwide=Dotumche\ 10
"set relativenumber

" Toolbar, Menubar 숨기기
set guioptions-=T
set guioptions-=m


"" F4키는 모든 마킹을 지우고 F5키는 해당 단어를 하이라이팅합니다
map <F4> <Plug>MarkClear 
map <F5> <Plug>MarkSet


" for tmux-vim ABCD error fix
imap <ESC>oA <ESC>ki
imap <ESC>oB <ESC>ji
imap <ESC>oC <ESC>li
imap <ESC>oD <ESC>hi

"" 아두이노 파일을 읽습니다
au BufRead,BufNewFile *.pde set filetype=pde
au BufRead,BufNewFile *.ino set filetype=arduino

"" ROS filetype added
au BufRead,BufNewFile *.launch set filetype=xml





""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" 편집 기능 설정
""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

" 파일의 종류를 자동으로 인식
filetype on

" 커서의 위치를 항상 보이게 함.
set ru

" 완성중인 명령을 표시
set sc

" 줄 번호 표시
set nu

" 탭 크기 설정
set ts=4
set sw=4

" 탭 -> 공백 변환 기능 (사용 안함)
set noet
set sts=0

" 자동 줄바꿈 안함
"set nowrap

" 자동 들여쓰기 기능 설정
set autoindent
set cindent

" Hex viewer Setting
map <F2> :b<BS>%!xxd<CR>
map <F3> :b<BS>%!xxd -r<CR>

""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" 검색 기능 설정
""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

" 검색어 강조 기능
set hls
 
" 검색시 파일 끝에서 처음으로 되돌리기 안함
set nows

" 검색시 대소문자를 구별하지 않음
set ic

" 똑똑한 대소문자 구별 기능 사용
set scs
 
 
""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" 모양 설정
""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
 
" GUI 이면, 시작시 크기 설정
if has("gui_running")
   set lines=50
   set co=125
endif
 
" 추적 수준을 최대로
set report=0

" 항상 status 라인을 표시하도록 함.
set ls=2

" background 효과 dark.
set background=dark 

" colorscheme 세팅 
colorscheme gruvbox

 
""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" filetype 기능 & Syntax Highlighting 기능
""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

" 파일의 종류를 자동으로 인식
filet plugin indent on

" 알아서 하이라이팅
syntax on


""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" indent 설정
""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
 
" 자동 들여쓰기 사용
set ai
 
" 똑똑한 들여쓰기 사용
set si



""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" 편리한 기능
""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

" Tab 자동 완성시 가능한 목록을 보여줌
set wmnu

" 파일 탐색기 설정
let g:explVertical=1
let g:explSplitRight=1
let g:explStartRight=1
let g:explWinSize=20





""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" Coding용 설정
""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

" 블럭시작
"map  V
"map  y
"map  p

" F5 컴파일링 , F6 실행 , F8 함수보기
"map  :w!:!gcc % -o %<.out
"map  :!./%<.out
"map  K


" Shift+Enter로 아래줄로 커서 넘기기 기능 "
map <S-CR> <ESC>o
map! <S-CR> <ESC>o
"







""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" 기타 설정
""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

" 매크로 실행중에 화면을 다시 그리지 않음
set lz
 
" 프로그램 시작시 플러그인 로드
set lpl

" unix dos mac 줄 변경자 모두 다 읽을 수 있도록 합니다.
set ffs=unix,dos,mac

" 괄호를 입력할 때 일치하는 괄호를 표시한다
set showmatch

" 자동완성 기능 ctrl + p 키로 사용한다
filetype plugin on

" 파이썬 관련 설정들
let python_version_2 = 1              " python 2 문법을 따른다고 옵션을 설정합니다.
" let python_highlight_all = 1          " 모든 강조(색상) 기능을 켭니다.
let g:pydiction_location='/home/edward/.vim/pydiction/complete-dict'
let g:neocomplcache_enable_at_startup = 1

" 디버거 설정
let g:vim_debug_disable_mappings = 1

set tags=./tags,../tags,../../tags,../../../tags,../../../../tags




""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" 단축키 설정
""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

" Nerdtree 는 왼쪽에 생성한다
let NERDTreeWinPos = "left"


" NERDtree는 F7으로 시작하고 TlistToggle은 F8로 시작한다
nmap <F7> :NERDTreeToggle<CR>
nmap <F8> :TlistToggle<CR>


" ctags -R
" 함수나 변수를를 이동하는 단축키를 Alt + ., 로 변경합니다 
execute "set <M-.>=\e."
execute "set <M-,>=\e,"
nnoremap <M-.> <C-]>
nnoremap <M-,> <C-t>



" NerdTree 에서 
let NERDTreeQuitOnOpen=1

"miniBufexp
let g:miniBufExplMapWindowNavVim = 1  " Ctrl+[hjkl] 로 윈도우간 이동 가능
let g:miniBufExplMapWindowNavArrows = 1 " Ctrl+화살표로 윈도우간 이동 가능
let g:miniBufExplMapCTabSwitchBufs = 1 " Ctrl-Tab, Ctrl-Shift-Tab으로 버퍼간 스위칭... !! 짱이예욤!!
let g:miniBufExplModSelTarget = 1 


" Tag list가 사용하는 ctags의 경로 설정
let Tlist_Ctags_Cmd = "/usr/bin/ctags"
let Tlist_Inc_Winwidth = 0
let Tlist_Exit_OnlyWindow = 0
let Tlist_Auto_Open = 0

" Tag list 창을 오른쪽으로 생성
let Tlist_Use_Right_Window = 1

" ctags 파일의 경로를 입력합니다
set tags +=~/tags



" for vim-airline
set laststatus=2 " turn on bottom bar
set t_Co=256

" 버퍼 목록 켜기
let g:airline#extensions#tabline#enabled=1 " turn on buffer list
" 파일명만 출력
let g:airline#extensions#tabline#fnamemod=':t'
let g:airline_theme='zenburn'
let g:airline#extensions#tabline#enabled=1
let g:airline#extensions#tabline#left_sep=' '
let g:airline#extensions#tabline#left_alt_sep='|'
let g:airline_powerline_fonts=1


" YouCompleteMe
" .ycm_extra_conf.py가 있는 경로를 입력해야 합니다
let g:ycm_global_ycm_extra_conf = '~/.vim/bundle/youcompleteme/third_party/ycmd/cpp/ycm/.ycm_extra_conf.py' 
let g:ycm_confirm_extra_conf = 0 
let g:ycm_key_list_select_completion = ['', ''] 
let g:ycm_key_list_previous_completion = ['', ''] 
let g:ycm_autoclose_preview_window_after_completion = 1 
" let g:ycm_warning_symbol = '>*'
nnoremap <leader>g :YcmCompleter GoTo<CR>
" nnoremap <leader>gg :YcmCompleter GoToImprecise<CR>
nnoremap <leader>d :YcmCompleter GoToDeclaration<CR>
nnoremap <leader>t :YcmCompleter GetType<CR>
nnoremap <leader>p :YcmCompleter GetParent<CR>
" YCM의 Syntax Checking 기능을 끕니다
let g:ycm_show_diagnostics_ui = 0


" vim-sneak
map f <Plug>Sneak_s
map F <Plug>Sneak_S

" %s키로 단어를 바꾸던 기능을 커서 위에서 \s키를 누르면 동작하도록 설정합니다
nnoremap <Leader>s :%s/\<<C-r><C-w>\>/

" vim-rtags
"Out of box this plugin provides mappings. In order to use custom mappings the default mappings can be disabled:
let g:rtagsUseDefaultMappings = 1
"By default, search results are showed in a location list. Location lists are local to the current window. To use the vim QuickFix window, which is shared between all windows, set:
let g:rtagsUseLocationList = 0
"To implement 'return to previous location after jump' feature, internal stack is used. It is possible to set its maximum size (number of entries), default is 100:
let g:rtagsJumpStackMaxSize = 100

" vim-cpp-enhanced-highlight
""Highlighting of class scope is disabled by default. To enable set
let g:cpp_class_scope_highlight = 1
""Highlighting of member variables is disabled by default. To enable set
let g:cpp_member_variable_highlight = 1
""Highlighting of class names in declarations is disabled by default. To enable set
let g:cpp_class_decl_highlight = 1
""There are two ways to highlight template functions. Either
let g:cpp_experimental_simple_template_highlight = 1
""which works in most cases, but can be a little slow on large files. Alternatively set
let g:cpp_experimental_template_highlight = 1
""which is a faster implementation but has some corner cases where it doesn't work.
""Note: C++ template syntax is notoriously difficult to parse, so don't expect this feature to be perfect.
""Highlighting of library concepts is enabled by
let g:cpp_concepts_highlight = 1
""This will highlight the keywords concept and requires as well as all named requirements (like DefaultConstructible) in the standard library.
""Highlighting of user defined functions can be disabled by
let g:cpp_no_function_highlight = 1

""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" Vundle 설정 (플러그인 설정)
""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
set nocompatible
filetype off
 
set rtp+=~/.vim/bundle/vundle/
 
call vundle#rc()
Bundle 'gmarik/vundle'
Bundle 'git://git.wincent.com/command-t.git'

" 여러가지 플러그인들입니다 자세한 사용법은 구글링으로 알아보세요~~
Plugin 'The-NERD-tree'    " 유명한 플러그인으로 디렉토리간 이동을 쉽게 해주는 플러그인입니다 (파일탐색기 플러그인)
Plugin 'minibufexpl.vim'  " 버퍼를 보기 쉽게 만들어주는 플러그인  (gvim에서 Ctrl + Tab 으로 버퍼르 이동합니다)
Plugin 'ctags.vim'        " 함수나 구조체 클래스 변수 선언들을 참조하고 싶을 때 사용하는 플러그인입니다
Plugin 'snipMate'         " 명령어 자동완성 플러그인입니다 (inc + <tab> : #include <>)
Plugin 'tComment'         " visual 모드로 블록(구간)을 만든 뒤 Ctrl + _ + Ctrl + _ 키를 누르면 자동으로 주석이 입혀지는 플러그인
Plugin 'listtag'          " taglist와 비슷한 플러그인
Plugin 'taglist-plus'     " 열러있는 파일의 함수, 클래스, 변수 등의 정보를 볼 수 있게 해주는 플러그인
Plugin 'EasyMotion'       " 단어 간 이동을 쉽게해주는 플러그인입니다 (단축키 : \\w, \\b)
Plugin 'justinmk/vim-sneak' " 단어 간 이동을 쉽게 해주는 플로그인입니다2 (단축키 : s)
Plugin 'AutoClose'        " [] {} 등 괄호 입력시 자동으로 닫아주는 플러그인
Plugin 'Mark'  " 동일한 단어들을 마킹해주는 플러그인입니다  
			   " \m + 엔터 : 해당 단어를 마킹합니다 \n + 엔터 : 마킹을 해제합니다 

Plugin 'vim-airline/vim-airline'  " vim 화면을 좀 더 예쁘게 구성해주는 플러그인
Plugin 'vim-airline/vim-airline-themes'
Plugin 'lyuts/vim-rtags'
Plugin 'gtags.vim'
Plugin 'valloric/youcompleteme'   " C++, Python 등 언어의 자동완성 플러그인
Plugin 'airblade/vim-gitgutter'   " git project에서 수정,추가,제거된 라인을 표시해주는 gitgutter for Vim
Plugin 'octol/vim-cpp-enhanced-highlight' " C++ Code Highlight Package

" Plugin 'matchparenpp'     " 괄호에 커서를 가져다 대면 반대쪽 커서가 깜빡거리게 해주는 플러그인 (NOT USED)
filetype plugin indent on



" 자동으로 라인의 끝에서 다음라인으로 넘어가게 해주는 코드
set whichwrap+=h,l,<,>
set noswapfile


""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" End of File
""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
