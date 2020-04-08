(setq tg-font-lock-keywords
      (let* (;; define several category of keywords
	     (x-keywords '("BOX" "TUBE" "TUBS" "HYPE" "TWISTEDTRD"))
	     (x-types '("cm" "mm" "m" "meter" "degree"))
	     (x-constants '("G4_Ge" "G4_AIR" "G4_Galatic"))
	     (x-events '("at_rot_target" "at_target" "attach"))
	     (x-functions '("vis" "color" "volu" "rotm" "place"))
	     ;; generate regex string for each category of keywords
	     (x-keywords-regexp (regexp-opt x-keywords 'words))
	     (x-types-regexp (regexp-opt x-types 'words))
	     (x-constants-regexp (regexp-opt x-constants 'words))
	     (x-events-regexp (regexp-opt x-events 'words))
	     (x-functions-regexp (regexp-opt x-functions 'words)))
	`((,x-types-regexp . font-lock-type-face)
	  (,x-constants-regexp . font-lock-constant-face)
	  (,x-events-regexp . font-lock-builtin-face)
	  (,x-functions-regexp . font-lock-function-name-face)
	  (,x-keywords-regexp . font-lock-keyword-face)
	  ;; note: order above matters, because once colored, that part won't change.
	  ;; in general, put longer words first
	  ))) 

(define-derived-mode tg-mode c-mode "tg mode"
		     "major mode for editing Geant4 text geometry definition file" 
		     ;; code for syntax highlighting
		     (setq font-lock-defaults '((tg-font-lock-keywords))))

;; add the mode to the `features' list
(provide 'tg-mode)

;; autoload
(add-to-list 'auto-mode-alist '("\\.tg\\'" . tg-mode))
