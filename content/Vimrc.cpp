source $VIMRUNTIME/defaults.vim
set ts=4 sw=4 ai cin nu cino+=L0
syntax on

inoremap {<CR>  {<CR>}<Esc>O
imap jk         <Esc>

" Select region and then type :Hash to hash your selection.
" Useful for verifying that there aren't mistypes.
ca Hash w !cpp -dD -P -fpreprocessed \| tr -d '[:space:]' \
 \| md5sum \| cut -c-6
