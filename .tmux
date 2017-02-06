#!/bin/sh

set -e

SESSION_NAME="railtracing"

if tmux has-session -t ${SESSION_NAME} 2> /dev/null; then
  tmux attach -t ${SESSION_NAME}
  exit
fi

tmux new-session -d -s ${SESSION_NAME} -n vim

tmux send-keys -t ${SESSION_NAME}:vim "vim main.cpp" Enter

tmux split-window -t ${SESSION_NAME}:vim -h

tmux send-keys -t ${SESSION_NAME}:vim.right "make watch" Enter

tmux split-window -t ${SESSION_NAME}:vim.right -v

tmux send-keys -t ${SESSION_NAME}:vim.bottom-right "git status" Enter

tmux attach -t ${SESSION_NAME}:vim.left

