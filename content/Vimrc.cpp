source $VIMRUNTIME/defaults.vim
set tabstop=4
set shiftwidth=4
set nocompatible autoindent cindent ruler showcmd incsearch number relnumber
set cino+=L0
syntax on
filetype indent on

inoremap {<CR>  {<CR>}<Esc>O
inoremap {}     {}
imap jk         <Esc>
set belloff=all

" Select region and then type :Hash to hash your selection.
" Useful for verifying that there aren't mistypes.
ca Hash w !cpp -dD -P -fpreprocessed \| tr -d '[:space:]' \
 \| md5sum \| cut -c-6
