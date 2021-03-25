[![home](https://img.shields.io/badge/gears-home-blue?style=flat)](../../..)
[![examples](https://img.shields.io/badge/gears-examples-green?style=flat)](../..)
[![detector](https://img.shields.io/badge/detector-construction-orange?style=flat)](..)

## Syntax highlighting for .tg files

### Emacs

[tg-mode.el](tg-mode.el) defines a major mode for editing `.tg` files in [Emacs][]. You can [install it manually](http://ergoemacs.org/emacs/emacs_installing_packages.html) in two steps. First,

```sh
$ mkdir -p ~/.emacs.d/lisp/
$ cp tg-mode.el ~/.emacs.d/lisp
```

Secondly, add the following two lines to your `~/.emacs`:

```lisp
(add-to-list 'load-path "~/.emacs.d/lisp/")
(load "tg-mode")
```

[Emacs]: https://www.gnu.org/software/emacs/

### Vim

[tg.vim](tg.vim) defines syntax highlighting rules for displaying `.tg` files in [Vim][]. You can install it in two steps as well. First,

```sh
$ mkdir -p ~/.vim/after/syntax/
$ cp tg.vim ~/.vim/after/syntax/
```

Secondly, add the following line to your `~/.vimrc`:

```vim
au BufNewFile,BufRead *.tg set filetype=tg
```

[Vim]:https://www.vim.org/

### Micro

[tg.yaml](tg.yaml) defines syntax highlighting rules for displaying `.tg` files in [Micro][], a modern replacement of the [nano][] editor. To install it, you simply do

```sh
$ mkdir -p ~/.config/micro/syntax/
$ cp tg.yaml ~/.config/micro/syntax/
```

[Micro]: https://micro-editor.github.io/
[nano]: https://www.nano-editor.org/

### Sublime Text

[tg.sublime-syntax](tg.sublime-syntax) defines syntax highlighting rules for displaying `.tg` files in [Sublime Text Editor][], which is great in indexing and multiple selection. To install it, simply do

```sh
$ cp tg.sublime-syntax ~/.config/sublime-text-3/Packages/User/
```

[Sublime Text Editor]: https://www.sublimetext.com/
