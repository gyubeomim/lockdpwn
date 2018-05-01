;;; MELPA와 MARMALADE 저장소를 package list에 추가합니다
(require 'package)

(add-to-list 'package-archives'("marmalade" . "http://marmalade-repo.org/packages/") t)
(add-to-list 'package-archives '("gnu" . "http://elpa.gnu.org/packages/") t)
(add-to-list 'package-archives '("melpa" . "http://melpa.milkbox.net/packages/") t)
(add-to-list 'package-archives '("melpa" . "http://stable.melpa.org/packages/") t)
(add-to-list 'package-archives'("melpa" . "http://melpa.org/packages/") t)

(package-initialize) ;; You might already have this line
(setq gc-cons-threshold 100000000)
(setq inhibit-startup-message t)
(defalias 'yes-or-no-p 'y-or-n-p)
(defconst demo-packages
  '(
    anzu                   ;; 단어를 찾은 다음 교체하는 패키지 (단축키: M-%)
    duplicate-thing        ;; M-c 키로 현재 행을 그대로 복사하는 패키지
    helm                   ;; 파일목록이나 최근사용하 파일들, 버퍼를 쉽게 볼 수 있게 해주는 패키지
    helm-gtags
    helm-projectile
    helm-swoop
    clean-aindent-mode
    ws-butler              ;; whitespace를 알아서 제거해주는 패키지
    projectile
    undo-tree              ;; Alt + z 키를 통해 undo한 목록들을 볼 수 있는 패키지
    smartparens            ;; {}, [] 등 자동으로 괄호를 닫아주는 패키지
    auto-complete          ;; 단어 자동완성 패키지
    ecb                    ;; Emacs Code Browser의 약자로 코드를 상세하게 분석할 수 있게 해주는 패키지
    dtrt-indent            ;; 여러 파일들이 하나는 탭, 하나는 스페이스로 공백이 되어있을 경우 emacs가 알아서 처리하게 해주는 패키지
    google-c-style         ;; 들여쓰기 형식을 google style (구글 엔지니어들 스타일인듯)로 해주는 패키지
    etags                  ;; 함수나 여러 변수들의 선언을 찾아볼 수 있게 해주는 패키지
    key-chord              ;; 여러 쉬운 단축키들을 등록해주 수 있는 패키지 ( '..'키를 등록했습니다 )( 클래스 자동완성으로 등록 )
    solarized-theme        ;; solarized 테마
    rainbow-delimiters     ;; 괄호를 색색깔있게 바꿔줍니다
    jedi                   ;; 파이썬용 jedi 패키지 (terminal 창에서 pip install jedi epc pylint virtualenv 를 쳐줘야 정상작동하는듯 하다)
    arduino-mode           ;; 만약 아두이노를 사용한다면 추가해줍니다
    highlight-indentation  ;; 파이썬용 들여쓰기 라인을 보여주는 패키지 (Alt + l로 설정했다)
    ess                    ;; R 언어 전용 패키지입니다
    gtags                  ;; 함수나 여러 변수들의 선언을 찾아볼 수 있게 해주는 패키지
    highlight-symbol       ;; 같은 단어들 하이라이팅 해주는 패키지 (보기 좋게 글자를 색상을 칠해준다)
                           ;; highlight-symbol.el 파일에서
                           ;; highlight-symbol-colors ==> highlight-symbol-color로 수정한다 (색깔을 제대로 표시하지 못한다)
                           ;; 바로 적용이 안되므로 .elc 파일을 삭제하던지 아니면 M-x : byte-compile-file을 실시한다
    yasnippet              ;; 여러가지 자주 사용하는 구문들을 쉽게 사용할 수 있게 템플릿 형식으로 제공해주는 패키지
                           ;; ~/.emacs.d/elpa/yasnippet-.../snippets 에 있는 파일들을 ~/.emacs.d/snippets 에 넣어야 정상적으로 동작합니다
    hide-comnt             ;; 주석을 감췄다 보여줬다 하는 패키지 (F9 단축키)
    php-mode               ;; php 모드를 활성화합니다 (~/.emacs.d/elpa/php-mode.../php-mode.elc 파일이 잘못된 듯 합니다 이걸 삭제해주면 정상적으로 실행됩니다)
    flycheck               ;; 코드의 오류를 검사해주는 패키지
    robe                   ;; Ruby 관련된 패키지들 : 변수, 함수로 이동할 수 있는 패키지 : robe start를 입력해줘야 합니다
    inf-ruby               ;; Ruby 관련된 패키지들 : ruby shell (irb)를 사용할 수 있는 패키지
    rvm                    ;; Ruby 관련된 패키지들 : ruby version 관리해주는 패키지


    yaml-mode              ;; .yaml 구문을 하이라이팅해주는 패키지
    nxml                   ;; xml 구문들을 folding하기 위한 패키지
    lua-mode               ;; lua 언어를 하이라이팅해주는 패키지

    protobuf-mode          ;; .proto (google protocol buffer) 하이라이팅해주는 패키지

    csharp-mode            ;; C# 구문을 하이라이팅해주는 패키지

    multi-term             ;; 여러 터미널을 emacs에서 실행하 수 있게 해주는 패키지
    which-key              ;; 단축키들의 목록을 보여주는 패키지
    magit                  ;; emacs용 git 패키지 (Alt + \ 단축키)
    iedit                  ;; 단어들의 일괄편집을 해주는 패키지 (Alt + [ 단축키)
    wgrep                  ;; 프로젝트 내 grep 후 한개의 버퍼에서 모든 파일 수정하는 패키지 (grep창에서 C-c C-p 단축키)
    avy                    ;; 편집중 버퍼상의 빠른 이동   (Ctrl + = 단축키)
    swiper                 ;; 편집중 버퍼상의 빠른 이동2  (Ctrl + - 단축키)
    eyebrowse              ;; 워크 스페이스 관리 패키지 (다중 윈도우)

    elpy                   ;; jedi 모드 같이 python code navigation을 해주는 패키지
    markdown-mode          ;; markdown 구문을 하이라이팅해주는 패키지
    ein                    ;; emacs에서 Ipython Notebook를 사용하게 해주는 패키지
    org-bullets            ;; org-mode에서 마크 모양을 bullet 모양으로 해주는 패키지
    git-gutter             ;; 수정된 파일의 변경된 라인을 하이라이팅해주는 패키지
    mic-paren              ;; 괄호로 닫혀진 구문이 너무 길어서 한쪽 끝이 안보일 경우 line, number를 알려주는 패키지

    bm





    ;;flymd                  ;; markdown 구문을 preview 해주는 패키지 (.md 파일을 켠 다음 Ctrl + 4 단축키)
    ;; org-preview-html       ;; org-mode의 편집을 실시간으로 html로 나타내주는 패키지 (not used)
    ;; htmlize                ;; org-preview-html을 실행하기 위한 의존성 패키지
    ;; smart-mode-line
    ;; smart-mode-line-powerline-theme
    ;; powerline              ;; emacs 상태창을 예쁘게 꾸며주는 패키지
    ;; anaconda-mode ;; jedi 모드 같이 python code navigation을 해주는 패키지2
    ;;helm-ros  ;; ROS용 emacs 패키지 (not used)
    ;; autopair
    ;; function-args
    ;; company
    ;; comment-dwim-2
    ;; volatile-highlights
    ))

(defun install-packages ()
  "Install all required packages."
  (interactive)
  (unless package-archive-contents
    (package-refresh-contents))
  (dolist (package demo-packages)
    (unless (package-installed-p package)
      (package-install package))))

(install-packages)

;; this variables must be set before load helm-gtags
;; you can change to any prefix key of your choice
;; (setq helm-gtags-prefix-key "\C-cg")


;;===========================================================================
;;===========================================================================

;; 1. helm에 관한 코드들

(require 'helm-config)
(require 'helm-grep)
;;(require 'setup-helm)
;;(require 'setup-helm-gtags)
;;(require 'setup-cedet)
;;(require 'setup-editing)



;; The default "C-x c" is quite close to "C-x C-c", which quits Emacs.
;; Changed to "C-c h". Note: We must set "C-c h" globally, because we
;; cannot change `helm-command-prefix-key' once `helm-config' is loaded.
(global-set-key (kbd "C-c h") 'helm-command-prefix)
(global-unset-key (kbd "C-x c"))

(define-key helm-map (kbd "<tab>") 'helm-execute-persistent-action) ; rebihnd tab to do persistent action
;;(define-key helm-map (kbd "C-i") 'helm-execute-persistent-action) ; make TAB works in terminal
;;(define-key helm-map (kbd "C-z")  'helm-select-action) ; list actions using C-z

(define-key helm-grep-mode-map (kbd "<return>")  'helm-grep-mode-jump-other-window)
(define-key helm-grep-mode-map (kbd "n")  'helm-grep-mode-jump-other-window-forward)
(define-key helm-grep-mode-map (kbd "p")  'helm-grep-mode-jump-other-window-backward)

(when (executable-find "curl")
  (setq helm-google-suggest-use-curl-p t))

(setq
 helm-scroll-amount 4 ; scroll 4 lines other window using M-<next>/M-<prior>
 helm-ff-search-library-in-sexp t ; search for library in `require' and `declare-function' sexp.
 helm-split-window-in-side-p t ;; open helm buffer inside current window, not occupy whole other window
 helm-candidate-number-limit 500 ; limit the number of displayed canidates
 ;; helm-ff-file-name-history-use-recentf t
 helm-move-to-line-cycle-in-source t ; move to end or beginning of source when reaching top or bottom of source.
 helm-buffers-fuzzy-matching t          ; fuzzy matching buffer names when non-nil
 ;; useful in helm-mini that lists buffers

 )

(add-to-list 'helm-sources-using-default-as-input 'helm-source-man-pages)

(global-set-key (kbd "M-x") 'helm-M-x)
(global-set-key (kbd "M-y") 'helm-show-kill-ring)
(global-set-key (kbd "C-x b") 'helm-mini)
(global-set-key (kbd "C-x C-f") 'helm-find-files)
(global-set-key (kbd "C-h SPC") 'helm-all-mark-rings)
(global-set-key (kbd "C-c h o") 'helm-occur)



;;(global-set-key (kbd "C-c h C-c w") 'helm-wikipedia-suggest)

;;(global-set-key (kbd "C-c h x") 'helm-register)
;;(global-set-key (kbd "C-x r j") 'jump-to-register)

;;(define-key 'help-command (kbd "C-f") 'helm-apropos)
;;(define-key 'help-command (kbd "r") 'helm-info-emacs)
;;(define-key 'help-command (kbd "C-l") 'helm-locate-library)

;; use helm to list eshell history
(add-hook 'eshell-mode-hook
          #'(lambda ()
              (define-key eshell-mode-map (kbd "M-l")  'helm-eshell-history)))

;;; Save current position to mark ring
(add-hook 'helm-goto-line-before-hook 'helm-save-current-pos-to-mark-ring)

;; show minibuffer history with Helm
;;(define-key minibuffer-local-map (kbd "M-p") 'helm-minibuffer-history)
;;(define-key minibuffer-local-map (kbd "M-n") 'helm-minibuffer-history)

;;(define-key global-map [remap find-tag] 'helm-etags-select)
;;(define-key global-map [remap list-buffers] 'helm-buffers-list)

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; PACKAGE: helm-swoop                ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;; Locate the helm-swoop folder to your path
(require 'helm-swoop)

;; Change the keybinds to whatever you like :)
;;(global-set-key (kbd "C-c h o") 'helm-swoop)
;;(global-set-key (kbd "C-c s") 'helm-multi-swoop-all)

;; When doing isearch, hand the word over to helm-swoop
;;(define-key isearch-mode-map (kbd "M-i") 'helm-swoop-from-isearch)

;; From helm-swoop to helm-multi-swoop-all
;;(define-key helm-swoop-map (kbd "M-i") 'helm-multi-swoop-all-from-helm-swoop)

;; Save buffer when helm-multi-swoop-edit complete
;;(setq helm-multi-swoop-edit-save t)

;; If this value is t, split window inside the current window
;;(setq helm-swoop-split-with-multiple-windows t)

;; Split direcion. 'split-window-vertically or 'split-window-horizontally
;;(setq helm-swoop-split-direction 'split-window-vertically)

;; If nil, you can slightly boost invoke speed in exchange for text color
;;(setq helm-swoop-speed-or-color t)

(helm-mode 1)

(provide 'setup-helm)
(require 'helm-gtags)

(setq
 helm-gtags-ignore-case t
 helm-gtags-auto-update t
 helm-gtags-use-input-at-cursor t
 helm-gtags-pulse-at-cursor t
 helm-gtags-prefix-key "\C-cg"
 helm-gtags-suggested-key-mapping t
 )

;; Enable helm-gtags-mode in Dired so you can jump to any tag
;; when navigate project tree with Dired
(add-hook 'dired-mode-hook 'helm-gtags-mode)

;; Enable helm-gtags-mode in Eshell for the same reason as above
(add-hook 'eshell-mode-hook 'helm-gtags-mode)

;; Enable helm-gtags-mode in languages that GNU Global supports
(add-hook 'c-mode-hook 'helm-gtags-mode)
(add-hook 'c++-mode-hook 'helm-gtags-mode)
(add-hook 'java-mode-hook 'helm-gtags-mode)
(add-hook 'asm-mode-hook 'helm-gtags-mode)
(add-hook 'python-mode-hook 'helm-gtags-mode)

;; key bindings
;(define-key helm-gtags-mode-map (kbd "C-c g a") 'helm-gtags-tags-in-this-function)
;(define-key helm-gtags-mode-map (kbd "C-j") 'helm-gtags-select)
;(define-key helm-gtags-mode-map (kbd "M-.") 'helm-gtags-dwim)
;(define-key helm-gtags-mode-map (kbd "M-,") 'helm-gtags-pop-stack)
;(define-key helm-gtags-mode-map (kbd "C-c <") 'helm-gtags-previous-history)
;(define-key helm-gtags-mode-map (kbd "C-c >") 'helm-gtags-next-history)

;; gtags 관련해서 자동으로 파일 열고 저장할 때 gtags를 실행하도록 하는 함수들
(gtags-mode 1)
(add-hook 'prog-mode-hook 'gtags-mode)


(defun gtags-create-or-update ()
  "create or update the gnu global tag file"
  (interactive)
  (if (not (= 0 (call-process "global" nil nil nil " -p"))) ; tagfile doesn't exist?
      (let ((olddir default-directory)
            (topdir (read-directory-name
                     "gtags: top of source tree:" default-directory)))
        (cd topdir)
        (shell-command "gtags -q && echo 'created tagfile'")
        (cd olddir)) ; restore
    ;;  tagfile already exists; update it
    (with-temp-buffer
      (shell-command "global -u && echo 'updated tagfile'" t))))


;; (add-hook 'c-mode-common-hook
;;           (lambda ()
;;             (gtags-create-or-update)))
;; (add-hook 'c++-mode-common-hook
;;           (lambda ()
;;             (gtags-create-or-update)))


(defun gtags-root-dir ()
  "Return GTAGS Root directory or nil if doesn't exist"
  (with-temp-buffer
    (if (zerop (call-process "global" nil t nil "-pr"))
        (buffer-substring (point-min) (1- (point-max)))
      nil)))


;; gtags를 매번 저장할 때마다 업데이트하는 함수인듯, global -u 커맨드가 핵심커맨드인듯하다
(defun gtags-update-single (filename)
  "Update Gtags database for changes in a single file"
  (interactive)
  (with-temp-buffer
      (shell-command "global -u" t))
  (start-process "update-gtags" "update-gtags" "bash" "-c" (concat "cd " (gtags-root-dir) " ; gtags --single-update " filename )))


(defun gtags-update-current-file()
  (interactive)
  (defvar filename)
  (setq filename (replace-regexp-in-string (gtags-root-dir) "." (buffer-file-name (current-buffer))))
  (gtags-update-single filename)
  (message "Gtags updated for %s" filename)
  )


(defun gtags-update-hook()
  "Update GTAGS file incrementally upon saving a file"
  (when gtags-mode
    (when (gtags-root-dir)
      (gtags-update-current-file))))


(add-hook 'after-save-hook 'gtags-update-hook)


(provide 'setup-helm-gtags)



;;===========================================================================
;; 2. cedet에 관한 코드들 (auto-complete, cc-mode, semantic...)(단어 자동완성 관련된 코드들)


;;indent adjustment
;;(setq-default c-default-style "linux" c-basic-offset 4)
;;(setq-default tab-width 4 indent-tabs-mode t)
;;(define-key c-mode-base-map (kbd "RET") 'newline-and-indent)


;;autopair
;;(require 'autopair)
;;(autopair-global-mode 1)
;;(setq autopair-autowrap t)


;;auto-complete
;;start auto-complete with emacs
(require 'auto-complete)
;;do default config for auto-complete
(require 'auto-complete-config)
(ac-config-default)


(require 'cc-mode)
(require 'cedet)
(require 'semantic)
(require 'semantic/ia)
(require 'semantic/complete)

;; Enable EDE only in C/C++
(require 'ede)
(global-ede-mode)


;; 함수나 변수들을 찾아 이동할 때마다 로그를 기록합니다
(global-semantic-mru-bookmark-mode)


;; CC-mode
(add-hook 'c-mode-hook '(lambda ()
                          (setq ac-sources (append '(ac-source-semantic) ac-sources))
                          (local-set-key (kbd "RET") 'newline-and-indent)
                          (linum-mode t)
                          (semantic-mode t)))



;; Semantic
(global-semantic-idle-completions-mode t)
(semantic-mode 1)
;;(global-semantic-show-unmatched-syntax-mode t)
;;(global-semanticdb-minor-mode 1)
;;(global-semantic-idle-scheduler-mode 1)
;;(global-semantic-stickyfunc-mode 1)
;;(global-semantic-decoration-mode t)
;;(global-semantic-highlight-func-mode t)



;; 자동완성에 쓸 헤더 파일 경로 적는 예
;; 이것이 있어야 #include 한 헤더파일의 내용도 자동완성에 나타납니다.
(semantic-add-system-include "/usr/include" 'c-mode)
(semantic-add-system-include "/usr/include" 'c++-mode)




;; 자동완성 단축키는 클래스나 변수 앞에서 ,,를 빠르게 2번 눌러주면 됩니다 (',,' ==> semantic-ia-fast-jump)
;; C-c\C-j로 특정 구문의 선언문이나 함수를 확인합니다, C-c\C-s는 특정 구문의 선언문을 확인만 합니다
(defun alexott/cedet-hook ()
  (local-set-key "\C-c\C-j" 'semantic-ia-fast-jump)
  (local-set-key "\C-c\C-s" 'semantic-ia-show-summary))

(add-hook 'c-mode-common-hook 'alexott/cedet-hook)
(add-hook 'c-mode-hook 'alexott/cedet-hook)
(add-hook 'c++-mode-hook 'alexott/cedet-hook)



(provide 'setup-cedet)


;; ;; powerline 관련 코드
;; (column-number-mode 1)
;; (require 'powerline)
;; (setq powerline-default-separator-dir '(left . right))
;; (powerline-default-theme)






;;===========================================================================
;; 3. 기타 초기값 설정 코드들



;; GROUP: Editing -> Editing Basics

(setq global-mark-ring-max 5000         ; increase mark ring to contains 5000 entries
      mark-ring-max 5000                ; increase kill ring to contains 5000 entries
      mode-require-final-newline t      ; add a newline to end of file
      tab-width 4                       ; default to 4 visible spaces to display a tab
      )

(add-hook 'sh-mode-hook (lambda ()
                          (setq tab-width 4)))



;; 한글폰트 설정 (size 부분을 바꾸면 크기가 바뀝니다)
(set-fontset-font t 'hangul  (font-spec :name "NanumGothicCoding" :size 20))
;; (set-fontset-font "fontset-default" '(#x1100 . #xffdc)  '("NanumGothicCoding" . "unicode-bmp") )
;; (set-fontset-font "fontset-default" '(#xe0bc . #xf66e)  '("NanumGothicCoding" . "unicode-bmp") )

;; 선호하는 인코딩환경을 utf-8으로 설정합니다 (한글 문제)
;; 한글이 깨지는 경우
;; M-x revert-buffer-with-coding-system --> korea-iso-8bit 으로 설정해주면 정상적으로 보인다
(set-terminal-coding-system 'utf-8)
(set-keyboard-coding-system 'utf-8)
(set-language-environment "Korean")
(prefer-coding-system 'utf-8)


;; emacs --daemon 버전에서 M-x load-file 하거나 새로 켜는 경우 한글폰트를 적용하는 함수
(defun set_korean_font_after_loading (&optional frame)
  (set-fontset-font "fontset-default" 'hangul "NanumGothicCoding"))

(add-hook 'after-make-frame-functions 'set_korean_font_after_loading)



;; show whitespace in diff-mode
;; (add-hook 'diff-mode-hook (lambda ()
;;                             (setq-local whitespace-style
;;                                         '(face
;;                                           tabs
;;                                           tab-mark
;;                                           spaces
;;                                           space-mark
;;                                           trailing
;;                                           indentation::space
;;                                           indentation::tab
;;                                           newline
;;                                           newline-mark))
;;                             (whitespace-mode 1)))




;; Package: clean-aindent-mode
;; GROUP: Editing -> Indent -> Clean Aindent
(require 'clean-aindent-mode)
(add-hook 'prog-mode-hook 'clean-aindent-mode)


;; PACKAGE: dtrt-indent
(require 'dtrt-indent)
(dtrt-indent-mode 1)
(setq dtrt-indent-verbosity 0)

;; PACKAGE: ws-butler
(require 'ws-butler)
(add-hook 'c-mode-common-hook 'ws-butler-mode)
(add-hook 'text-mode 'ws-butler-mode)
(add-hook 'fundamental-mode 'ws-butler-mode)

;; Package: undo-tree
;; GROUP: Editing -> Undo -> Undo Tree
(require 'undo-tree)
(global-undo-tree-mode)




;; ;; Jedi settings
(require 'jedi)
;; It's also required to run "pip install --user jedi" and "pip
;; install --user epc" to get the Python side of the library work
;; correctly.
;; With the same interpreter you're using.

;; if you need to change your python intepreter, if you want to change it
;; (setq jedi:server-command
;; '("python2" "/home/andrea/.emacs.d/elpa/jedi-0.1.2/jediepcserver.py"))

;; 파이썬 모드 단축키를 설정합니다
(add-hook 'python-mode-hook
          (lambda ()
            (jedi:setup)
            (jedi:ac-setup)
            (define-key jedi-mode-map (kbd "C-c /") nil)
            ;; (local-set-key "\C-cd" 'jedi:show-doc)
            (local-set-key (kbd "M-,") 'jedi:goto-definition-pop-marker)
            (local-set-key (kbd "M-.") 'jedi:goto-definition)

            ;; 파이썬 선택한영역을 < 또는 > 쪽으로 이동합니다
            (local-unset-key (kbd "C-c >"))
            (local-unset-key (kbd "C-c <"))
            (local-set-key (kbd "C-<") 'python-indent-shift-left)
            (local-set-key (kbd "C->") 'python-indent-shift-right)
            ;;(local-set-key (kbd "C-;") 'highlight-indentation-mode)
            (setq indent-tabs-mode t)
            (setq python-indent-offset 4)
            (setq tab-width 4)

            (elpy-mode)                        ;; elpy mode 추가 (elpy-rgrep으로 reference를 찾을 수 있습니다)
            ))



;; elpy에서 사용하는 모든 keymap을 비활성화합니다
(setq elpy-mode-map nil)

;; elpy 모드가 실행되고 나서 설정하고 싶은 코드는 아래 작성한다
(eval-after-load "elpy" (lambda ()
                          ;; Alt + r 키로 reference를 찾아준다 (grep -r 명령어와 비슷하다고 한다)
                          (local-set-key (kbd "M-r") 'elpy-rgrep-symbol)

                          ;; elpy-mode에서 부가적으로 실행되는 모든 모듈들을 해제한다
                          (remove-hook 'elpy-modules 'elpy-module-flymake)
                          (remove-hook 'elpy-modules 'elpy-module-yasnippet)
                          (remove-hook 'elpy-modules 'elpy-module-highlight-indentation)
                          (remove-hook 'elpy-modules 'elpy-module-django)
                          (remove-hook 'elpy-modules 'elpy-module-company)
                          (remove-hook 'elpy-modules 'elpy-module-eldoc)
                          (remove-hook 'elpy-modules 'elpy-module-pyvenv)
                          (remove-hook 'elpy-modules 'elpy-module-sane-defaults)
                          ))


;; python에서 클래스 이름에 .을 입력하면 자동으로 멤버함수들의 목록을 출력해준다
(setq jedi:install-server t)
(setq jedi:complete-on-dot t)


;;ORG MODE==================================================================
;; DONE 시에 CLOSED timestamp를 사용하는 함수
(defun my/org-mode-hook ()
  (progn
    "Stop the org-level headers from increasing in height relative to the other text."
      (dolist (face '(org-level-1))
        (set-face-attribute face nil :weight 'normal :height 1.2))

      (dolist (face '(org-level-2
                      org-level-3
                      org-level-4
                      org-level-5))
        (set-face-attribute face nil :weight 'normal :height 0.98))
  ))

;; org 모드가 실행되고 나서 설정하고 싶은 코드는 아래 작성한다
;; "org" because C-h f org-mode RET says that org-mode is defined in org.el
(eval-after-load "org"
  '(progn
     ;; ed: 단축키 해제
     (define-key org-mode-map (kbd "<M-right>") nil) ; erasing a keybinding.
     (define-key org-mode-map (kbd "<M-left>") nil) ; erasing a keybinding.
     (define-key org-mode-map (kbd "<S-right>") nil)
     (define-key org-mode-map (kbd "<S-left>") nil)
     (define-key org-mode-map (kbd "<S-up>") nil)
     (define-key org-mode-map (kbd "<S-down>") nil)
     (define-key org-mode-map (kbd "C-k") nil)
     (define-key org-mode-map (kbd "C-y") nil)
     (define-key org-mode-map (kbd "q") nil)
     (define-key org-mode-map (kbd "<C-tab>") nil)
     (define-key org-mode-map (kbd "<C-S-left>") nil)
     (define-key org-mode-map (kbd "<C-S-right>") nil)
     (define-key org-mode-map (kbd "C-a") nil)

     ;; orgm
     ;; ed: 단축키 등록
     (define-key org-mode-map (kbd "<M-S-right>") 'org-shiftright)
     (define-key org-mode-map (kbd "<M-S-left>") 'org-shiftleft)
     (define-key org-mode-map (kbd "<M-S-up>") 'org-shiftup)
     (define-key org-mode-map (kbd "<M-S-down>") 'org-shiftdown)
     (define-key org-mode-map (kbd "<C-S-right>") 'org-metaright)
     (define-key org-mode-map (kbd "<C-S-left>") 'org-metaleft)
     (define-key org-mode-map (kbd "C-c a") 'org-agenda)
     ;; org capture 기능 단축키
     (define-key org-mode-map (kbd "C-c c") 'org-capture)
     ;; org-mode를 저장할 때마다 html로 preview를 보여주는 단축키
     (define-key org-mode-map (kbd "C-c w") 'org-preview-html/preview)
     ;; code ==> image Update 단축키
     (define-key org-mode-map (kbd "C-c q") 'org-toggle-inline-images)
     ;; org  ==> markdown export 단축키
     (define-key org-mode-map (kbd "C-c m") 'org-md-export-to-markdown)

     ;; DONE 시에 CLOSED timestamp를 사용하는 설정
     (setq org-log-done 'time)
     ;; org-mode에서 이미지를 보여주는 설정
     (setq org-startup-with-inline-images t)
     ;; src block에 syntax highlighting을 해주는 패키지
     (setq org-src-fontify-natively t)
     ;; org-mode를 시작할 때 unfold all
     ;;(setq org-inhibit-startup-visibility-stuff t)
     ;; org-mode에서 이미지 크기를 줄이기 위한 설정
     (setq org-image-actual-width nil)
     ;; tag가 달리는 위치 설정
     (setq org-tags-column 120)
     (setq org-startup-indented nil)
     ;; org-agenda view에서 하루가 지난 뒤까지 deadline이 없는 경우 계속 누적되지 않도록 설정
     (setq org-scheduled-past-days 0)


     ;; org-bullets 모드 활성화
     (add-hook 'org-mode-hook (lambda () (org-bullets-mode 1)))
     ;; wrap line
     (add-hook 'org-mode-hook (lambda () (setq truncate-lines nil)))
     ;; header 크기 변하지 않게
     (add-hook 'org-mode-hook 'my/org-mode-hook)

     (setq org-agenda-files (file-expand-wildcards "~/gitrepo/ims/org_files/*.org"))
     (setq org-default-notes-file "~/gitrepo/ims/org_files/index.org")
     (setq org-capture-templates '(("t" "Task" entry
                                    (file+headline "~/gitrepo/ims/org_files/index.org" "Task")
                                    "* TODO %i%? %^G")
                                   ("n" "Note" entry
                                    (file+headline "~/gitrepo/ims/org_files/index.org" "Note")
                                    "* %i%?")
                                   ("a" "Link" entry
                                    (file+headline "~/gitrepo/ims/org_files/index.org" "Link")
                                    "* %i%?")
                                   ("s" "Note for SqueezeSeg" entry
                                    (file+headline "~/gitrepo/ims/org_files/project_squeezeseg.org" "Note")
                                    "* %i%?")
                                   ("e" "Task for SqueezeSeg" entry
                                    (file+headline "~/gitrepo/ims/org_files/project_squeezeseg.org" "SqueezeSeg")
                                    "* TODO %i%?")
                                   ))
     (setq org-refile-targets '((org-agenda-files :level . 1)))
     (setq org-agenda-log-mode-items '(closed clock state))

))

;; C-c + / 키로 index.org 파일을 엽니다
(global-set-key (kbd "C-c /") (lambda() (interactive)(find-file "~/gitrepo/ims/org_files/index.org")))
;; C-c + l 키로 org mode에서 링크를 타기 위한 단축키를 설정합니다
(global-set-key (kbd "C-c l") 'org-store-link)
;; C-c + a 키로 어느곳에서나 agenda view를 열게합니다
(global-set-key (kbd "C-c a") 'org-agenda)
;; C-c + r 키로 어느곳에서나 capture 기능을 열게합니다
(global-set-key (kbd "C-c c") 'org-capture)
;;ORGEND=================================================================





;; python 단축키들 C-c,C-c 이나 C-c,C-z
;; PACKAGE: smartparens
(require 'smartparens-config)
;;(setq sp-base-key-bindings 'paredit)
;;(setq sp-autoskip-closing-pair 'always)
;;(setq sp-hybrid-kill-entire-symbol nil)
;;(sp-use-paredit-bindings)
(smartparens-global-mode t)
; (show-smartparens-global-mode t)


;; PACKAGE: comment-dwim
(global-set-key (kbd "M-'") 'comment-dwim)



;; Package: yasnippet
;; GROUP: Editing -> Yasnippet
;; ~/.emacs.d/elpa/yasnippet-.../snippets 에 있는 파일들을 ~/.emacs.d/snippets 에 넣어야 정상적으로 동작합니다
(require 'yasnippet)
(yas-global-mode 1)
;;(yas-load-directory "~/.emacs.d/elpa/yasnippet-20180102.1824/snippets/")



;; PACKAGE: anzu
;; GROUP: Editing -> Matching -> Isearch -> Anzu
(require 'anzu)
(global-anzu-mode)

;; M-% 키로 해당 buffer에서 특정 단어를 바꿉니다
(global-set-key (kbd "M-%") 'anzu-query-replace)
(global-set-key (kbd "C-M-%") 'anzu-query-replace-regexp)


;; PACKAGE: duplicate-thing
(require 'duplicate-thing)
(global-set-key (kbd "M-c") 'duplicate-thing)



;; PACKAGE : flycheck(구문 검사 패키지)를 사용합니다
(require 'flycheck)


;; (setq flycheck-python-pycompile-executable
;;       (or (executable-find "python")
;;           (executable-find "/usr/bin/python")
;;           (executable-find "/usr/local/bin/python")
;;           "python"))
;; (add-hook 'flycheck-python-pycompile-executable t)

;; (setq flycheck-python-flake8-executable
;;       (or (executable-find "flake8")
;;           (executable-find "/usr/bin/flake8")
;;           (executable-find "/usr/local/bin/flake8")
;;           "flake8"))

;; c++11에 안맞는 문법이 있을경우(range-based loop 등) 경고 메세지를 띄우는데 이를 무시한다
(add-hook 'c++-mode-hook (lambda () (setq flycheck-gcc-language-standard "c++11")))

;; emacs syntax warning + error 들을 무시합니다
(with-eval-after-load 'flycheck
  (setq-default flycheck-disabled-checkers '(emacs-lisp-checkdoc))
  )





;; PAKCAGE : which-key 모드를 활성화합니다
(require 'which-key)
(which-key-mode)


(require 'avy)


(require 'eyebrowse)
(eyebrowse-mode t)

;; C + 1,2,3을 누를때마다 워크스테이션을 생성한다
(setq eyebrowse-new-workspace t)

(setq eyebrowse-wrap-around t)
(setq eyebrowse-switch-back-and-forth t)
(setq eyebrowse-new-workspace nil)
(setq eyebrowse-mode-line-style (quote always))

;; eyebrowse 모드에서 C-1,2,3키로 워크스페이스를 변경합니다
(global-set-key (kbd "C-1") 'eyebrowse-switch-to-window-config-0)
(global-set-key (kbd "C-2") 'eyebrowse-switch-to-window-config-1)
(global-set-key (kbd "C-3") 'eyebrowse-switch-to-window-config-2)





;; PACKAGE : solarized theme를 활성화합니다
(require 'solarized-dark-theme)
(provide 'solarized-dark-theme)

(provide 'setup-editing)


;; rainbow-delimiters를 활성화합니다
(add-hook 'prog-mode-hook 'rainbow-delimiters-mode)


(require 'ein)
;; jupyter notebook을 킨 상태에서 브라우저가 자동으로 켜지는 옵션을 끕니다
(setq ein:jupyter-server-args (quote ("--no-browser")))
(setq ein:use-auto-complete t)
;; (setq ein:use-smartrep t)


;; ein 모드가 실행되고 난 후 세팅에 관한 코드
(eval-after-load "ein"
  '(progn
     (ein:ipynb-mode)
     ;; ed: ein 단축키 해제
     (define-key ein:notebook-mode-map (kbd "C-c i") nil)
     (define-key ein:notebook-mode-map (kbd "C-x C-s") nil)


     ;; ed: ein 단축키 등록
     (define-key ein:notebook-mode-map (kbd "C-w") 'ein:notebook-save-notebook-command)
     ))



;; markdown 언어를 볼 수 있게 해주는 패키지 (not used)
;; (require 'flymd)

;; ;; markdown을 파이어폭스에서 실행하도록 하는 코드
;; (defun my-flymd-browser-function (url)
;;    (let ((browse-url-browser-function 'browse-url-firefox))
;;      (browse-url url)))
;;  (setq flymd-browser-open-function 'my-flymd-browser-function)


;; highlight-indentation
(require 'highlight-indentation)
;;(add-hook 'python-mode-hook 'highlight-indentation-mode)
;;(add-hook 'js2-mode-hook 'highlight-indentation-mode)
(set-face-font 'highlight-indentation-face "Monospace")
(set-face-background 'highlight-indentation-face "#0d0d0d")
(set-face-attribute 'highlight-indentation-face nil :height 54)


;; Show the current function name in the header line
;; 현재 라인이 가리키고 있는 함수를 위에 상태창에 표시합니다
(require 'which-func)
;;(add-to-list 'which-func-modes 'ruby-mode)
;;(add-to-list 'which-func-modes 'cc-mode)
;;(add-to-list 'which-func-modes 'emacs-lisp-mode)
(setq which-func-unknown "n/a")
(which-function-mode)
(setq-default header-line-format
              '((which-func-mode ("" which-func-format " "))))
(setq mode-line-misc-info
      ;; We remove Which Function Mode from the mode line, because it's mostly
      ;; invisible here anyway.
      (assq-delete-all 'which-func-mode mode-line-misc-info))


;; iedit 패키지 활성화
(require 'iedit)

;; wgrep 패키지 활성화
(require 'wgrep)







;; Ruby 관련된 패키지 설정들
;; 1. 처음 루비 파일을 연 다음 C-c C-s를 누르면 inf-ruby (irb) 창이 열립니다
;; 2. 이 때 다시 한 번 C-c C-s를 눌러 robe start 명령어를 실행합니다
;; 3. C-c C-c 를 눌러 irb 창을 닫습니다.
;; 그 다음부턴 원하는 함수, 변수의 자동완성과 jump 기능을 사용할 수 있습니다
(require 'rvm)
(rvm-use-default)
(defadvice inf-ruby-console-auto
    (before activate-rvm-for-robe activate)
  (rvm-activate-corresponding-ruby))

;;(eval-after-load 'company
;;  '(push 'company-robe company-backends))

;;(require 'rinari)
;;(require 'ido)
;;(ido-mode)
;;(require 'rhtml-mode)
;;(global-rinari-mode)
;;(add-hook 'rhtml-mode-hook
;;	  (lambda () (rinari-launch)))
;;(setq rinari-tags-file-name "TAGS")
;;(add-hook 'ruby-mode-hook 'rinari-launch)

(add-hook 'ruby-mode-hook
          (lambda ()
;;(local-set-key (kbd "TAB") 'company-robe)
            (local-set-key (kbd "C-c C-s") 'inf-ruby-console-auto)))

(add-hook 'inf-ruby-mode-hook
          (lambda()
            (local-set-key (kbd "C-c C-s") 'robe-start)
            ;; (local-set-key (kbd "C-c C-c") 'delete-window)
            ))

(autoload 'inf-ruby-minor-mode "inf-ruby" "Run an inferior Ruby process" t)
;;(add-hook 'ruby-mode-hook 'company-mode)
(add-hook 'ruby-mode-hook 'inf-ruby-minor-mode)
(add-hook 'ruby-mode-hook 'robe-mode)
(add-hook 'robe-mode-hook 'ac-robe-setup)






;;===========================================================================
;;===========================================================================

;; function-args
;; (require 'function-args)
;; (fa-config-default)
;; (define-key c-mode-map  [(tab)] 'company-complete)
;; (define-key c++-mode-map  [(tab)] 'company-complete)

;; company
;;(require 'company)
;;(add-hook 'after-init-hook 'global-company-mode)
;;(delete 'company-semantic company-backends)
;;(define-key c-mode-map  [(tab)] 'company-complete)
;;(define-key c++-mode-map  [(tab)] 'company-complete)
;; (define-key c-mode-map  [(control tab)] 'company-complete)
;; (define-key c++-mode-map  [(control tab)] 'company-complete)

;; company-c-headers
;;(add-to-list 'company-backends 'company-c-headers)


;; Package: clean-aindent-mode
(require 'clean-aindent-mode)
(add-hook 'prog-mode-hook 'clean-aindent-mode)

;; Package: dtrt-indent
(require 'dtrt-indent)
(dtrt-indent-mode 1)

;; Package: ws-butler
(require 'ws-butler)
(add-hook 'prog-mode-hook 'ws-butler-mode)



;; Package: projejctile
(require 'projectile)
(projectile-global-mode)
(setq projectile-enable-caching t)

(require 'helm-projectile)
(helm-projectile-on)
(setq projectile-completion-system 'helm)
(setq projectile-indexing-method 'alien)




;; emacs 25.1 버전에서는 왜그런지 모르지만 이 부분에서 에러난다
;; Package: arduino-mode
;;(require 'arduino-mode)
;; arduino 아두이노 모드에 자동완성 기능을 추가합니다
;;(add-hook 'arduino-mode-hook 'auto-complete-mode)
;;(add-hook 'arduino-mode-hook
;;          (lambda ()
;;            (local-set-key (kbd "M-,") 'pop-tag-mark)))

;; 태그는 etags 기능을 써야하는듯 합니다 terminal >> etags *.ino

;; highlight symbol mode를 활성화합니다
(require 'highlight-symbol)
(add-hook 'c-mode-hook 'highlight-symbol-mode)
(add-hook 'c++-mode-hook 'highlight-symbol-mode)
(add-hook 'python-mode-hook 'highlight-symbol-mode)
(add-hook 'prog-mode-hook 'highlight-symbol-mode)


;; hs-minor-mode 를 활성화합니다. 코드를 접엇다 펼쳤다 하는 모드
(add-hook 'prog-mode-hook 'hs-minor-mode)


;; multi-term 패키지를 활성화한다
(require 'multi-term)
(setq multi-term-program "/bin/bash")

;; C + v 키로 multi-term 모드에서 붙여넣기를 설정한다
;; multi-term은 term-mode를 사용하므로
;; (term-mode)
(add-hook 'term-mode-hook
          (lambda ()
            ;; cua-mode에서 c-v 키를 바인딩하고 있어서 다른 키들이 안먹히고 있었다
            (cua-mode -1)
            ;; (local-unset-key (kbd "C-y"))
            (define-key term-raw-map (kbd "C-b") nil)
            (define-key term-raw-map (kbd "C-y") nil)
            (define-key term-raw-map (kbd "C-q") nil)
            (define-key term-raw-map (kbd "<S-insert>") nil)

            (define-key term-raw-map (kbd "C-v") 'term-paste)
            (define-key term-raw-map (kbd "C-b") 'helm-for-files)

            (define-key term-mode-map (kbd "C-v") 'term-paste)
            (define-key term-mode-map (kbd "C-b") 'helm-for-files)
            ))


;; protobuf-mode를 활성화한다
(require 'protobuf-mode)


;;(require 'helm-ros)
;;(global-helm-ros-mode t)

;;===========================================================================
;; Variable Customizing
(custom-set-variables
 ;; custom-set-variables was added by Custom.
 ;; If you edit it by hand, you could mess it up, so be careful.
 ;; Your init file should contain only one such instance.
 ;; If there is more than one, they won't work right.
 '(ansi-color-faces-vector
   [default default default italic underline success warning error])
 '(ansi-color-names-vector
   ["#242424" "#e5786d" "#95e454" "#cae682" "#8ac6f2" "#333366" "#ccaa8f" "#f6f3e8"])
 '(auto-hscroll-mode t)
 '(column-number-mode t)
 '(cua-mode t nil (cua-base))
 '(custom-enabled-themes (quote (solarized)))
 '(custom-safe-themes
   (quote
    ("a27c00821ccfd5a78b01e4f35dc056706dd9ede09a8b90c6955ae6a390eb1c1e" "84d2f9eeb3f82d619ca4bfffe5f157282f4779732f48a5ac1484d94d5ff5b279" "962dacd99e5a99801ca7257f25be7be0cebc333ad07be97efd6ff59755e6148f" "a8245b7cc985a0610d71f9852e9f2767ad1b852c2bdea6f4aadc12cce9c4d6d0" "8db4b03b9ae654d4a57804286eb3e332725c84d7cdab38463cb6b97d5762ad26" default)))
 '(display-time-mode t)
 '(ecb-layout-name "right1")
 '(ecb-layout-window-sizes
   (quote
    (("right1"
      (ecb-directories-buffer-name 0.3151515151515151 . 0.20833333333333334)
      (ecb-sources-buffer-name 0.3151515151515151 . 0.2916666666666667)
      (ecb-methods-buffer-name 0.3151515151515151 . 0.4791666666666667))
     ("left14"
      (ecb-directories-buffer-name 0.271523178807947 . 0.7317073170731707)
      (ecb-history-buffer-name 0.271523178807947 . 0.24390243902439024)))))
 '(ecb-options-version "2.50")
 '(ecb-tip-of-the-day nil)
 '(elpy-modules
   (quote
    (elpy-module-company elpy-module-eldoc elpy-module-flymake elpy-module-pyvenv elpy-module-highlight-indentation elpy-module-yasnippet elpy-module-django elpy-module-sane-defaults)))
 '(flycheck-clang-include-path nil)
 '(flycheck-cppcheck-include-path nil)
 '(flycheck-gcc-include-path nil)
 '(flycheck-gcc-includes nil)
 '(flycheck-gcc-warnings nil)
 '(git-gutter:added-sign "+ ")
 '(git-gutter:deleted-sign "- ")
 '(git-gutter:modified-sign "▸ ")
 '(helm-bookmark-show-location t)
 '(org-agenda-files
   (quote
    ("~/gitrepo/ims/org_files/180327_emacs_useful_functions.org" "~/gitrepo/ims/org_files/index.org" "~/gitrepo/ims/org_files/project_squeezeseg.org" "~/gitrepo/ims/org_files/180318_deeplearning_network_models.org" "~/gitrepo/ims/org_files/180407_deeplearning_core_concept.org" "~/gitrepo/ims/org_files/180407_deeplearning_tensorflow.org" "~/gitrepo/ims/org_files/180423_cmake_for_edward.org" "~/gitrepo/ims/org_files/180427_jupyter_notebook_remote.org" "~/gitrepo/ims/org_files/project_cartographer.org")))
 '(org-bullets-bullet-list (quote ("●" "◉" "▸" "✸")))
 '(org-hide-emphasis-markers t)
 '(org-scheduled-delay-days 0)
 '(package-selected-packages
   (quote
    (mic-paren htmlize org-preview-html jedi-direx yasnippet ws-butler undo-tree solarized-theme smartparens rainbow-delimiters key-chord jedi highlight-indentation helm-swoop helm-projectile helm-gtags google-c-style flycheck ess ecb duplicate-thing dtrt-indent clean-aindent-mode arduino-mode anzu)))
 '(safe-local-variable-values
   (quote
    ((eval font-lock-add-keywords nil
           (\`
            (((\,
               (concat "("
                       (regexp-opt
                        (quote
                         ("sp-do-move-op" "sp-do-move-cl" "sp-do-put-op" "sp-do-put-cl" "sp-do-del-op" "sp-do-del-cl"))
                        t)
                       "\\_>"))
              1
              (quote font-lock-variable-name-face))))))))
 '(sml/mode-width
   (if
       (eq
        (powerline-current-separator)
        (quote arrow))
       (quote right)
     (quote full)))
 '(sml/pos-id-separator
   (quote
    (""
     (:propertize " " face powerline-active1)
     (:eval
      (propertize " "
                  (quote display)
                  (funcall
                   (intern
                    (format "powerline-%s-%s"
                            (powerline-current-separator)
                            (car powerline-default-separator-dir)))
                   (quote powerline-active1)
                   (quote powerline-active2))))
     (:propertize " " face powerline-active2))))
 '(sml/pos-minor-modes-separator
   (quote
    (""
     (:propertize " " face powerline-active1)
     (:eval
      (propertize " "
                  (quote display)
                  (funcall
                   (intern
                    (format "powerline-%s-%s"
                            (powerline-current-separator)
                            (cdr powerline-default-separator-dir)))
                   (quote powerline-active1)
                   (quote sml/global))))
     (:propertize " " face sml/global))))
 '(sml/pre-id-separator
   (quote
    (""
     (:propertize " " face sml/global)
     (:eval
      (propertize " "
                  (quote display)
                  (funcall
                   (intern
                    (format "powerline-%s-%s"
                            (powerline-current-separator)
                            (car powerline-default-separator-dir)))
                   (quote sml/global)
                   (quote powerline-active1))))
     (:propertize " " face powerline-active1))))
 '(sml/pre-minor-modes-separator
   (quote
    (""
     (:propertize " " face powerline-active2)
     (:eval
      (propertize " "
                  (quote display)
                  (funcall
                   (intern
                    (format "powerline-%s-%s"
                            (powerline-current-separator)
                            (cdr powerline-default-separator-dir)))
                   (quote powerline-active2)
                   (quote powerline-active1))))
     (:propertize " " face powerline-active1))))
 '(sml/pre-modes-separator (propertize " " (quote face) (quote sml/modes)))
 '(sp-base-key-bindings nil))


;; Custom Face + 영어폰트 설정  (height 부분을 바꾸면 크기가 바뀝니다)
(custom-set-faces
 ;; custom-set-faces was added by Custom.
 ;; If you edit it by hand, you could mess it up, so be careful.
 ;; Your init file should contain only one such instance.
 ;; If there is more than one, they won't work right.
 '(default ((t (:family "Source Code Pro" :foundry "PfEd" :slant normal :weight normal :height 136 :width normal))))
 '(diff-added ((t (:background "dark olive green" :foreground "gray"))))
 '(diff-hunk-header ((t (:inherit diff-header :background "black"))))
 '(diff-refine-added ((t (:background "nil"))))
 '(diff-refine-changed ((t (:background "nil"))))
 '(diff-refine-removed ((t (:background "nil"))))
 '(diff-removed ((t (:background "red4" :foreground "gray"))))
 '(ein:cell-input-area ((t (:background "black"))))
 '(font-lock-comment-delimiter-face ((t (:foreground "forest green"))))
 '(font-lock-comment-face ((t (:foreground "forest green"))))
 '(hi-blue ((t (:background "blue" :foreground "#5c95b9"))))
 '(hi-blue-b ((t (:background "cyan" :foreground "#49a19a" :weight bold))))
 '(hi-green ((t (:background "green" :foreground "#8c9d50"))))
 '(hi-green-b ((t (:background "chartreuse" :foreground "#899b30" :weight bold))))
 '(hi-pink ((t (:background "pink" :foreground "#b36b91"))))
 '(hi-red-b ((t (:background "orange" :foreground "#c65351" :weight bold))))
 '(hi-yellow ((t (:background "yellow" :foreground "#a39450"))))
 '(highlight ((t (:background "grey"))))
 '(magit-diff-hunk-heading ((t (:background "black"))))
 '(magit-diff-hunk-heading-highlight ((t (:background "black"))))
 '(org-block ((t (:background "gray13" :foreground "dark gray"))))
 '(org-block-begin-line ((t (:background "gray13" :foreground "gray13" :weight bold))))
 '(org-block-end-line ((t (:background "gray13" :foreground "gray13" :weight bold))))
 '(org-link ((t (:foreground "#b58900" :box nil :underline t :weight bold))))
 '(org-meta-line ((t (:foreground "#586e75" :slant normal))))
 '(org-tag ((t (:background "black" :weight bold :height 0.9)))))



;; 다중모니터에서 C-x-5-2를 통해서 새로운 frame을 생성한 다음에 모니터가 작아서 폰트사이즈가 작은 경우 폰트크기를 크게하기 위해 설정한 함수
;; https://stackoverflow.com/questions/24705984/increase-decrease-font-size-in-an-emacs-frame-not-just-buffer
(defun zoom-frame (&optional n frame amt)
  "Increase the default size of text by AMT inside FRAME N times.
  N can be given as a prefix arg.
  AMT will default to 10.
  FRAME will default the selected frame."
  (interactive "p")
  (let ((frame (or frame (selected-frame)))
        (height (+ (face-attribute 'default :height frame) (* n (or amt 5)))))
    (set-face-attribute 'default frame :height height)
      (message "Set frame's default text height to %d." height)))

;;(when (called-interactively-p)) 생략

(defun zoom-frame-out (&optional n frame amt)
  "Call `zoom-frame' with -N."
  (interactive "p")
  (zoom-frame (- n) frame amt))


;; C-c + i/o 키로 새로 생성한 프레임의 폰트가 작을 경우 크기를 키우거나 줄일 수 있다
(global-set-key (kbd "C-c i") 'zoom-frame)
(global-set-key (kbd "C-c o") 'zoom-frame-out)





;; [+] Font Lists
;; [+] 폰트 목록은 *scratch* 에서 (print (font-famliy-list)) 를 입력하고 C-x C-e를 입력하면 된다
;; 1. Noto Mono for Powerline
;; 2. DeJaVu Sans Mono


;;GUI 환경에서 시작 시 창 화면 최대화 하기
(add-to-list 'default-frame-alist '(fullscreen . maximized))(add-to-list 'default-frame-alist '(height . 31))
(add-to-list 'default-frame-alist '(width . 100))
(set-frame-position (selected-frame) 0 0)



;; 매칭되는 괄호 강조하기
;;show paren mode
(show-paren-mode 1)
(setq show-paren-delay 0)
;; (setq show-paren-style 'mixed)

;; 시작화면 스킵하고 기본 모드 설정하기
;;skip startup screen and specify default mode
(setq inhibit-startup-screen t)
;;(setq initial-major-mode 'scheme-mode)


;; 상태표시줄에 시간표시하기
;;show time on status bar
(display-time)


;; 몇가지 유용한 설정
;;#useful settings
(transient-mark-mode t)
(global-set-key [C-kanji] 'set-mark-command)



;;파일 편집 위치 기억
(require 'saveplace)
(setq-default save-place t)
(setq save-place-file     "~/_places.sav")


;;최근 파일 접근
(require 'recentf)
(recentf-mode 1)
(setq recentf-max-menu-items 20) ; 최근 파일 목록 수



;;GUI 환경에서 줄 간격 조절
(setq-default line-spacing 1)

;;파일이 수정되었을 때 자동으로 다시 읽어들이도록 하는 설정
(global-auto-revert-mode t)


;;linum 모드 켜기 (줄번호 표시하기)
(global-linum-mode 1)


;; 계산기 자릿수 분리기호 삽입 calc EMACS 기본 계산기 모드에서 자릿수 분리기호 삽입
(setq calc-group-digits t)


;;status bar에 시간 표시기능.
(display-time)


;;시작 화면 메세지 끄기
(setq inhibit-startup-message t)
(setq initial-scratch-message "")


;;시작 모드를 text모드로 시작하기. 보통은 LISP Interaction 상태.
(setq initial-major-mode 'text-mode)


;;블럭 선택부분 색상 반전시키기
(setq-default transient-mark-mode t)


;;status bar에 줄 번호, 칼럼 번호 표시
(setq line-number-mode t)
(setq column-number-mode t)

;;백업파일 만들지 않기, ( #Readmin.md# )
(setq make-backup-files nil)

;;자동 저장 기능 끄기  ( Readme.md~ )
(setq auto-save-default nil)

;; interlocking 파일 생성 끄기 ( .#Readme.md )
(setq create-lockfiles nil)

;; 모든 자동저장, 백업파일을 tmp 폴더에 만들기
;; store all backup and autosave files in the tmp dir
(setq backup-directory-alist
      `((".*" . ,temporary-file-directory)))
(setq auto-save-file-name-transforms
      `((".*" ,temporary-file-directory t)))


;;하단 스크롤시에 빈 줄 추가 하지 않기.
;;보통은 스크롤이 맨 끝까지 가면 자동으로 빈 줄이 추가 된다.
(setq next-line-add-newlines nil)


;;하단 스크롤시 1줄씩만 스크롤 되도록 하기.
(setq scroll-step 1)


;;페이지 넘길 때 3줄은 포함.
(setq next-screen-context-lines 3)


;;찾기 기능에서 하이라이트 설정
(setq search-highlight t)


;;상단 메뉴 숨기기
(menu-bar-mode 0)

;;도구 모음 숨기기
(tool-bar-mode 0)

;; scroll bar 끄기
(scroll-bar-mode 0)



;; word wrap 강제 줄바꿈 auto-fill-mode 이기능은 특정 칼럼 이상 넘어가면
;; 자동으로 강제 줄바꿈 해주는 기능인데, 대량의 텍스트 문서를 워드프로세서로 편집 할 경우


;;강제줄바꿈 기능이 오히려 편집의 불편함을 주기 때문에 지금은 사용하지 않는다.
;; (setq-default auto-fill-function 'do-auto-fill)


;;줄 바꿈 칼럼수 설정.
(setq-default fill-column 75)




;;grep 기능 옵션 설정 리눅스 에서는 grep을 쓰고 윈도우 환경에서는 find를 쓴다.
;;뒤에 붙여주는 인자도 수정 할 수 있다. 보통 텍스트 파일을 검색하므로 txt를 붙여 주었다.
;;(setq grep-command "grep -n \"\" *.txt")
;;(setq grep-command "find \"\" *.txt")


;;날짜 삽입하기. 편집 할 때
(defun today ()
  "Insert Date YYYY-MM-DD"
  (interactive)
  (insert (format-time-string "%Y-%m-%d")))


;;날짜 삽입 단축키 (편집 시)
(global-set-key "\M-\pd" 'today)


;;날짜 삽입하기. 저장 할 때
(defun today1 ()
  "Insert Date YYMMDD00"
  (interactive)
  (insert (format-time-string "%y%m%d00")))



;;Dired모드에서 디렉토리 우선 정렬로 보기 (기본은 지원 안함)
(defun sof/dired-sort ()
  "Dired sort hook to list directories first."
  (save-excursion
    (let (buffer-read-only)
      (forward-line 2)
      (sort-regexp-fields t "^.*$" "[ ]*." (point) (point-max))))
  (and (featurep 'xemacs)
       (fboundp 'dired-insert-set-properties)
       (dired-insert-set-properties (point-min) (point-max)))
  (set-buffer-modified-p nil))
(add-hook 'dired-after-readin-hook 'sof/dired-sort)


;; dired mode에서 여러 단축키들을 설정하는 코드
(eval-after-load "dired" '(progn
      ;; dired mode : Move to the parent directory
      (define-key dired-mode-map "a"
        (lambda ()
          (interactive)
          (find-alternate-file "..")))

      ;; dired mode 관련 단축키들을 추가했다
      ;; dired mode : Emacs's adaption of find
      (define-key dired-mode-map "F" 'find-name-dired);

      ;; dired mode : Move up and down
      (define-key dired-mode-map "j" 'dired-next-line)
      (define-key dired-mode-map "k" 'dired-previous-line);

      ;; dired mode : Jump to a file with ido
      (define-key dired-mode-map "i" 'ido-find-file)

      ;; dired mode 에서 chmod를 바로 수행하고 싶을 경우 M키를 눌러서 합니다
      (define-key dired-mode-map "M" 'chmod)

      ;; dired mode 에서 /키를 검색키로 설정합니다
      (define-key dired-mode-map "/" 'isearch-forward)
))



;; 엔터 입력시 자동 들여쓰기 다른 방법
(load "cc-mode")
(define-key c++-mode-map "\r" 'reindent-then-newline-and-indent)
(define-key c-mode-map "\r" 'reindent-then-newline-and-indent)
(define-key java-mode-map "\r" 'reindent-then-newline-and-indent)


;; 엔터 입력시 자동 들여쓰기 다른 방법
;;(require 'cc-mode)
;;(define-key c-mode-base-map (kbd "RET") 'newline-and-indent)


;; { , ; 입력시 자동 줄 추가
;;(add-hook 'c-mode-common-hook '(lambda () (c-toggle-auto-state 1)))



;;emacs tab 설정
(setq c-basic-offset 4
      tab-width 4
      indent-tabs-mode t)
;;(add-hook 'c-mode-common-hook '(lambda () (c-toggle-auto-state 1)))


;; 탭 대신 공백 넣기
(setq-default indent-tabs-mode nil)


;; c-toggle-auto-state 기능에 backspace입력시 모든 공백(줄 바꿈 포함) 삭제
;;(add-hook 'c-mode-common-hook '(lambda () (c-toggle-auto-hungry-state 1)))


;;최근 사용된 word list를 가지고, 자동 완성구현, 3글자 이후에M-RET
(dynamic-completion-mode)


(require 'mic-paren) ; loading
(paren-activate)     ; activating
;; offscreen parenthesis의 경우 반대쪽 괄호의 라인정보를 알려준다
(setq paren-message-show-linenumber "absolute")



;;==============================================================================
;; prog mode 설정하기(emacs 24+ only)
;; (참조 : http://www.gnu.org/software/emacs/manual/html_node/elisp/Basic-Major-Modes.html)
;;==============================================================================
;; prog mode 에 설정을 해두면 각각의 언어에서 별도 설정을 하지 않아도 된다.
;; prog mode 를 상속하지 않는 경우 별도로 설정해야 한다.

(defun set-default-programming-style ()
  ;; -------------------------------------------------------------------------
  ;; 엔터 입력시 들여쓰기
  (local-set-key (kbd "RET") 'newline-and-indent)
  ;; -------------------------------------------------------------------------
  ;; 탭키를 일반 에디터에서 작동하는 방식으로 변경
  ;; (local-set-key (kbd "TAB") 'self-insert-command)

  ;; 탭키 입력시 영역지정되어 있으면 영역 들여쓰기. 영역없으면 탭키.
  (local-set-key (kbd "TAB") 'indent-block)

  ;; 들여쓰기 할 때 실제 탭문자 입력
  (setq indent-tabs-mode t)

  ;; 탭 사이즈 4
  (setq tab-width 4)
  ;; -------------------------------------------------------------------------
  ;; 줄번호 표시
  (linum-mode 1)

  ;; -------------------------------------------------------------------------
  ;; 커서라인 표시
  ;;(global-hl-line-mode)
  )







;;---------------------------------------------------------------

;; gdb 다중창 설정
(setq gdb-many-windows t)

;; compile 명령어 수정 (c++일 경우 g++, c일 경우 gcc로 해주면 됩니다)
(setq compile-command "g++ -std=c++14 -g -o ")


;; ECB Emacs Code Browser 활성화
(require 'ecb)

;; ECB tree view에서 F3 키가 ecb-show-help로 키바인딩되어있는 것을 해제해준다
(add-hook 'ecb-common-tree-buffer-after-create-hook
          (lambda ()
            (local-unset-key [f3])
                             ))

(add-hook 'ecb-directories-buffer-after-create-hook
          (lambda ()
            (local-unset-key [f3])
            ))


;; etags 사용법
;; 1. M-x compile RET etags *.cpp *.h RET해 주고
;; 2. M-x visit-tags-table 해 주고
;; 3. 원하는 함수명 위에 커서 놓고 M-. 해 주고 엔터치면 함수 정의로 이동한다.
;; 4. 되돌아 가려면 M-*
;; 5. 다른 디렉토리도 적용하면
;; find . -name "*.[chCH]" -print | etags -
;; 또 다른 명령어
;; find /usr/include/ -name "*.[ch]" -print | etags - *.cpp *.h
;; find /usr/include/ -name "*.[ch]" -print | etags - *.[ch]
;; -------------------------------------------------------------
;; gtags 사용 이후론 잘 안쓴다 gtags가 알아서 해주는듯


;; 180122_월
;; emacs 25.x 이후로 xref-find-definition을 (xx) 키로 key-chord 설정해놨다
;;                  이를 사용하려면 TAGS 파일이 필요한데 이를 위해 또 etags를 써야하는듯 :-)
;; find ./ -print | etags - *.{cpp,h,c,cc,hpp,py,el} 같이 쓰면 여러 확장자를 필터링할 수 있다



;; path를 입력하면 그곳에서 TAGS 파일을 생성해주는 함수
(defun make_TAGS_file (&optional path)
  "make TAGS file"
  (interactive (list (read-file-name "path to make TAGS : " default-directory)))
  (with-temp-buffer
  (shell-command (concat "find " (concat path) (concat " -print | etags - *.{cpp,h,c,cc,hpp,py,el}")) t)))


;; M-? 키를 이용해 TAGS file을 만든다.
;;(define-key c++-mode-map "\M-e" nil)
;;(define-key c-mode-map "\M-e" nil)
(global-set-key (kbd "M-?") 'make_TAGS_file)

;; M-> 키를 이용해 GTAGS file을 만든다.
(global-set-key (kbd "M->") 'helm-gtags-create-tags)




(require 'google-c-style)
(add-hook 'c-mode-common-hook 'google-set-c-style)
(add-hook 'c-mode-common-hook 'google-make-newline-indent)
(add-hook 'c++-mode-common-hook 'google-set-c-style)
(add-hook 'c++-mode-common-hook 'google-make-newline-indent)


;; C언어 모드에서 자동정렬 (들여쓰기 스타일)
(add-hook 'c-mode-hook
          '(lambda ()
             (c-set-style "google")))


;;C++ 모드 자동정렬 (들여쓰기 스타일)
(add-hook 'c++-mode-hook
          '(lambda ()
             (c-set-style "google")))



;; completion-at-point를 비활성화합니다
;; (setq helm-mode-completion-at-point nil)


;; 단축키 지정===============================================================

;; 영어 대문자, 소문자를 토글해주는 함수
(defun xah-toggle-letter-case ()
  "Toggle the letter case of current word or text selection.
Always cycle in this order: Init Caps, ALL CAPS, all lower.

URL `http://ergoemacs.org/emacs/modernization_upcase-word.html'
Version 2017-04-19"
  (interactive)
  (let (
        (deactivate-mark nil)
        $p1 $p2)
    (if (use-region-p)
        (setq $p1 (region-beginning)
              $p2 (region-end))
      (save-excursion
        (skip-chars-backward "[:alnum:]-_")
        (setq $p1 (point))
        (skip-chars-forward "[:alnum:]-_")
        (setq $p2 (point))))
    (when (not (eq last-command this-command))
      (put this-command 'state 0))
    (cond
     ((equal 0 (get this-command 'state))
      (upcase-initials-region $p1 $p2)
      (put this-command 'state 1))
     ((equal 1  (get this-command 'state))
      (upcase-region $p1 $p2)
      (put this-command 'state 2))
     ((equal 2 (get this-command 'state))
      (downcase-region $p1 $p2)
      (put this-command 'state 0)))))


;; Alt + = 키로 region 영역에 영어단어를 대문자, 소문자, 앞에만 대문자 형식으로 토글해줍니다
(global-set-key (kbd "M-u") 'xah-toggle-letter-case)


;;최근 작업 파일 목록 열기
;; (global-set-key "\M-\p1" 'recentf-open-files)


;;f1 이전 버퍼창 이동
(global-set-key [f1] 'previous-buffer)

;;f2 다음 버퍼창 이동
(global-set-key [f2] 'next-buffer)

;; f3, C-left, C-right  윈도우 창 이동
(global-set-key [f3] 'next-multiframe-window)
(global-set-key (kbd "<M-right>") 'next-multiframe-window)
(global-set-key (kbd "<M-down>") 'next-multiframe-window)
(global-set-key (kbd "<M-left>") 'previous-multiframe-window)
(global-set-key (kbd "<M-up>") 'previous-multiframe-window)

;; F4 또는 M-] 키로 파일 탐색기 Dired 모드 켜기
(global-set-key [f4] 'dired)
;; (global-set-key (kbd "M-]") 'dired)

;; 단어 하이라이트(특정 단어만 색깔강조하기)
(global-set-key [f5] 'highlight-symbol)

;; 단어 하이라이트 모두 지우기
(global-set-key (kbd "<C-f5>") 'highlight-symbol-remove-all)

;; ECB 시작
(global-set-key [f6] 'ecb-minor-mode)

;; 컴파일 단축키
(global-set-key [f7] 'compile)

;; 디버깅 단축키
(global-set-key [f8] 'gdb)

;; 주석을 감췄다 보여줬다 하는 단축키 F9
(hide/show-comments)
(global-set-key [f9] 'hide/show-comments-toggle)

;; f10 라인 실행하고 다음 라인으로
(global-set-key [f10] 'gud-next)

;; f11 함수안으로 따라 들어간다
(global-set-key [f11] 'gud-step)

;; f12 소스창에서 바로 브레이크포인트 설정
(global-set-key [f12] 'gud-break)



;; shift + f11 현재 실행중인 함수 리턴후 멈춤
(global-set-key [(shift f11)] 'gud-finish)

;; shift + f10 현재 커서까지 실행하고 멈춤
(global-set-key [(shift f10)] '(lambda ()
                                 (interactive)
                                 (call-interactively 'gud-tbreak)
                                 (call-interactively 'gud-cont)))


;; Ctrl + 7 키로 선택한 버퍼를 닫습니다
(global-set-key (kbd "C-7") 'buffer-menu)

;; Ctrl + 8 키로 현재 버퍼를 닫습니다
(global-set-key (kbd "C-8") 'kill-this-buffer)

;; Ctrl + 9 키로 Customize Variable 명령어를 사용한다
(global-set-key (kbd "C-9") 'pwd)

;; Ctrl + 0 키로 Customize Variable 명령어를 사용한다
(global-set-key (kbd "C-0") 'customize-variable)



;; Alt + 1 키로 shell을 불러오는 커맨드를 실행합니다
(global-set-key (kbd "M-1") 'shell-command)

;; Alt + 2 키로 multi terminal을 실행합니다
(global-set-key (kbd "M-2") 'multi-term)

;; Alt + 3 키로 flycheck 기능을 ON/OFF합니다
(global-set-key (kbd "M-3") 'global-flycheck-mode)

;; Alt + 4 키로 projectile에 project를 제거합니다
(global-set-key (kbd "M-4") 'projectile-remove-known-project)

;; Alt + 5 키로 projectile에 project를 추가합니다
(global-set-key (kbd "M-5") 'projectile-add-known-project)

;; Alt + 6키로 remote 접속을 위한 notebooklist-open 명령어를 설정합니다
(global-set-key (kbd "M-6") 'ein:notebooklist-open)



;; edebug defun을 ctrl + b로 설정한다
(global-set-key "\C-b" 'edebug-defun)


;; Ctrl + q 키로 현재 창 남기고 나머지 창 모두 닫기
(global-set-key "\C-q" 'delete-other-windows)

;; Alt + q 키로 현재 창을 닫습니다
(global-set-key "\M-q" 'delete-window)


;; Shift + Space 키를 한영키에서 해제한다.
(global-unset-key (kbd "S-SPC"))


;; Ctrl + tab 키를 한/영키로
(global-unset-key (kbd "C-S-SPC"))
(global-set-key [(control tab)] 'toggle-input-method)

;;잘라내기, 붙여넣기, CTRL+C, V를 활성화 시켜준다.
(cua-mode)


;;북 마크에 저장 하기 Alt + m
(global-set-key "\M-m" 'bookmark-set)

;;북 마크 열기 Alt + v
(global-set-key (kbd "M-v") 'bookmark-jump)
(define-key cua--cua-keys-keymap (kbd "M-v") 'bookmark-jump)

;; 북마크 삭제 Ctrl + Alt + m
(global-set-key (kbd "C-M-m") 'bookmark-delete)

;;버퍼 목록 열기
;;(global-set-key "\M-\pl" 'electric-buffer-list)

;;버퍼 메뉴 열기
;;(global-set-key "\M-\pp" 'buffer-menu)

;;grep 실행
;;(global-set-key "\M-\pg" 'grep)

;;줄번호 이동(M-g)
(global-set-key "\M-g" 'goto-line)

;;커서에 위치한 문자열을 파일명으로 인식하여 열기.
;;(global-set-key "\M-1" 'find-file-at-point)

;;가로 분할 화면 위로 크기 조절
;;(global-set-key "\M-\p[" 'shrink-window)

;;가로 분할 화면 아래로 크기 조절
;;(global-set-key "\M-\p]" 'enlarge-window)

;;세로 화면 사이즈 좌측으로 크기 조절
;;(global-set-key "\M-\p;" 'shrink-window-horizontally)

;;세로 화면 사이즈 우측으로 크기 조절
;;(global-set-key "\M-\p'" 'enlarge-window-horizontally)

;; Ctrl + k 키로 해당 커서의 한 줄 전체를 지웁니다
(global-set-key "\C-k" 'kill-whole-line)


;; Alt + k 키로 해당 커서의 오른쪽부분만 삭제합니다
(global-set-key "\M-k" 'kill-visual-line)


;; Ctrl + A 키로 전체선택하게 합니다
(global-set-key "\C-a" 'mark-whole-buffer)


;; Ctrl + w 키로 해당 버퍼를 저장합니다
(global-set-key "\C-w" 'save-buffer)

;; Ctrl + Shift + w 키로 모든 버퍼를 저장합니다
(defun save-all () (interactive) (save-some-buffers t))
(global-set-key (kbd "C-S-w") 'save-all)

;; Ctrl + Alt + e 키로 현재 커서의 라인 맨 앞칸으로 이동합니다
(global-set-key (kbd "C-M-e") 'move-beginning-of-line)
(add-hook 'c-mode-hook
          '(lambda ()
             (local-set-key (kbd "C-M-e") 'move-beginning-of-line))
          )
(add-hook 'c++-mode-hook
          '(lambda ()
             (local-set-key (kbd "C-M-e") 'move-beginning-of-line))
          )


;; Ctrl + p 키로 grep 명령어를 실행합니다
(global-set-key (kbd "C-p") 'grep-find)

;; grep-find 기본 명령어를 아래와 같이 수정합니다
;;(setq grep-find-template
;;"find . <X> -type f <F> -exec grep <C> -nH -ie <R> \\{\\} +")
;;"find . -type f -exec grep --exclude=*{ph.h, rviz, rst} --include={cpp,c,h,py} -nH -ie   {} +" 같이 확장자를 필터링할 수 있다
(grep-apply-setting 'grep-find-command '("find . -type f -exec grep -nH -ie   {} +" . 35))
;;(grep-apply-setting 'grep-find-command '("find . -type d \\( -name '.git' \\) -prune -o -type f  -exec grep -nH -e  \\{\\} +" . 72))


;; Ctrl + ; 키로 find file 파일이 존재하는지 검색합니다
(global-set-key (kbd "C-;") 'helm-find)

;; Ctrl + ' 키로 find dir 폴더가 존재하는지 검색합니다
(global-set-key (kbd "C-'") 'helm-projectile-find-dir)

;; c++ 주석 처리 변경 코드 (// -> /* */ 로 변경한다)
(add-hook 'c++-mode-hook (lambda () (setq comment-start "/* "
                                          comment-end   "*/")))

;; python 주석 처리 변경 코드 (# -> ''' ''' 로 변경한다) ( 사용안함 )
;; (add-hook 'python-mode-hook (lambda () (setq comment-start "'\'' " ''''
;;                                              comment-end   "'\''"))) ''''


;; 괄호 사이를 이동하는 코드
;; (defun match-paren ()
;;   "% command of vi."
;;   (interactive)
;;   (let ((char (char-after (point))))
;;     (cond ((memq char '(?\( ?\{ ?\[))
;;            (forward-sexp 1)
;;            (backward-char 1))
;;           ((memq char '(?\) ?\} ?\]))
;;            (forward-char 1)
;;            (backward-sexp 1))
;;           (t (call-interactively 'self-insert-command)))))
(defun match-paren (arg)
            "Go to the matching paren if on a paren; otherwise insert %."
            (interactive "p")
            (cond ((looking-at "\\s(") (forward-list 1) (backward-char 1))
                  ((looking-at "\\s)") (forward-char 1) (backward-list 1))
                  (t (self-insert-command (or arg 1)))))

;; Ctrl + ] 키를 누르면 해당 괄호의 끝부분으로 이동합니다
(global-set-key (kbd "\C-]") 'match-paren)



(defun newline-without-break-of-line ()
  "1. move to end of the line, 2. insert newline with index."
  (interactive)
  (let ((oldpos (point)))
    (end-of-line)
    (newline-and-indent)))

(defun newline-without-break-of-line-upper ()
  "1. move to end of the line, 2. insert newline with index above."
  (interactive)
  (let ((oldpos (point)))
    (beginning-of-line)
    (open-line 1)))

;; Ctrl + F 키를 누르면 자동으로 빈 라인이 하나 만들어집니다 (vim의 o키와 동일합니다)
(global-set-key "\C-f" 'newline-without-break-of-line)

;; Ctrl + O 키를 누르면 자동으로 한 줄 위에 빈 라인이 하나 만들어집니다
(global-set-key "\C-o" 'newline-without-break-of-line-upper)


(defun increment-number-at-point ()
  "."
  (interactive)
  (skip-chars-backward "0-9")
  (or (looking-at "[0-9]+")
      (error "No number at point"))
  (replace-match (number-to-string (1+ (string-to-number (match-string 0))))))

;; Ctrl + t 를 누르면 커서의 숫자가 증가합니다
(global-set-key (kbd "C-t") 'increment-number-at-point)


;; 함수나 변수로 이동하는 단축키를 Alt + . , 로 설정한다
;; semantic이 gtags보다 좋네 gtags는 zz,aa로 설정했다
(global-set-key (kbd "M-.") 'semantic-ia-fast-jump)
(global-set-key (kbd "M-,") 'pop-global-mark)


;; 변수나 함수 하이라이팅한 구문을 빠르게 이동합니다 higlight-symbol 패키지
(global-set-key (kbd "M-n") 'highlight-symbol-next)
(global-set-key (kbd "M-p") 'highlight-symbol-prev)


;; Ctrl + G 단축키로 구문을 fold 접거나 펼치거나 합니다
(global-set-key "\C-g" 'hs-toggle-hiding)

;; Ctrl + PageUp, Down 단축키로 첫째줄, 마지막줄로 바로 이동합니다. Ctrl + Home, End는 원래 가능
(global-set-key (kbd "C-<prior>") 'beginning-of-buffer)
(global-set-key (kbd "C-<next>") 'end-of-buffer)


;; Alt + z로 시각화된 undo tree를 봅니다
(global-set-key "\M-z" 'undo-tree-visualize)

;; Ctrl + z로 뒤로가기 기능을 실행합니다
(global-set-key "\C-z" 'undo-tree-undo)


;; Alt + h로 vim처럼 한칸씩 아래로 움직입니다
(global-set-key "\M-h" 'next-line)

;; Alt + j로 vim처럼 한칸씩 위로 올라갑니다
(define-key c++-mode-map "\M-j" nil)
(define-key c-mode-map "\M-j" nil)
(global-set-key "\M-j" 'previous-line)


;; C-c + C-c 로 window의 사이즈를 조절합니다
(define-key c++-mode-map (kbd "C-c C-c") nil)
(define-key c-mode-map (kbd "C-c C-c") nil)
(global-set-key (kbd "C-c C-c") 'enlarge-window-horizontally)
;; python-mode에서도 같은 단축키가 동작하도록 설정한다
(add-hook 'python-mode-hook
          '(lambda ()
             (local-set-key (kbd "C-c C-c") 'enlarge-window-horizontally))
          )
(add-hook 'org-mode-hook
          '(lambda ()
             (local-unset-key (kbd "M-h"))
             (local-set-key (kbd "C-c C-c") 'enlarge-window-horizontally))
             (local-set-key (kbd "M-h") 'next-line)
          )


;; M-/ 키로 함수참조에 사용할 TAGS 파일을 변경합니다
(global-set-key (kbd "M-/") 'visit-tags-table)




;; M-l 키로 python 코드에서 들여쓰기를 보여줍니다
(global-set-key (kbd "M-l") 'highlight-indentation-mode)




(defun select-current-line ()
  "Select the current line"
  (interactive)
  (end-of-line) ; move to end of line
  (set-mark (line-beginning-position)))


;; Ctrl + y 키로 현재 커서의 라인을 선택합니다
(global-set-key (kbd "C-y") 'select-current-line)


;; Ctrl + b 키로 helm 파일 브라우저를 실행합니다
(global-set-key (kbd "C-b") 'helm-for-files)


(defun select-current-line-and-comment ()
  "Select the current line"
  (interactive)
  (end-of-line) ; move to end of line
  (set-mark (line-beginning-position))
  (comment-dwim 1))


;; Alt + ' 키로 현재 커서라인을 주석처리 Toggle ON/OFF 합니다
(global-set-key (kbd "M-;") 'select-current-line-and-comment)


;; Alt + w,e 키로 커서를 기준으로 한 구문을 선택할 수 있도록 합니다
(define-key c-mode-map (kbd "M-e") nil)
(define-key c-mode-map (kbd "M-w") nil)
(define-key c++-mode-map (kbd "M-e") nil)
(define-key c++-mode-map (kbd "M-w") nil)
(global-set-key (kbd "M-e") 'forward-sentence)
(global-set-key (kbd "M-w") 'backward-sentence)



;; Alt + \ 키로 magit의 상태창을 실행합니다
(global-set-key (kbd "M-\\") 'magit-status)

;; C-c + e 키로 git project에서 두 파일을 비교하는 magit-ediff-dwim을 수행합니다
(global-set-key (kbd "C-c e") 'magit-ediff-dwim)

;; C-c + d 키로 git project에서 두 파일을 비교하는 magit-diff-dwim을 수행합니다
(global-set-key (kbd "C-c d") 'magit-diff-dwim)

;; C-c + f키로 두 파일을 비교하는 diff 명령어를 실행합니다
(global-set-key (kbd "C-c f") 'diff)


;; C-c + t 키로 한 파일의 변경기록을 검사하는 magit-log-buffer-file 명령을 수행합니다
(global-set-key (kbd "C-c t") 'magit-log-buffer-file)

;; C-c + y 키로 다른 branch에 있는 파일의 내용을 확인합니다
(global-set-key (kbd "C-c y") 'magit-find-file)


;;; 이맥스가 기본적으로 제공하는 Git 백엔드를 켜두면 매우 느려진다. magit만 쓴다.
(setq vc-handled-backends nil)



;; Alt + [ 키로 선택된 단어를 iedit 일괄편집합니다
(global-set-key (kbd "M-[") 'iedit-mode)


;; Ctrl + =,+키로 avy (버퍼 간 빠른이동) 기능을 실행합니다
(global-set-key (kbd "C-=") 'avy-goto-word-0)
(global-set-key (kbd "C-+") 'avy-goto-word-1)


;; Ctrl + - 키로 swiper (버퍼 간 빠른이동) 기능을 실행합니다
(global-set-key (kbd "C--") 'swiper-all)


;; Alt + r 키로 해당 단어의 reference를 검색해줍니다
(global-set-key (kbd "M-e") 'helm-projectile-grep)


;; ESC키 2번으로 기존에 3번 ESC를 눌러야 작동하던 escape를 대신합니다
(global-set-key (kbd "<escape> <escape>") 'keyboard-escape-quit)


;; Ctrl + 4 키로 .md 파일을 파이어폭스로 프리뷰합니다 (not used)
;; (global-set-key (kbd "C-4") 'flymd-flyit)


;; C-5 키로 다른 프로젝트로 스위치하는 명령어를 실행합니다
(global-set-key (kbd "C-5") 'helm-projectile-switch-project)


;; Ctrl + 6키로 jupyter notebook 서버를 실행합니다
(global-set-key (kbd "C-6") 'ein:jupyter-server-start)

;; Ctrl + 6키로 remote 접속을 위한 notebooklist-login 명령어를 설정합니다
(global-set-key (kbd "C-^") 'ein:notebooklist-login)



;; helm-projectile-switch-project (C-5) 로 프로젝트를 바꾼 다음 실행하는 명령어로
;;                                         바뀐 프로젝트의 홈폴더에서 dired 모드를 실행합니다
(setq projectile-switch-project-action 'projectile-dired)




;;(add-to-list 'load-path "/opt/ros/kinetic/share/emacs/site-lisp")
;; or whatever your install space is + "/share/emacs/site-lisp"
;;(require 'rosemacs-config)

;; Package: key-chord를 사용합니다
(require 'key-chord)
;; 두 키가 입력되는데 걸리는 시간 설정
(setq key-chord-two-keys-delay 0.1) ; default 0.1
;; 1개의 키가 입력되는데 걸리는 시간 설정
(setq key-chord-one-key-delay 0.17) ; default 0.2
(key-chord-define-global "66" 'ein:jupyter-server-stop)        ;; jupyter notebook 서버 종료
(key-chord-define-global "``" 'helm-find-files)                ;; 파일 열기
(key-chord-define-global "??" 'split-window-right)             ;; 오른쪽에 새창 만들기
(key-chord-define-global ">>" 'split-window-below)             ;; 아래쪽에 새창 만들기
(key-chord-define-global ",," 'ac-complete-semantic)           ;; 코드 자동완성
(key-chord-define-global "<<" 'ac-complete-semantic-raw)       ;; 코드 자동완성2
(key-chord-define-global "mm" 'jedi:complete)                  ;; 코드 자동완성 for python
(key-chord-define-global "zz" 'helm-gtags-dwim)                ;; 코드 네비게이션 함수 찾아가기
(key-chord-define-global "aa" 'helm-gtags-pop-stack)           ;; 코드 네비게이션 돌아오기
(key-chord-define-global "xx" 'xref-find-definitions)          ;; 코드 네비게이션 함수 찾아가기 (up to emacs 25.2)
(key-chord-define-global "cc" 'xref-pop-marker-stack)          ;; 코드 네비게이션 돌아오기      (up to emacs 25.2)
(key-chord-define-global "xc" 'save-buffers-kill-terminal)     ;; emacs 종료하기 (or emacsclient)
(key-chord-define-global "zv" 'kill-emacs)                     ;; emacs --daemon 종료하기
;;(key-chord-define-global "df" 'save-buffer)
;;(key-chord-define-global "aa" 'helm-global-mark-ring)
(key-chord-mode t)



;; .h header 파일을 c++ 모드로 설정합니다
;; 아니면 아래 라인을 적용하지 않고 헤더파일 맨 첫줄에 // -*-c++-*- 구문을 입력합니다
;; 아니면 .hpp 파일로 만들면 됩니다
(add-to-list 'auto-mode-alist '("\\.h\\'" . c++-mode))


;; xml 구문을 folding해서 쉽게 보기 위해 아래와 같이 코드를 작성합니다.
(require 'hideshow)
(require 'sgml-mode)
(require 'nxml-mode)
(add-to-list 'hs-special-modes-alist
             '(nxml-mode
               "<!--\\|<[^/>]*[^/]>"
               "-->\\|</[^/>]*[^/]>"
               "<!--"
               sgml-skip-tag-forward
               nil))
(add-hook 'nxml-mode-hook 'hs-minor-mode)


;; Ctrl + g 키로 xml 파일 내에서 코드를 folding할 수 있습니다
(define-key nxml-mode-map (kbd "C-g") 'hs-toggle-hiding)


;; grep-find (ctrl-P) 명령어에서 새로운 grep 창이 열리지 않고 바로 현재창이 바뀌도록 하는 코드
(eval-when-compile (require 'cl))
(defun kill-grep-window ()
  (destructuring-bind (window major-mode)
      (with-selected-window (next-window (selected-window))
        (list (selected-window) major-mode))
    (when (eq major-mode 'grep-mode)
      (delete-window window))))
(add-hook 'next-error-hook 'kill-grep-window)



;; git gutter 모드를 사용해 수정된 라인을 하이라이팅한다
(global-git-gutter-mode +1)

;; custom 모양 및 색상 추가


(set-face-foreground 'git-gutter:modified "yellow")
(set-face-foreground 'git-gutter:added "green")
(set-face-foreground 'git-gutter:deleted "red")

;; C-c + g 키로 git gutter에서 수정된 부분을 뒤로 돌릴건지 물어보는 명령어를 실행합니다
(global-set-key (kbd "C-c g") 'git-gutter:revert-hunk)


;; ROS의 .launch 파일을 xml모드로 구문 하이라이팅하기 위해 설정합니다
(setq auto-mode-alist
      (append '((".*\\.launch\\'" . xml-mode))
              auto-mode-alist))
(setq auto-mode-alist
      (append '((".*\\.xacro\\'" . xml-mode))
              auto-mode-alist))
(setq auto-mode-alist
      (append '((".*\\.urdf\\'" . xml-mode))
              auto-mode-alist))
(setq auto-mode-alist
      (append '((".*\\.gazebo\\'" . xml-mode))
              auto-mode-alist))
(setq auto-mode-alist
      (append '((".*\\.world\\'" . xml-mode))
              auto-mode-alist))
(setq auto-mode-alist
      (append '((".*\\.sdf\\'" . xml-mode))
              auto-mode-alist))
;; ROS의 CMakefile을 구문하이라이팅하기 위해 설정합니다
(setq auto-mode-alist
      (append '((".*\\.txt\\'" . ruby-mode))
              auto-mode-alist))
(setq auto-mode-alist
      (append '((".*\\.vim\\'" . ruby-mode))
              auto-mode-alist))
(setq auto-mode-alist
      (append '((".*\\.msg\\'" . ruby-mode))
              auto-mode-alist))
;; .cu 같은 CUDA 확장자를 c++ 환경으로 인식하도록 설정합니다
(setq auto-mode-alist
      (append '((".*\\.cu\\'" . c++-mode))
              auto-mode-alist))
