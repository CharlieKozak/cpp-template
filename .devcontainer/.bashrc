# Custom bash configuration for cpp-template devcontainer

# Add newline + prompt symbol on a new line for interactive bash shells
if [[ $- == *i* ]]; then
  PS1="${PS1}\\n\\$ "
fi
