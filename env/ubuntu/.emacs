;;=======================================================================
;; Misc
;;=======================================================================
(mouse-wheel-mode t)							;; ホイールマウス
;; (global-font-lock-mode nil)						;; 文字の色つけを無効にする
(setq line-number-mode t)						;; カーソルのある行番号を表示
(setq column-number-mode t)						;; カーソル位置の文字数を表示
(auto-compression-mode t)						;; 日本語 info の文字化け防止
(set-scroll-bar-mode 'right)					;; スクロールバーを右に表示
;; (global-set-key "\C-z" 'undo)					;; C-z で UNDO
(setq frame-title-format
	  (concat "%b - emacs@" system-name))		;; フレームのタイトル指定

(display-time)									;; 時計を表示
;; (global-set-key "\C-h" 'backward-delete-char)	;; Ctrl-H でバックスペース
(setq make-backup-files nil)					;; バックアップファイルを作成しない
(setq read-file-name-completion-ignore-case t)	;; find file で大文字／小文字を区別しない
(setq split-width-threshold nil)				;; [emacs23] find file での画面分割は常に上下分割
(global-linum-mode)								;; 行番号を表示
(setq hl-line-face 'underline)					;; カーソル行の強調表示は下線を使う
(global-hl-line-mode)							;; カーソル行の強調表示 ON
;; (global-whitespace-mode)						;; スペースの可視化
;; (setq visible-bell t)							;; 警告音を消す
(delete-selection-mode t)						;; 選択領域を一括削除
;; (setq kill-whole-line t)							;; カーソルが行頭にある場合も行全体を削除
(setq scroll-step 5)							;; 画面スクロールを n ライン毎にする
;; (when (boundp 'show-trailing-whitespace)
;; (setq-default show-trailing-whitespace t))		;; 行末のスペースを強調表示
(global-set-key "\C-xp" (lambda () (interactive) (other-window -1)))	;; C-x p で C-x o の逆
(global-set-key	"\t"		'tab-to-tab-stop)	;; Tab
(global-set-key	"\C-a"		'mark-whole-buffer)	;; Ctrl + a で mark-whole-buffer
(global-set-key	"\M-g"		'goto-line)			;; Alt + g で goto-line
;; (iswitchb-mode 1)								;; C-x b バッファ切替 C-s 順送り C-r 逆送り
(global-set-key [M-right]	'next-buffer)		;; Alt + -> キーで次のバッファに移動
(global-set-key [M-left]	'previous-buffer)	;; Alt + <- キーで前のバッファに移動
;;
;;=======================================================================
;; 文字色の変更
;;=======================================================================
;; 型
(set-face-foreground 'font-lock-type-face "yellow")				;; 文字色：黄色
;; キーワード
;; (set-face-foreground 'font-lock-keyword-face "")				;; 文字色：標準
;; 文字列
(set-face-foreground 'font-lock-string-face "cyan")				;; 文字色：シアン
;; 関数名
;; (set-face-foreground 'font-lock-function-name-face "")		;; 文字色：標準
;; 変数名
(set-face-foreground 'font-lock-variable-name-face "red")		;; 文字色：赤
;; コメント
(set-face-foreground 'font-lock-comment-face "green")			;; 文字色：緑
;; (set-face-background 'font-lock-comment-face "black")		;; 背景色：標準
;;
;;=======================================================================
;; 最近使ったファイル
;;=======================================================================
;;(recentf-mode)
;;
;;=======================================================================
;; リージョンに色を付ける
;;=======================================================================
(setq transient-mark-mode t)
;;
;;=======================================================================
;; 対応する括弧を光らせる
;;=======================================================================
(show-paren-mode)
;;
;;=======================================================================
;; C-c c で compile コマンドを呼び出す
;;=======================================================================
(define-key mode-specific-map "c" 'compile)
;;
;;=======================================================================
;; スクリプトを保存する時、自動的に chmod +x を行うようにする
;;=======================================================================
;; http://www.namazu.org/~tsuchiya/elisp/#chmod
;; を参照
(defun make-file-executable ()
  "Make the file of this buffer executable, when it is a script source."
  (save-restriction
    (widen)
    (if (string= "#!"
		 (buffer-substring-no-properties 1
						 (min 3 (point-max))))
        (let ((name (buffer-file-name)))
          (or (equal ?. (string-to-char
			 (file-name-nondirectory name)))
              (let ((mode (file-modes name)))
                (set-file-modes name (logior mode (logand
						   (/ mode 4) 73)))
                (message (concat "Wrote " name " (+x)"))))))))
(add-hook 'after-save-hook 'make-file-executable)

;;
;;=======================================================================
;; TAB Setting
;;=======================================================================
(setq-default tab-width 4)
;;タブは 2 文字ごとに
;;追加　タブの設定は以下のようにしないとだめ
;; インデンドではない普通の TAB の入力は M-i
;; 改行＆インデント： C-j (C-Enter)
(setq-default tab-stop-list
  '(4 8 12 16 20 24 28 32 36 40 44 48 52 56 60 64 68 72 76 80 84 88 92 96 100))
(setq-default indent-tabs-mode t)

;;
;;=======================================================================
;; cua-mode setting
;;=======================================================================
(cua-mode t)
(setq cua-enable-cua-keys nil)							;; C-c や C-v の乗っ取りを阻止
(global-set-key	"\C-cr"	'cua-set-rectangle-mark)		;; emacs -nw では C-RET を認識できないため代替
;;(global-set-key	[?\C-c ?r]		'cua-set-rectangle-mark)	;; 同じ操作の異なる書き方
;;(global-set-key	(kbd "C-c r")	'cua-set-rectangle-mark)	;; 同じ操作の異なる書き方
;;(global-set-key	"\C-\ "			'cua-set-rectangle-mark)	;; スペースは '\ ' と表現する
;;(global-set-key	[?\C-\S-\ ]		'cua-set-rectangle-mark)	;; gnome-terminal では C-S-key 系は C-key と認識されるっぽい
;;(global-set-key	[?\C-\M-\ ]		'cua-set-rectangle-mark)	;; gnome-terminal では C-M-Space も使えないっぽい

;;
;;=======================================================================
;; C-mode setting
;;=======================================================================
(add-hook 'c-mode-common-hook
          '(lambda ()
             (c-set-style "cc-mode")
             (setq c-basic-offset tab-width)
			 (setq c-tab-always-indent t)
             (setq c-auto-newline t)
			 (c-toggle-auto-hungry-state)))

;;
;;=======================================================================
;; Evernote-mode setting
;;=======================================================================
;;(add-to-list 'load-path "<your load path>")	; already added to "site-lisp"
;;(require 'evernote-mode)
;;(setq evernote-username "<your evernote user name>")							; optional
;;(setq evernote-enml-formatter-command '("w3m" "-dump" "-I" "UTF8" "-O" "UTF8"))	; optional
;;(global-set-key "\C-cec" 'evernote-create-note)
;;(global-set-key "\C-ceo" 'evernote-open-note)
;;(global-set-key "\C-ces" 'evernote-search-notes)
;;(global-set-key "\C-ceS" 'evernote-do-saved-search)
;;(global-set-key "\C-cew" 'evernote-write-note)
;;(global-set-key "\C-cep" 'evernote-post-region)
;;(global-set-key "\C-ceb" 'evernote-browser)

;;
;;=======================================================================
;; Ruby-mode setting
;;=======================================================================
;;(setq ruby-indent-level 2)						;; default setting
(setq ruby-indent-tabs-mode t)

;;
;;=======================================================================
;; End of File
;;=======================================================================
