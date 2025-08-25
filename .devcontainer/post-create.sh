#!/usr/bin/env bash
set -euo pipefail

BASHRC="${HOME}/.bashrc"
MARK_START="# >>> prompt-newline >>>"
MARK_END="# <<< prompt-newline <<<"

if [ -f "$BASHRC" ] && ! grep -qF "$MARK_START" "$BASHRC"; then
  {
    echo "$MARK_START"
    echo "# Add newline + prompt symbol on a new line for interactive bash shells"
    echo "if [[ $- == *i* ]]; then"
    echo "  PS1=\"${PS1}\\n\\$ \""
    echo "fi"
    echo "$MARK_END"
  } >> "$BASHRC"
fi

echo "Post-create: prompt newline setup complete."
