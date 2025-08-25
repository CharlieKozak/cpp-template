#!/usr/bin/env bash
set -euo pipefail

BASHRC="${HOME}/.bashrc"
CUSTOM_BASHRC="${CODESPACE_VSCODE_FOLDER}/.devcontainer/.bashrc"

# Add source line for our custom .bashrc if not already present
if [ -f "$BASHRC" ] && ! grep -qF "source ${CUSTOM_BASHRC}" "$BASHRC"; then
  echo "source ${CUSTOM_BASHRC}" >> "$BASHRC"
fi

echo "Post-create: prompt newline setup complete."
